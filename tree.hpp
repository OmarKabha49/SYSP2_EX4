#ifndef TREE_HPP
#define TREE_HPP

#include "node.hpp"
#include <queue>
#include <stack>
#include <stdexcept>
#include <iostream>

using namespace std;

template<typename T, int K = 2>
class Tree {
private:
    shared_ptr<Node<T>> root;
    int max_children;

public:
    Tree();
    void add_root(const Node<T>& node);
    void add_sub_node(const Node<T>& parent_node, const Node<T>& child_node);
    shared_ptr<Node<T>> find_node(shared_ptr<Node<T>> current, const T& value);

    class PreOrderIterator {
    private:
        stack<shared_ptr<Node<T>>> node_stack;
    public:
        PreOrderIterator(shared_ptr<Node<T>> root);
        bool operator!=(const PreOrderIterator& other) const;
        PreOrderIterator& operator++();
        shared_ptr<Node<T>> operator*() const;
        shared_ptr<Node<T>> operator->() const;
    };

    class PostOrderIterator {
    private:
        stack<shared_ptr<Node<T>>> node_stack;
        shared_ptr<Node<T>> last_visited;
    public:
        PostOrderIterator(shared_ptr<Node<T>> root);
        bool operator!=(const PostOrderIterator& other) const;
        PostOrderIterator& operator++();
        shared_ptr<Node<T>> operator*() const;
        shared_ptr<Node<T>> operator->() const;
    };

    class InOrderIterator {
    private:
        stack<shared_ptr<Node<T>>> node_stack;
    public:
        InOrderIterator(shared_ptr<Node<T>> root);
        bool operator!=(const InOrderIterator& other) const;
        InOrderIterator& operator++();
        shared_ptr<Node<T>> operator*() const;
        shared_ptr<Node<T>> operator->() const;
    };

    class BFSIterator {
    private:
        queue<shared_ptr<Node<T>>> node_queue;
    public:
        BFSIterator(shared_ptr<Node<T>> root);
        bool operator!=(const BFSIterator& other) const;
        BFSIterator& operator++();
        shared_ptr<Node<T>> operator*() const;
        shared_ptr<Node<T>> operator->() const;
    };

    class DFSIterator {
    private:
        stack<shared_ptr<Node<T>>> node_stack;
    public:
        DFSIterator(shared_ptr<Node<T>> root);
        bool operator!=(const DFSIterator& other) const;
        DFSIterator& operator++();
        shared_ptr<Node<T>> operator*() const;
        shared_ptr<Node<T>> operator->() const;
    };

    PreOrderIterator begin_pre_order();
    PreOrderIterator end_pre_order();

    PostOrderIterator begin_post_order();
    PostOrderIterator end_post_order();

    InOrderIterator begin_in_order();
    InOrderIterator end_in_order();

    BFSIterator begin_bfs_scan();
    BFSIterator end_bfs_scan();

    DFSIterator begin_dfs_scan();
    DFSIterator end_dfs_scan();

    // Enable range-based for loop with BFS traversal
    BFSIterator begin();
    BFSIterator end();

    // Friend function to enable cout << tree
    template<typename U, int V>
    friend ostream& operator<<(ostream& os, const Tree<U, V>& tree);
};

#endif // TREE_HPP
