#include <unordered_map>
#include <vector>
#include <iostream>
#include <unordered_map>


template<typename T, typename Collection>
std::unordered_map<T, int> histogram(Collection& collection) {
    std::unordered_map<T, int> hist_map;
    for (auto const element : collection) {
        if (!hist_map.contains(element)) {
            hist_map[element] = 1;
        } else {
            hist_map[element] = ++hist_map[element];
        }
    }
    return hist_map;
}

int main() {
    
    std::vector<int> numbers = {1, 2, 3, 2, 3, 4, 5, 4, 5, 6, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6};

    std::unordered_map<int, int> hist = histogram<int>(numbers);

    for (auto element : hist) {
        std::cout << element.first << ": " << element.second << std::endl;
    }

    return 0;
}