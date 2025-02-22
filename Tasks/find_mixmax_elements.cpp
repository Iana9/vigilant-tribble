
#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>

template <typename Collection>
std::pair<typename Collection::value_type, typename Collection::value_type> find_minmax_element(Collection& collection) {
    collection.erase(
    std::remove_if(
        collection.begin(),
        collection.end(),
        [](int i) { return i % 2; }), collection.end());
    using T = typename Collection::value_type;
    T min = collection[0];
    T max = collection[0];
    for (int i = 1; i < collection.size(); ++i) {
        min = collection[i] < min ? collection[i] : min;
        max = collection[i] > max ? collection[i] : max;
    }
    return std::make_pair(min, max);
}
int main(){

    std::vector<int> elements = {1,2,3, 4,5,6,7,8,9,10,11, 12, 13, 14, 15, 16, 17, 18, 19, 20};

    std::pair<int, int> minmax = find_minmax_element(elements);

    std::cout << minmax.first << " " << minmax.second << std::endl;

    for (auto element : elements) {
        std::cout << element << std::endl;
    }

    return 0;
}