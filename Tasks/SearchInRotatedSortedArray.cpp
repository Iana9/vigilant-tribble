#include <vector>
#include <iostream>

class Solution {
public:
    int search(std::vector<int>& nums, int target) {
        int pivot = findPivot(nums);
        int result;
        if (pivot > -1) {
            if (nums[pivot] == target) { return pivot; }
            if (target >= nums[0]) {
                result = binarySearch(nums.begin(), nums.begin() + pivot, target);
            }
            else {
                result = this->binarySearch(nums.begin() + pivot + 1, nums.end(), target);
                result = (result > -1 ? result + pivot + 1 : -1);
            }
        } else {
            result = this->binarySearch(nums.begin(), nums.end(), target);
        }
        return result;
    }
private:
    int binarySearch(std::vector<int>::const_iterator begin, std::vector<int>::const_iterator end, int target) {
        int low, high, mid;
        low = 0;
        high = end - begin - 1;
        while (low <= high) {
            mid = low + (high - low) / 2;
            if (*(begin + mid) == target) { return mid; }
            else if (*(begin + mid) < target) { low = mid + 1; }
            else { high = mid - 1; }
        }
        return -1;
    }

    int findPivot(std::vector<int>& nums) {
        int high, low, mid;
        low = 0;
        high = nums.size() - 1;
        while (low <= high) {
            mid = low + (high - low) / 2;

            if (mid < high && nums[mid] >= nums[mid+1]) { return mid; }
            else if (mid > low && nums[mid] <= nums[mid-1]) { return mid-1; }

            if (nums[low] >= nums[mid]) { high = mid - 1; }
            else { low = mid + 1; }
        }
        return -1;
    }
};


int main() { 
    std::vector<int> num{3,1};
    Solution sol;
    
    auto res = sol.search(num, 3);

    std::cout << res << std::endl;
    return 0;
}