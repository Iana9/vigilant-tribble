#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <set>
#include <map>
#include <random>
#include <cmath>
#include <numeric>

#ifndef SEARCH_SERVER_H
#define SEARCH_SERVER_H

class SearchServer
{
public:
    enum class DocumentStatus
    {
        ACTUAL,
        IRRELEVANT,
        BANNED,
        REMOVED
    };
private:
    struct Document
    {
        int id;
        DocumentStatus status;
        int rating;
        double relevance;
    };

    struct DocumentData {
        int rating;
        DocumentStatus status;
    };

    struct DefaultKeyMapper {
        bool operator()(int& id, DocumentStatus& status, int& rating) const {
            return status == DocumentStatus::ACTUAL;
        }
    };

    struct Query {
        std::set<std::string> query_words_positive;
        std::set<std::string> query_words_negative;
    };

    const int MAX_RESULT_DOCUMENT_COUNT = 5;
    std::map<int, DocumentData> documents_;
    std::map<std::string, std::map<int, double>> word_to_document_freqs_;
    std::vector<Document> matched_documents_;
    std::set<std::string> stop_words_;
    Query query_;
    int document_count_ = 0;

    std::vector<std::string> SplitIntoWords(const std::string& text) const {
        std::vector<std::string> words;
        std::string word;
        for (const char c : text) {
            if (c == ' ') {
                if (!word.empty()) {
                    words.push_back(word);
                    word.clear();
                }
            }
            else {
                word += c;
            }
        }
        if (!word.empty()) {
            words.push_back(word);
        }
        return words;
    }

    std::vector<std::string> SplitIntoWordsNoStop(const std::string& text) const {
        std::vector<std::string> words;
        for (const std::string& word : SplitIntoWords(text)) {
            if (stop_words_.count(word) == 0) {
                words.push_back(word);
            }
        }
        return words;
    }

    void ParseQuery(const std::string& text) {
        query_.query_words_negative.clear();
        query_.query_words_positive.clear();
        for (const std::string& word : SplitIntoWordsNoStop(text)) {
            if (word.at(0) == '-') {
                query_.query_words_negative.insert(word.substr(1));
            }
            else {
                query_.query_words_positive.insert(word);
            }
        }
    }

    double idf(const std::string& word) const {
        return std::log(GetDocumentCount() * 1.0 / word_to_document_freqs_.at(word).size());
    }

    std::tuple<std::vector<std::string>, double> IDFPositiveWords(const int& document_id) {
        std::tuple<std::vector<std::string>, double> relevance;

        for (const std::string query_word : query_.query_words_negative) {
            if (word_to_document_freqs_.find(query_word) != word_to_document_freqs_.end() &&
                word_to_document_freqs_.at(query_word).find(document_id) != word_to_document_freqs_.at(query_word).end()) {
                return std::make_tuple(std::vector<std::string>(), 0.0);
            }
        }

        for (const std::string query_word : query_.query_words_positive) {
            if (word_to_document_freqs_.find(query_word) != word_to_document_freqs_.end()) {
                auto it = word_to_document_freqs_.at(query_word).find(document_id);
                if (it != word_to_document_freqs_.at(query_word).end()) {
                    std::get<0>(relevance).push_back(query_word);
                    std::get<1>(relevance) += it->second * idf(query_word);
                }
            }
        }
        return relevance;
    }

    static int ComputeAverageRating(const std::vector<int>& ratings) {
        if (ratings.empty()) {
            return 0;
        }
        return std::accumulate(ratings.begin(), ratings.end(), 0) / int(ratings.size());
    }

    void FindAllDocuments()
     {
        matched_documents_.clear();
        for (auto& document : documents_) {
            double tfidf = std::get<1>(IDFPositiveWords(document.first));
            if (tfidf > 0) {
                matched_documents_.push_back({ document.first, document.second.status, document.second.rating, tfidf});
            }
        }
    }
public:

    size_t GetStopWordsSize() const {
        return stop_words_.size();
    }

    int GetDocumentCount() const {
        return static_cast<int>(document_count_);
    };

    std::tuple<std::vector<std::string>, DocumentStatus> MatchDocument(const std::string& raw_query, const int& document_id) {
        ParseQuery(raw_query);
        return {std::get<0>(IDFPositiveWords(document_id)), documents_[document_id].status};
    };

    void AddDocument(const int document_id, const std::string& document, DocumentStatus status, const std::vector<int>& ratings) {
        ++document_count_;
        const std::vector<std::string> words = SplitIntoWordsNoStop(document);
        const double inv_word_count = 1.0 / words.size();
        const std::set<std::string> uniq_words(words.begin(), words.end());

        documents_.insert({ document_id, { ComputeAverageRating(ratings), status } });
        for (const std::string& word : words) {
            word_to_document_freqs_[word][document_id] += inv_word_count;
        }
    }

    void SetStopWords(const std::string& text) {
        for (const std::string& word : SplitIntoWords(text)) {
            stop_words_.insert(word);
        }
    }

    std::vector<Document> FindTopDocuments(const std::string& raw_query, const DocumentStatus& status) {
        return FindTopDocuments(raw_query, [status](int document_id, DocumentStatus st, int rating) { return st == status; });
    }

    template <typename Key_mapper = DefaultKeyMapper>
    std::vector<Document> FindTopDocuments(const std::string& raw_query, const Key_mapper key_mapper = DefaultKeyMapper()) {
        ParseQuery(raw_query);
        FindAllDocuments();
        std::sort(matched_documents_.begin(), matched_documents_.end(), [](const Document& lhs, const Document& rhs) { 
            return (lhs.relevance > rhs.relevance) ||
                (std::abs(lhs.relevance - rhs.relevance) < 1e-6 && lhs.rating > rhs.rating); });
        std::vector<Document> matched_status;
        std::vector<Document> matched_top_documents;
        std::copy_if(matched_documents_.begin(), matched_documents_.end(), std::back_inserter(matched_status), [key_mapper](Document doc) { return key_mapper(doc.id, doc.status, doc.rating); });
        if (matched_status.size() >= MAX_RESULT_DOCUMENT_COUNT) {
            matched_top_documents.assign(matched_status.begin(), matched_status.begin() + MAX_RESULT_DOCUMENT_COUNT);
        }
        else {
            matched_top_documents.assign(matched_status.begin(), matched_status.end());
        }
        return matched_top_documents;
    }
};

#endif // SEARCH_SERVER_H