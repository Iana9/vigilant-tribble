#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <vector>
#include <iostream>
#include <unordered_map>

template<typename T, typename Collection>
std::unordered_map<T, int> histogram(Collection& collection);

#endif