#include <string>
#include <iostream>
#include <set>


class Solution {
    public:
        int lengthOfLongestSubstring(std::string s) {
            if (s.size() == 0) { return 0; }
            int lC = 0;
            std::set<char> uniqC{s[lC]};
            for (int lR = 1; lR < s.size(); ++lR) {
                if (uniqC.contains(s[lR])) {
                    intCounter = std::max(intCounter, static_cast<int>(uniqC.size()));
                    while (uniqC.contains(s[lR])) {
                        uniqC.erase(s[lC]); 
                        lC += 1;
                    }
                }
                uniqC.insert(s[lR]);
            }
            intCounter = std::max(intCounter, static_cast<int>(uniqC.size()));
            return std::move(intCounter);
        }
    private:
        int intCounter = 1;
    };

int main() { 
    Solution sol;
    std::string s{"qrsvbspk"};
    std::cout << sol.lengthOfLongestSubstring(s);

    return 0;
}  