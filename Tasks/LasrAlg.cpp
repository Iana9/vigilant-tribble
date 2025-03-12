#include <vector>
#include <algorithm>
#include <random>
#include <iostream>


int main() {
    std::vector<int> init_vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 9, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    
    std::vector<int> odd_numbers;
    std::vector<int> sorted;
    size_t BOUND_VAL = 15;
    std::vector<int> result;
    int ran = std::rand();

    // Скопировать нечетные элементы из вектора в котором изначально 20 элементов в хештаблицу
    std::copy_if(init_vec.begin(), init_vec.end(), std::back_inserter(odd_numbers), [idx = 0](int) mutable {
        return idx++ % 2 != 0; }
    );
    auto last = std::unique(odd_numbers.begin(), odd_numbers.end());
    odd_numbers.erase(last, odd_numbers.end());

    // удалить все после 15 элемента по величине, оставшиеся вставить в новый вектор
    size_t bound = std::min(odd_numbers.size(), BOUND_VAL);
    sorted.resize(bound);
    std::partial_sort_copy(odd_numbers.begin(), odd_numbers.end(), sorted.begin(), sorted.end());

    // прибавив случайное число, новый вектор отсортировать по убыванию
    result.resize(bound);
    std::transform(sorted.begin(), sorted.end(), result.begin(), [ran] (int elem) { return elem + ran; });
    std::sort(result.begin(), result.end(), [] (int a, int b) { return a > b; });

    for (auto it = result.begin(); it != result.end(); ++it) {
        std::cout << *it << " ";
    }
}