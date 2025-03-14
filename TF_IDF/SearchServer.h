#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <set>
#include <map>
#include <random>
#include <cmath>
#include <numeric>
#include <sstream>
#include <optional>
#include <stdexcept>

#ifndef SEARCH_SERVER_H
#define SEARCH_SERVER_H

enum class DocumentStatus
{
    ACTUAL,
    IRRELEVANT,
    BANNED,
    REMOVED
};

class SearchServer
{
public:
    explicit SearchServer() = default;

    template <typename Container>
    explicit SearchServer(const Container &stop_words)
    {
        static_assert(std::is_same<typename Container::value_type,
                                   std::string>::value,
                      "Container must contain strings");
        if (IsNotValidWord(stop_words))
        {
            throw std::invalid_argument("Special symbols were used in stop-words");
        }
        for (const std::string &word : stop_words)
        {
            stop_words_.insert(word);
        }
    }

    explicit SearchServer(const std::string &text)
        : SearchServer(SplitIntoWords(text))
    {
    }

    struct Document
    {
        int id;
        DocumentStatus status;
        int rating;
        double relevance;

        Document(const int id, const DocumentStatus status, const int rating, const double relevance)
            : id(id), status(status), rating(rating), relevance(relevance)
        {
        }

        Document() : id(0), status(DocumentStatus::IRRELEVANT), rating(0), relevance(0) {}
    };

    friend std::ostream &operator<<(std::ostream &out, const Document &doc)
    {
        out << "{ document_id = " << doc.id << ", ";
        out << "relevance = " << doc.relevance << ", ";
        out << "rating = " << doc.rating << " } ";
        return out;
    }

private:
    struct DocumentData
    {
        int rating;
        DocumentStatus status;
    };

    struct DefaultKeyMapper
    {
        bool operator()(int &id, DocumentStatus &status, int &rating) const
        {
            return status == DocumentStatus::ACTUAL;
        }
    };

    struct Query
    {
        std::set<std::string> query_words_positive;
        std::set<std::string> query_words_negative;
    };

    const int MAX_RESULT_DOCUMENT_COUNT = 5;
    std::map<int, DocumentData> documents_;
    std::map<std::string, std::map<int, double>> word_to_document_freqs_;
    std::vector<Document> matched_documents_;
    std::set<std::string> stop_words_ = {};
    Query query_;
    int document_count_ = 0;

    std::vector<std::string> SplitIntoWords(const std::string &text) const
    {
        std::vector<std::string> words;
        std::string word;
        std::istringstream iss(text);
        while (iss >> word)
        {
            words.push_back(word);
        }
        return words;
    }

    std::vector<std::string> SplitIntoWordsNoStop(const std::string &text) const
    {
        std::vector<std::string> words;
        for (const std::string &word : SplitIntoWords(text))
        {
            if (stop_words_.count(word) == 0)
            {
                words.push_back(word);
            }
        }
        return words;
    }

    [[nodiscard]] static bool IsNotValidWord(const std::vector<std::string> &words)
    {
        return std::count_if(words.begin(), words.end(), [](std::string word)
                             { return std::any_of(word.begin(), word.end(), [](char c)
                                                  { return c > 0 && c < 32; }); }) > 0;
    }

    void ParseQuery(const std::string &text)
    {
        if (text.empty())
        {
            throw std::invalid_argument("Query is empty");
        }
        std::vector<std::string> words = SplitIntoWordsNoStop(text);

        if (IsNotValidWord(words))
        {
            throw std::invalid_argument("Query has banned symbols");
        }

        query_.query_words_negative.clear();
        query_.query_words_positive.clear();
        for (const std::string &word : words)
        {
            if (word.at(0) == '-')
            {
                if (word.substr(1).empty())
                {
                    throw std::invalid_argument("There is nothing after excluding symbol");
                }
                else if (word.substr(1)[0] == '-')
                {
                    throw std::invalid_argument("There is double exclusion in query");
                }

                query_.query_words_negative.insert(word.substr(1));
            }
            else
            {
                query_.query_words_positive.insert(word);
            }
        }
    }

    double idf(const std::string &word) const
    {
        return std::log(GetDocumentCount() * 1.0 / word_to_document_freqs_.at(word).size());
    }

    std::tuple<std::vector<std::string>, double> IDFPositiveWords(const int &document_id)
    {
        std::tuple<std::vector<std::string>, double> relevance;

        for (const std::string query_word : query_.query_words_negative)
        {
            if (word_to_document_freqs_.find(query_word) != word_to_document_freqs_.end() &&
                word_to_document_freqs_.at(query_word).find(document_id) != word_to_document_freqs_.at(query_word).end())
            {
                return std::make_tuple(std::vector<std::string>(), 0.0);
            }
        }

        for (const std::string query_word : query_.query_words_positive)
        {
            if (word_to_document_freqs_.find(query_word) != word_to_document_freqs_.end())
            {
                auto it = word_to_document_freqs_.at(query_word).find(document_id);
                if (it != word_to_document_freqs_.at(query_word).end())
                {
                    std::get<0>(relevance).push_back(query_word);
                    std::get<1>(relevance) += it->second * idf(query_word);
                }
            }
        }
        return relevance;
    }

    static int ComputeAverageRating(const std::vector<int> &ratings)
    {
        if (ratings.empty())
        {
            return 0;
        }
        return std::accumulate(ratings.begin(), ratings.end(), 0) / int(ratings.size());
    }

    void FindAllDocuments()
    {
        matched_documents_.clear();
        for (auto &document : documents_)
        {
            double tfidf = std::get<1>(IDFPositiveWords(document.first));
            if (tfidf > 0)
            {
                matched_documents_.push_back({document.first, document.second.status, document.second.rating, tfidf});
            }
        }
    }

public:
    size_t GetStopWordsSize() const
    {
        return stop_words_.size();
    }

    int GetDocumentCount() const
    {
        return static_cast<int>(document_count_);
    };

    DocumentData GetDocumentId(int index) const
    {
        return documents_.at(index);
    }

    std::tuple<std::vector<std::string>, DocumentStatus> MatchDocument(const std::string &raw_query, const int &document_id)
    {
        ParseQuery(raw_query);
        return {std::get<0>(IDFPositiveWords(document_id)), documents_[document_id].status};
    };

    void AddDocument(const int document_id, const std::string &document, DocumentStatus status, const std::vector<int> &ratings)
    {
        ++document_count_;
        const std::vector<std::string> words = SplitIntoWordsNoStop(document);
        const double inv_word_count = 1.0 / words.size();

        if (document_id < 0)
        {
            throw std::invalid_argument("Document id consists of negative number");
        }
        else if (documents_.count(document_id) > 0)
        {
            throw std::invalid_argument("Document id is already in SearchServer");
        }
        else if (IsNotValidWord(words))
        {
            throw std::invalid_argument("Document consists of invalid words");
        }

        const std::set<std::string> uniq_words(words.begin(), words.end());
        documents_.insert({document_id, {ComputeAverageRating(ratings), status}});
        for (const std::string &word : words)
        {
            word_to_document_freqs_[word][document_id] += inv_word_count;
        }
    }

    std::vector<Document> FindTopDocuments(const std::string &raw_query, const DocumentStatus &status)
    {
        return FindTopDocuments(raw_query, [status](int document_id, DocumentStatus st, int rating)
                                { return st == status; });
    }

    template <typename Key_mapper = DefaultKeyMapper>
    std::vector<Document> FindTopDocuments(const std::string &raw_query, const Key_mapper key_mapper = DefaultKeyMapper())
    {
        ParseQuery(raw_query);
        FindAllDocuments();
        std::sort(matched_documents_.begin(), matched_documents_.end(), [](const Document &lhs, const Document &rhs)
                  { return (lhs.relevance > rhs.relevance) ||
                           (std::abs(lhs.relevance - rhs.relevance) < 1e-6 && lhs.rating > rhs.rating); });
        std::vector<Document> matched_status;
        std::vector<Document> matched_top_documents;
        std::copy_if(matched_documents_.begin(), matched_documents_.end(), std::back_inserter(matched_status), [key_mapper](Document doc)
                     { return key_mapper(doc.id, doc.status, doc.rating); });
        if (matched_status.size() >= MAX_RESULT_DOCUMENT_COUNT)
        {
            matched_top_documents.assign(matched_status.begin(), matched_status.begin() + MAX_RESULT_DOCUMENT_COUNT);
        }
        else
        {
            matched_top_documents.assign(matched_status.begin(), matched_status.end());
        }
        return matched_top_documents;
    }
};

#endif // SEARCH_SERVER_H

template <typename _Iterator>
class Page
{
public:
    Page(_Iterator first, _Iterator last) : _M_first(first), _M_last(last) {};

    friend std::ostream &operator<<(std::ostream &out, const Page &page)
    {
        for (_Iterator it = page._M_first; it != page._M_last; ++it)
        {
            out << *it << " "; // Add space for better readability
        }
        return out;
    }

    _Iterator begin() const { return _M_first; }
    _Iterator end() const { return _M_last; }

private:
    _Iterator _M_first;
    _Iterator _M_last;
};

template <typename _Iterator>
class Paginator
{
public:
    typedef _Iterator iterator_type;
    using traits_type = std::iterator_traits<iterator_type>;
    using iterator_category = typename traits_type::iterator_category;
    using value_type = typename traits_type::value_type;
    using difference_type = typename traits_type::difference_type;
    using reference = typename traits_type::reference;
    using pointer = typename traits_type::pointer;

    explicit Paginator(_Iterator first, _Iterator last, int page_size = 1)
    {
        for (auto &it = first; it != last;)
        {
            auto next = it;
            std::advance(next, page_size);
            if (next > last)
            {
                next = last;
            }
            _M_pages.emplace_back(it, next);
            it = next;
        }
    }

    auto begin() const
    {
        return _M_pages.begin();
    }
    auto end() const
    {
        return _M_pages.end();
    }
    size_t size() const
    {
        return _M_pages.size();
    }

    Page<iterator_type> &operator->() const
    {
        return _M_pages.at(_M_current_page);
    }

    Paginator &
    operator++()
    {
        ++_M_current_page;
        return *this;
    }

    Paginator &
    operator++(int)
    {
        return Paginator(_M_current_page++);
    }

private:
    int _M_page_size;
    int _M_current_page = 0;
    std::vector<Page<iterator_type>> _M_pages;
};
