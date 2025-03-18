#include <stdexcept>
#include <map>
#include <cstdint>
#include <iostream>

struct node {
    int data;
    int key;
    node* next;
    node* prev;
    node(int key, int data) : key(key), data(data), next(nullptr), prev(nullptr) {}
};

class DoublyLinkedList {
public:
    node* head;
    node* tail;

    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    ~DoublyLinkedList() {
        node* current = head;
        while (current) {
            node* next = current->next;
            delete current;
            current = next; 
        }
    }

    void push(int key, int data) {
        node* newNode = new node(key, data);
        if (tail != nullptr) {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        } else { 
            head = tail = newNode;
         } 
    }

    void remove(node* nodeToRemove) {
        node* prev = nodeToRemove->prev;
        node* next = nodeToRemove->next;
        if (prev != nullptr) {
            prev->next = next;
        } else {
            head = next;
        }
        if (next != nullptr) {
            next->prev = prev;
        } else {
            tail = prev;
        }
        delete nodeToRemove;
    }

};

class LRUCache {
public:
    LRUCache(int capacity) {
        if (capacity < 0) {
            throw std::invalid_argument("Capacity must be be positive");
        } else { capacity_ = capacity; };
    }
    
    int get(int key) {
        auto it = cache_access_.find(key);
        if (it != cache_access_.end()) {
            node* curNode = it->second;
            int value = curNode->data;
            cache_.remove(curNode);
            cache_.push(key, value);
            it->second = cache_.tail;
            return value;
        } else {
            return -1;
        }
    }
    
    void put(int key, int value) {
        auto it = cache_access_.find(key);
        if (it != cache_access_.end()) {
            node* curNode = it->second;
            cache_.remove(curNode);
            cache_.push(key, value);
            it->second = cache_.tail;
        } else {
            if (cache_access_.size() >= capacity_) {
                node* nodeToRemove = cache_.head;
                cache_access_.erase(nodeToRemove->key);
                cache_.remove(nodeToRemove);
            }
            cache_.push(key, value);
            cache_access_[key] = cache_.tail;
        }
    }

private:
    std::map<int, node*> cache_access_;
    DoublyLinkedList cache_;
    uint64_t capacity_;
};


int main() {
    LRUCache cache(2); // cache for two nodes
    
    cache.put(1, 1); // cache: {1}
    cache.put(2, 2); // cache: {1, 2}
    std::cout << cache.get(1) << std::endl; // Output: 1, cache: {2, 1}
    
    cache.put(3, 3); // Delete key 2, cache: {1, 3}
    std::cout << cache.get(2) << std::endl; // Output -1

    cache.put(4, 4); // Delete key 1, cache: {3, 4}
    std::cout << cache.get(1) << std::endl; // Output -1
    std::cout << cache.get(3) << std::endl; // Output 3
    std::cout << cache.get(4) << std::endl; // Output 4

    return 0;
}