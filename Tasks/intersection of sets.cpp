#include "histogram.cpp"


template<typename T>
std::vector<T> intersection_unordered_sets(std::vector<T>& first_set, std::vector<T>& sector_set){
    std::unordered_map<T, int> first_hist = histogram<T>(first_set);
    std::unordered_map<T, int> second_hist = histogram<T>(sector_set);
    std::vector<T> result;
    for (const auto& elem : first_hist) {
        if (second_hist.contains(elem.first)) {
            result.push_back(elem.first);
        }
    }
    return result;
}


int main() {
    
    std::vector<int> numbers1 = {1, 2, 3, 2, 3, 4, 5, 4, 5, 6, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6};
    std::vector<int> numbers2 = {1, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6};

    std::vector<int> hist = intersection_unordered_sets<int>(numbers1, numbers2);

    for (auto element : hist) {
        std::cout << element << std::endl;
    }

    return 0;
}