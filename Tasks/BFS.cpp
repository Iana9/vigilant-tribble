#include <iostream>
#include <queue>

class node {
    public:
        int value;
        node* left;
        node* right;
        node(int v) : value(v), left(nullptr), right(nullptr) {}
};

void bfs(node& n) {
    std::queue<node*> q;
    q.push(&n);
    while (!q.empty()) {
        node* current = q.front();

        if (current->left != nullptr) q.push(current->left);
        if (current->right != nullptr) q.push(current->right);
        
        std::cout << current->value << std::endl;
        q.pop();
    }
};

template <typename T>
node* bfs(node& n, T search_value) {
    std::queue<node*> q;
    q.push(&n);
    while (!q.empty()) {
        node* current = q.front();
        if (current->value == search_value) {
            return current;
        }

        if (current->left != nullptr) q.push(current->left);
        if (current->right != nullptr) q.push(current->right);
        
        q.pop();
    }
};

int main() {
    node n1(1);
    node n2(2);
    node n3(3);
    node n4(4);
    node n5(5);
    node n6(6);
    node n7(7);
    node n8(8);
    node n9(9);

    n1.left = &n2;
    n1.right = &n3;

    n2.left = &n4;
    n2.right = &n5;

    n3.left = &n6;
    n3.right = &n7;

    n4.left = &n8;
    n4.right = &n9;

    bfs(n1);

    node* res = bfs(n1, 4);

    std::cout << res->value << std::endl;

    return 0;
}