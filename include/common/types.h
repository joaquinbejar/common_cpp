//
// Created by Joaquin Bejar Garcia on 6/1/24.
//

#ifndef COMMON_TYPES_H
#define COMMON_TYPES_H

#include <iostream>
#include <atomic>
#include <memory>

namespace common::types {
    template<typename K, typename V, std::size_t N>
    class lock_free_hash_table {
    private:
        struct Node {
            K key;
            V value;
            Node *next;

            Node(const K &k, const V &v) : key(k), value(v),
                                           next(nullptr) {}
        };

        std::atomic<Node *> buckets[N];
    public:
        lock_free_hash_table() {
            for (std::size_t i = 0; i < N; ++i) {
                buckets[i].store(nullptr);
            }
        }

        bool insert(const K &key, const V &value) {
            std::size_t hash = std::hash<K>()(key) % N;
            Node *newNode = new Node(key, value);
            while (true) {
                Node *head = buckets[hash].load();
                newNode->next = head;
                if (buckets[hash].compare_exchange_weak(head, newNode)) {
                    return true;
                }
                // if compare_exchange_weak fails, head is
                // updated to the new value
                // we need to update the next pointer of
                // newNode and try again
                newNode->next = nullptr;
            }
        }

        bool find(const K &key, V &value) {
            std::size_t hash = std::hash<K>()(key) % N;
            Node *node = buckets[hash].load();
            while (node != nullptr) {
                if (node->key == key) {
                    value = node->value;
                    return true;
                }
                node = node->next;
            }
            return false;
        }
    };


    template<typename T>
    class lock_free_queue {
    private:
        struct node {
            T data;
            std::atomic<node *> next;

            explicit node(const T &value) : data(value), next(nullptr) {}
        };

        std::atomic<node *> head;
        std::atomic<node *> tail;
    public:
        lock_free_queue() : head(new node(T())),
                            tail(head.load()) {}

        void push(const T &value) {
            node *new_node = new node(value);
            node *old_tail = tail.exchange(new_node,
                                           std::memory_order_acq_rel);
            old_tail->next = new_node;
        }

        bool pop(T &value) {
            node *old_head = head.load(
                    std::memory_order_relaxed);
            while (true) {
                node *next = old_head->next.load(
                        std::memory_order_acquire);
                if (!next) {
                    return false;
                }
                if (head.compare_exchange_weak(old_head, next, std::memory_order_release)) {
                    value = next->data;
                    delete old_head;
                    return true;
                }
            }
        }
    };


    template<typename T>
    class lock_free_stack {
    private:
        struct node {
            T data_;
            std::atomic<node *> next_;

            explicit node(T value) : data_(std::move(value)),
                                     next_(nullptr) {}
        };

        std::atomic<node *> head_;

    public:
        lock_free_stack() : head_(nullptr) {}

        ~lock_free_stack() {
            while (pop()); // Vaciar la pila
        }

        void push(T data) {
            node* new_elem = new node(std::move(data));
            node* old_head = head_.load();
            new_elem->next_ = old_head;
            while (!std::atomic_compare_exchange_weak(&head_, &old_head, new_elem)) {
                new_elem->next_ = old_head;
                old_head = head_.load();
            }
        }

        std::unique_ptr<T> pop() {
            node *old_head = head_.load();
            while (old_head && !std::atomic_compare_exchange_weak(&head_,
                                                                  &old_head, old_head->next_.load())) {
                old_head = head_.load();
            }
            if (old_head) {
                std::unique_ptr<T> res(new T(std::move(old_head->data_)));
                delete old_head;
                return res;
            }
            return nullptr;
        }
    };


    template<typename T>
    class lock_free_set {
    private:
        struct Node {
            T value;
            Node *next;

            Node(const T &v) : value(v), next(nullptr) {}
        };

        std::atomic<Node *> head;
    public:
        lock_free_set() : head(nullptr) {}

        bool insert(const T &value) {
            Node *newNode = new Node(value);
            while (true) {
                Node *curHead = head.load();
                newNode->next = curHead;
                if (head.compare_exchange_weak(curHead, newNode)) {
                    return true;
                }
                newNode->next = nullptr;
            }
        }

        bool contains(const T &value) {
            Node *curNode = head.load();
            while (curNode != nullptr) {
                if (curNode->value == value) {
                    return true;
                }
                curNode = curNode->next;
            }
            return false;
        }
    };

}
#endif //COMMON_TYPES_H
