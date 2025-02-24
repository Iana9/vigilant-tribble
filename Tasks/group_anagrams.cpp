#include "group_anagrams.h"

std::string Solution::sort_key(std::string word) {
    std::sort(word.begin(), word.end());
    return word;
};

std::vector<std::vector<std::string>> Solution::groupAnagrams(std::vector<std::string>& strs) {
    std::unordered_map<std::string,std::vector<std::string>> strs_map;
    std::vector<std::vector<std::string>> result;
    for (const std::string& word : strs) {
        std::string bucket = sort_key(word);
        strs_map[bucket].push_back(word);
    }
    for (const auto& pair : strs_map) {
        result.push_back(pair.second);
    }
    return result;
};