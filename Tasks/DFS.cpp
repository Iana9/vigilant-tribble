#include <iostream>

class node {
    public:
        int value;
        node* left;
        node* right;
        node(int v) : value(v), left(nullptr), right(nullptr) {}
};

void dfs(node& n) {
    std::cout << n.value << " ";
    if (n.left != nullptr) {
        dfs(*n.left);
    }
    if (n.right!= nullptr) {
        dfs(*n.right);
    }
};


int main() 
{
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

    dfs(n1);

    return 0;
}