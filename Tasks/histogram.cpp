#include "histogram.h"


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