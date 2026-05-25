#ifndef MYCONTAINER_H
#define MYCONTAINER_H

#include <cstddef>
#include <iterator>
#include <stdexcept>
#include <algorithm>
#include <functional>

template <typename T, typename Compare = std::less<T>>
class MyContainer {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        
        Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
    };
    
    Node* head;
    Node* tail;
    size_t count;
    Compare comp;
    
    void insertSorted(Node* newNode) {
        if (!head) {
            head = tail = newNode;
            return;
        }
        
        if (comp(newNode->data, head->data)) {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
            return;
        }
        
        if (!comp(newNode->data, tail->data)) {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
            return;
        }
        
        Node* current = head;
        while (current && comp(current->data, newNode->data)) {
            current = current->next;
        }
        
        if (current) {
            newNode->prev = current->prev;
            newNode->next = current;
            if (current->prev) {
                current->prev->next = newNode;
            }
            current->prev = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void removeNode(Node* node) {
        if (!node) return;
        
        if (node->prev) {
            node->prev->next = node->next;
        } else {
            head = node->next;
        }
        
        if (node->next) {
            node->next->prev = node->prev;
        } else {
            tail = node->prev;
        }
        
        delete node;
        count--;
    }
    
    Node* findNode(const T& value) const {
        Node* current = head;
        while (current) {
            if (current->data == value) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }
    
public:
    class Iterator {
    private:
        Node* ptr;
        
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;
        
        Iterator(Node* p = nullptr) : ptr(p) {}
        
        reference operator*() const { return ptr->data; }
        pointer operator->() const { return &(ptr->data); }
        
        Iterator& operator++() {
            if (ptr) ptr = ptr->next;
            return *this;
        }
        
        Iterator operator++(int) {
            Iterator tmp = *this;
            if (ptr) ptr = ptr->next;
            return tmp;
        }
        
        Iterator& operator--() {
            if (ptr) ptr = ptr->prev;
            return *this;
        }
        
        Iterator operator--(int) {
            Iterator tmp = *this;
            if (ptr) ptr = ptr->prev;
            return tmp;
        }
        
        bool operator==(const Iterator& other) const { return ptr == other.ptr; }
        bool operator!=(const Iterator& other) const { return ptr != other.ptr; }
    };
    
    class ConstIterator {
    private:
        const Node* ptr;
        
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;
        
        ConstIterator(const Node* p = nullptr) : ptr(p) {}
        
        reference operator*() const { return ptr->data; }
        pointer operator->() const { return &(ptr->data); }
        
        ConstIterator& operator++() {
            if (ptr) ptr = ptr->next;
            return *this;
        }
        
        ConstIterator operator++(int) {
            ConstIterator tmp = *this;
            if (ptr) ptr = ptr->next;
            return tmp;
        }
        
        ConstIterator& operator--() {
            if (ptr) ptr = ptr->prev;
            return *this;
        }
        
        ConstIterator operator--(int) {
            ConstIterator tmp = *this;
            if (ptr) ptr = ptr->prev;
            return tmp;
        }
        
        bool operator==(const ConstIterator& other) const { return ptr == other.ptr; }
        bool operator!=(const ConstIterator& other) const { return ptr != other.ptr; }
    };
    
    MyContainer() : head(nullptr), tail(nullptr), count(0) {}
    
    MyContainer(const MyContainer& other) : head(nullptr), tail(nullptr), count(0) {
        Node* current = other.head;
        while (current) {
            push_back(current->data);
            current = current->next;
        }
    }
    
    MyContainer& operator=(const MyContainer& other) {
        if (this != &other) {
            clear();
            Node* current = other.head;
            while (current) {
                push_back(current->data);
                current = current->next;
            }
        }
        return *this;
    }
    
    ~MyContainer() {
        clear();
    }
    
    void push_back(const T& value) {
        Node* newNode = new Node(value);
        insertSorted(newNode);
    }
    
    void pop_back() {
        if (tail) {
            removeNode(tail);
        }
    }
    
    void push_front(const T& value) {
        push_back(value);
    }
    
    void pop_front() {
        if (head) {
            removeNode(head);
        }
    }
    
    bool remove(const T& value) {
        Node* node = findNode(value);
        if (node) {
            removeNode(node);
            return true;
        }
        return false;
    }
    
    T& front() {
        if (!head) throw std::out_of_range("Container is empty");
        return head->data;
    }
    
    const T& front() const {
        if (!head) throw std::out_of_range("Container is empty");
        return head->data;
    }
    
    T& back() {
        if (!tail) throw std::out_of_range("Container is empty");
        return tail->data;
    }
    
    const T& back() const {
        if (!tail) throw std::out_of_range("Container is empty");
        return tail->data;
    }
    
    T& operator[](size_t index) {
        if (index >= count) throw std::out_of_range("Index out of range");
        Node* current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }
    
    const T& operator[](size_t index) const {
        if (index >= count) throw std::out_of_range("Index out of range");
        Node* current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }
    
    bool contains(const T& value) const {
        return findNode(value) != nullptr;
    }
    
    size_t size() const { return count; }
    bool empty() const { return count == 0; }
    
    void clear() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        count = 0;
    }
    
    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }
    
    ConstIterator begin() const { return ConstIterator(head); }
    ConstIterator end() const { return ConstIterator(nullptr); }
    ConstIterator cbegin() const { return ConstIterator(head); }
    ConstIterator cend() const { return ConstIterator(nullptr); }
};

#endif