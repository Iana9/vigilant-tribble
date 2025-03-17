#include <unordered_map>
#include <queue>
#include <iostream>
#include <cassert>
#include <cstdint>

// в класс идут запросы, ts + userid, по вызову get возвращать юзеров, которые за последние 300 сек сделали больше 5000 запросов
class RobotStatistics {
    public:
        void hit(std::uint32_t ts, std::uint32_t user_id) {
            robots_requests_[user_id].push(ts);
            removeTs(ts);
            updateUsersHits();
        }
        
        int get(std::uint32_t ts) {
            removeTs(ts);
            updateUsersHits();
            return users_hits_;
        }
    
    private:
        std::unordered_map<std::uint32_t, std::queue<std::uint32_t>> robots_requests_; // user_id -> ts of requests
        std::uint32_t users_hits_ = 0;
        void removeTs(std::uint32_t ts) {
            for (auto& user : robots_requests_) {
                while (!user.second.empty() && user.second.front() + 300 < ts) {
                    user.second.pop();
                }
            }
        }
        void updateUsersHits() {
            users_hits_ = 0;
    
            for (const auto& user : robots_requests_) {
                if (user.second.size() > 5000) {
                    users_hits_++;
                }
            }
        }
};