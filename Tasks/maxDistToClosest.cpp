#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
    public:
        int maxDistToClosest(std::vector<int>& seats) {
            int maxDist = 0;
            int left = -1;
            int right = 0;

            while (right < seats.size()) {
                if (seats[right] == 1) {
                    if (left == -1) {
                        maxDist = right;
                    } else {
                        maxDist = std::max(maxDist, (right - left) / 2);
                    }
                    left = right;
                }
                right++;
            }
            if (left != seats.size() - 1) {
                maxDist = std::max(maxDist, static_cast<int>(seats.size()) - 1 - left);
            }
            return maxDist;
    }
};



int main() {
    using std::cout;
    using std::endl;
    Solution s;
    std::vector<int> seats = {1,0,0,0,1,0,1};
    cout << s.maxDistToClosest(seats) << endl;
    return 0;
}