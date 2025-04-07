#include <vector>
#include <unordered_map>
#include <iostream>


class Solution {
    public:
        int subarraySum(std::vector<int>& nums, int k) {
            std::unordered_map<int, int> sum_acc;
            sum_acc[0] = 1;
            int sum = 0;
            int count = 0;

            for (int num : nums) {
                sum += num;
                if (sum_acc.find(sum - k) != sum_acc.end()) {
                    count += sum_acc[sum - k];
                }
                sum_acc[sum] += 1;
            }
    
            return count;
        }
    };

int main() { 
    Solution sol;
    std::vector s{1,2,3};
    std::cout << sol.subarraySum(s, 3);

    return 0;
}  