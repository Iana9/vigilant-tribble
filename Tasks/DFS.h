#ifndef DFS_H
#define DFS_H

#include <iostream>

class node {
    public:
        int value;
        node* left;
        node* right;
        node(int v) : value(v), left(nullptr), right(nullptr) {}
};

enum Type {
    PRE_ORDER = 1,
    IN_ORDER,
    POST_ORDER
};

class DFS {
    public:
        void Traversal(node& n, Type type);

        template <typename T>
        node* Search(node& n, T search_val, Type type) 
        {
            switch (type) {
                case Type::PRE_ORDER:
                    return PreOrderTraversal(n, search_val);
                case Type::IN_ORDER:
                    return InorderTraversal(n, search_val);
                case Type::POST_ORDER:
                    return PostorderTraversal(n, search_val);
                default:
                    return nullptr;
            }
        };

    private:
        void PreOrderTraversal(node& n);
        template <typename T>
        node* PreOrderTraversal(node& n, T search_val);
        void InorderTraversal(node& n);
        template <typename T>
        node* InorderTraversal(node& n, T search_val);
        void PostorderTraversal(node& n);
        template <typename T>
        node* PostorderTraversal(node& n, T search_val);
};

template <typename T>
node* DFS::PreOrderTraversal(node& n, T search_val) 
{
    if (n.value == search_val) {
        return &n;
    }
    if (n.left != nullptr) {
        node* result = PreOrderTraversal(*n.left, search_val);
        if (result != nullptr) {
            return result;
        }
    }
    if (n.right!= nullptr) {
        node* result = PreOrderTraversal(*n.right, search_val);
        if (result!= nullptr) {
            return result;
        }
    }
    return nullptr;
};

template <typename T>
node* DFS::InorderTraversal(node& n, T search_val) 
{
    if (n.value == search_val) {
        return &n;
    }
    if (n.left != nullptr) {
        node* result = InorderTraversal(*n.left, search_val);
        if (result != nullptr) {
            return result;
        }
    }
    if (n.right!= nullptr) {
        node* result = InorderTraversal(*n.right, search_val);
        if (result!= nullptr) {
            return result;
        }
    }
    return nullptr;
};

template <typename T>
node* DFS::PostorderTraversal(node& n, T search_val)
{
    if (n.value == search_val) {
        return &n;
    }
    if (n.left != nullptr) {
        node* result = PostorderTraversal(*n.left, search_val);
        if (result != nullptr) {
            return result;
        }
    }
    if (n.right!= nullptr) {
        node* result = PostorderTraversal(*n.right, search_val);
        if (result!= nullptr) {
            return result;
        }
    }
    return nullptr;
};

#endif