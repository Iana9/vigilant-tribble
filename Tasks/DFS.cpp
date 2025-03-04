
#include "DFS.h"

void DFS::PreOrderTraversal(node& n) 
{
    std::cout << n.value << " ";
    if (n.left != nullptr) {
        PreOrderTraversal(*n.left);
    }
    if (n.right!= nullptr) {
        PreOrderTraversal(*n.right);
    }
}
void DFS::InorderTraversal(node& n) 
{
    if (n.left != nullptr) {
        InorderTraversal(*n.left);
    }
    std::cout << n.value << " ";
    if (n.right!= nullptr) {
        InorderTraversal(*n.right);
    }
}
void DFS::PostorderTraversal(node& n)
{
    if (n.left != nullptr) {
        PostorderTraversal(*n.left);
    }
    if (n.right!= nullptr) {
        PostorderTraversal(*n.right);
    }
    std::cout << n.value << " ";
}

void DFS::Traversal(node& n, Type type) 
{
    switch (type) {
        case Type::PRE_ORDER:
            PreOrderTraversal(n);
            break;
        case Type::IN_ORDER:
            InorderTraversal(n);
            break;
        case Type::POST_ORDER:
            PostorderTraversal(n);
            break;
    }
}



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

    DFS dfs;

    dfs.Traversal(n1, Type::PRE_ORDER);
    std::cout << std::endl;

    dfs.Traversal(n1, Type::IN_ORDER);
    std::cout << std::endl;

    dfs.Traversal(n1, Type::POST_ORDER);
    std::cout << std::endl;

    node* res = dfs.Search<int>(n1, 6, Type::IN_ORDER);
    std::cout << res->value;

    return 0;
}