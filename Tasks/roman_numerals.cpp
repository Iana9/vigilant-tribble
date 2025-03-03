#include <vector>
#include <string>
#include <iostream>

class Solution {
    using romannumerals = std::vector<std::pair<int,std::string>>;
    public:
        std::string intToRoman(int num) {
            std::string result = "";
            for (const auto& [value, symbol] : romanNumerals) {
                while (num >= value) {
                    result += symbol;
                    num -= value;
                }
            }
            return result;
        }
    private:
        romannumerals romanNumerals = 
        {
            {1000, "M"},
            {900, "CM"},
            {500, "D"},
            {400, "CD"},
            {100, "C"},
            {90, "XC"},
            {50, "L"},
            {40, "XL"},
            {10, "X"},
            {9, "IX"},
            {5, "V"},
            {4, "IV"},
            {1, "I"}
        };
};


int main()
{
    Solution sol;
    std::cout << sol.intToRoman(3999) << std::endl; // "MCMXCIX"
    return 0;
}