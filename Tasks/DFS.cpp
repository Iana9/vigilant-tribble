#include <iostream>

class node {
    public:
        int value;
        node* left;
        node* right;
        node(int v) : value(v), left(nullptr), right(nullptr) {}
};

void dfs_PreOrderTraversal(node& n) {
    std::cout << n.value << " ";
    if (n.left != nullptr) {
        dfs_PreOrderTraversal(*n.left);
    }
    if (n.right!= nullptr) {
        dfs_PreOrderTraversal(*n.right);
    }
};

void dfs_InorderTraversal(node& n) {
    if (n.left != nullptr) {
        dfs_InorderTraversal(*n.left);
    }
    std::cout << n.value << " ";
    if (n.right!= nullptr) {
        dfs_InorderTraversal(*n.right);
    }
};

void dfs_PostorderTraversal(node& n) {
    if (n.left != nullptr) {
        dfs_PostorderTraversal(*n.left);
    }
    if (n.right!= nullptr) {
        dfs_PostorderTraversal(*n.right);
    }
    std::cout << n.value << " ";
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

    dfs_PreOrderTraversal(n1);
    std::cout << std::endl;

    dfs_InorderTraversal(n1);
    std::cout << std::endl;

    dfs_PostorderTraversal(n1);

    return 0;
}