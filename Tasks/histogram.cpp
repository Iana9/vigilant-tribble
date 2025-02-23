#include "histogram.h"


template<typename T, typename Collection>
std::unordered_map<T, int> histogram(Collection& collection) {
    std::unordered_map<T, int> hist_map;
    for (auto const element : collection) {
        hist_map[element]++;
    }
    return hist_map;
}