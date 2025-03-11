#include <vector>
#include <iostream>
#include <sstream>

template<typename It>
std::vector<std::pair<It, It>> Split(It beg, It end) {
    std::vector<std::pair<It, It>> words;
    It word_begin = beg;
    for (auto it = beg; it != end; ++it) {
        if (*it == ' ') {
            words.push_back(std::make_pair(word_begin, it+1));
            word_begin = it + 1;
        }
    }
    return words;
}

int main() {
    std::string foo = "hello, world, and one more time hello! ";
    auto words = Split(foo.begin(), foo.end());
    for (const auto& it : words) {
        std::string word{it.first, it.second};
        std::cout << word << '|' << std::endl;
    }
    return 0;
}