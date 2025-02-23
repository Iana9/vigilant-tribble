#ifndef GROUP_ANAGRAMS_H
#define GROUP_ANAGRAMS_H

#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

class Solution {
    public:
        std::string sort_key(std::string word);
    
        std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs);
};
#endif