// A. Интервью:
// 1. Записать себе заготовки обхода в ширину и глубину. Сделать их попроще чтобы окинуть взглядом и сразу вспомнилось.
// 2. Записать себе заготовку бинарного поиска.

#include <iostream>
#include <queue>
#include <vector>

struct node {
    int value;
    node* left;
    node* right;
    node(int value) : value(value), left(nullptr), right(nullptr) {};
    node(int value, node* left) : value(value), left(left), right(nullptr) {};
    node(int value, node* left, node* right) : value(value), left(left), right(right) {};
};

void dfs(node* root) {
    if (root != nullptr) {
        std::cout << root->value << std::endl;
    }
    if (root->left != nullptr) {
        dfs(root->left);
    }
    if (root->right!= nullptr) {
        dfs(root->right);
    }
}

void bfs(node* root) {
    std::queue<node*> q;
    q.push(root);
    while (!q.empty()) {
        node* current = q.front();
        q.pop();
        if (current->left != nullptr) { q.push(current->left); }
        if (current->right != nullptr) { q.push(current->right); }
        std::cout << current->value << std::endl;
    }
}

template<typename Container, typename El>
int binarySearch(const Container& container, const El value) {
    int high = static_cast<int>(container.size());
    int low = 0;
    while (low <= high) {
        int middle = low + (high - low) / 2;
        if (container[middle] == value) { return middle; }
        if (value > container[middle]) { low = middle + 1; }
        else if (value < container[middle]) { high = middle - 1; }
    }
}

int main() 
{

    node* root = new node(5, new node(3, new node(1), new node(4)), new node(8, new node(6), new node(9)));

    bfs(root);

    std::vector<int> values = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int result = binarySearch(values, 123);

    std::cout << "Binary search result: " << result << std::endl;

    return 0;
}