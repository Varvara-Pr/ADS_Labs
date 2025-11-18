#pragma once
#include <iostream>
#include <stdexcept>
#include <random>

template <typename T>
struct Node {
    T data;
    Node* prev, * next;

    Node(T value) : data(value), prev(nullptr), next(nullptr) {}
};

template <typename T>
class LinkedList {
private:
    Node<T>* _head;
    size_t _size;

public:
    LinkedList() : _head(nullptr), _size(0) {}

    LinkedList(const LinkedList& other) : _head(nullptr), _size(other._size)
    {
        if (!other._head) return;

        _head = new Node<T>(other._head->data);
        Node<T>* iter = _head;
        Node<T>* iter_other = other._head->next;

        while (iter_other != other._head)
        {
            Node<T>* new_node = new Node<T>(iter_other->data);

            iter->next = new_node;
            new_node->prev = iter;
            new_node->next = _head;

            iter = new_node;
            iter_other = iter_other->next;
        }

        _head->prev = iter;
    }

    LinkedList(size_t count, T min_val, T max_val, unsigned int seed) : _head(nullptr), _size(0) {

        if (min_val > max_val) {
            throw std::invalid_argument("min_val > max_val");
        }
        if (count == 0) return;

        std::default_random_engine gen(seed);

        if constexpr (std::is_integral_v<T>) {

            std::uniform_int_distribution<T> dist(min_val, max_val);
            for (size_t i = 0; i < count; ++i) {
                push_tail(dist(gen));
            }
        }
        else if constexpr (std::is_floating_point_v<T>) {

            std::uniform_real_distribution<T> dist(min_val, max_val);
            for (size_t i = 0; i < count; ++i) {
                push_tail(dist(gen));
            }
        }
        else {
            for (size_t i = 0; i < count; ++i) {
                push_tail(min_val);
            }
        }
    }

    ~LinkedList() {
        while (_size > 0) {
            pop_head();
        }
    }

    void push_tail(const T& value) {
        Node<T>* node = new Node<T>(value);

        if (_head == nullptr) {
            node->next = node;
            node->prev = node;
            _head = node;
        }
        else {
            Node<T>* tail = _head->prev;
            tail->next = node;
            node->prev = tail;
            node->next = _head;
            _head->prev = node;
        }

        ++_size;
    }

    void push_head(const T& value) {
        push_tail(value);
        _head = _head->prev;
    }

    void pop_head() {
        if (_head == nullptr) {
            throw std::out_of_range("pop from empty list");
        }

        Node<T>* node = _head;

        if (_size == 1) {
            _head = nullptr;
        }
        else {
            Node<T>* tail = _head->prev;
            _head = _head->next;
            _head->prev = tail;
            tail->next = _head;
        }

        delete node;
        --_size;
    }

    void pop_tail() {
        if (_head == nullptr) {
            throw std::out_of_range("pop from empty list");
        }
        _head = _head->prev;
        pop_head();
    }

    size_t size() const {
        return _size;
    }
};