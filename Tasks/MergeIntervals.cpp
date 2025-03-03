#include <vector>
#include <algorithm>
#include <iostream>

class Solution {
    public:
        std::vector<std::vector<int>> merge(std::vector<std::vector<int>>& intervals) {
            std::sort(intervals.begin(), intervals.end());

            std::vector<int> pre_result = intervals.empty() ? std::vector<int>() : intervals[0];
            std::vector<std::vector<int>> result;

            for (int i = 1; i < intervals.size(); i++) {
                std::vector<int> interval = intervals[i];
                if (doIntervalsOverlap(pre_result, interval)) {
                    pre_result[1] = std::max(pre_result[1], interval[1]);
                } else {
                    result.push_back(pre_result);
                    pre_result = interval;
                }
            }
            result.push_back(pre_result);
            return result;
        }
    private:
    bool doIntervalsOverlap(const std::vector<int>& interval1, const std::vector<int>& interval2) {
        return (interval1[0] <= interval2[1] && interval1[1] >= interval2[0]);
    }
};
    
int main(){
    std::vector<std::vector<int>> intervals = {{1,3},{2,6},{8,10},{15,18}};

    Solution sol;
    std::vector<std::vector<int>> merged = sol.merge(intervals);
    
    for (const auto& vec : merged) {
        for (const auto el : vec) {
            std::cout << el << " ";
        }
        std::cout << std::endl;
    }

    intervals = {{2, 3},
    {4, 5},
    {6, 7},
    {8, 9},
    {1, 10}};
    merged = sol.merge(intervals);
    for (const auto& vec : merged) {
        for (const auto el : vec) {
            std::cout << el << " ";
        }
        std::cout << std::endl;
    }

}