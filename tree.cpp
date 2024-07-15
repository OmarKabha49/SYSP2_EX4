#include "tree.hpp"

// Definitions for Tree class methods
template<typename T, int K>
Tree<T, K>::Tree() : root(nullptr), max_children(K) {}

template<typename T, int K>
void Tree<T, K>::add_root(const Node<T>& node) {
    root = make_shared<Node<T>>(node);
}

template<typename T, int K>
void Tree<T, K>::add_sub_node(const Node<T>& parent_node, const Node<T>& child_node) {
    auto parent = find_node(root, parent_node.get_value());
    if (parent && parent->children.size() < max_children) {
        parent->children.push_back(make_shared<Node<T>>(child_node));
    } else {
        throw runtime_error("Parent node not found or maximum children reached");
    }
}

template<typename T, int K>
shared_ptr<Node<T>> Tree<T, K>::find_node(shared_ptr<Node<T>> current, const T& value) {
    if (!current) return nullptr;
    if (current->value == value) return current;
    for (auto& child : current->children) {
        auto found = find_node(child, value);
        if (found) return found;
    }
    return nullptr;
}

// Pre-order iterator implementation
template<typename T, int K>
Tree<T, K>::PreOrderIterator::PreOrderIterator(shared_ptr<Node<T>> root) {
    if (root) node_stack.push(root);
}

template<typename T, int K>
bool Tree<T, K>::PreOrderIterator::operator!=(const PreOrderIterator& other) const {
    return !node_stack.empty() || !other.node_stack.empty();
}

template<typename T, int K>
typename Tree<T, K>::PreOrderIterator& Tree<T, K>::PreOrderIterator::operator++() {
    auto current = node_stack.top();
    node_stack.pop();
    for (auto it = current->children.rbegin(); it != current->children.rend(); ++it) {
        node_stack.push(*it);
    }
    return *this;
}

template<typename T, int K>
shared_ptr<Node<T>> Tree<T, K>::PreOrderIterator::operator*() const {
    return node_stack.top();
}

template<typename T, int K>
shared_ptr<Node<T>> Tree<T, K>::PreOrderIterator::operator->() const {
    return node_stack.top();
}

template<typename T, int K>
typename Tree<T, K>::PreOrderIterator Tree<T, K>::begin_pre_order() {
    return PreOrderIterator(root);
}

template<typename T, int K>
typename Tree<T, K>::PreOrderIterator Tree<T, K>::end_pre_order() {
    return PreOrderIterator(nullptr);
}

// Post-order iterator implementation
template<typename T, int K>
Tree<T, K>::PostOrderIterator::PostOrderIterator(shared_ptr<Node<T>> root) {
    while (root) {
        node_stack.push(root);
        root = root->children.empty() ? nullptr : root->children[0];
    }
}

template<typename T, int K>
bool Tree<T, K>::PostOrderIterator::operator!=(const PostOrderIterator& other) const {
    return !node_stack.empty() || !other.node_stack.empty();
}

template<typename T, int K>
typename Tree<T, K>::PostOrderIterator& Tree<T, K>::PostOrderIterator::operator++() {
    auto current = node_stack.top();
    node_stack.pop();
    if (!node_stack.empty() && node_stack.top()->children.back() != current) {
        auto parent = node_stack.top();
        auto& siblings = parent->children;
        auto it = find(siblings.begin(), siblings.end(), current);
        ++it;
        for (; it != siblings.end(); ++it) {
            auto node = *it;
            while (node) {
                node_stack.push(node);
                node = node->children.empty() ? nullptr : node->children[0];
            }
        }
    }
    return *this;
}

template<typename T, int K>
shared_ptr<Node<T>> Tree<T, K>::PostOrderIterator::operator*() const {
    return node_stack.top();
}

template<typename T, int K>
shared_ptr<Node<T>> Tree<T, K>::PostOrderIterator::operator->() const {
    return node_stack.top();
}

template<typename T, int K>
typename Tree<T, K>::PostOrderIterator Tree<T, K>::begin_post_order() {
    return PostOrderIterator(root);
}

template<typename T, int K>
typename Tree<T, K>::PostOrderIterator Tree<T, K>::end_post_order() {
    return PostOrderIterator(nullptr);
}

// In-order iterator implementation (for binary trees only)
template<typename T, int K>
Tree<T, K>::InOrderIterator::InOrderIterator(shared_ptr<Node<T>> root) {
    while (root) {
        node_stack.push(root);
        root = root->children.empty() ? nullptr : root->children[0];
    }
}

template<typename T, int K>
bool Tree<T, K>::InOrderIterator::operator!=(const InOrderIterator& other) const {
    return !node_stack.empty() || !other.node_stack.empty();
}

template<typename T, int K>
typename Tree<T, K>::InOrderIterator& Tree<T, K>::InOrderIterator::operator++() {
    auto current = node_stack.top();
    node_stack.pop();
    if (current->children.size() > 1) {
        auto node = current->children[1];
        while (node) {
            node_stack.push(node);
            node = node->children.empty() ? nullptr : node->children[0];
        }
    }
    return *this;
}

template<typename T, int K>
shared_ptr<Node<T>> Tree<T, K>::InOrderIterator::operator*() const {
    return node_stack.top();
}

template<typename T, int K>
shared_ptr<Node<T>> Tree<T, K>::InOrderIterator::operator->() const {
    return node_stack.top();
}

template<typename T, int K>
typename Tree<T, K>::InOrderIterator Tree<T, K>::begin_in_order() {
    return InOrderIterator(root);
}

template<typename T, int K>
typename Tree<T, K>::InOrderIterator Tree<T, K>::end_in_order() {
    return InOrderIterator(nullptr);
}

// BFS iterator implementation
template<typename T, int K>
Tree<T, K>::BFSIterator::BFSIterator(shared_ptr<Node<T>> root) {
    if (root) node_queue.push(root);
}

template<typename T, int K>
bool Tree<T, K>::BFSIterator::operator!=(const BFSIterator& other) const {
    return !node_queue.empty() || !other.node_queue.empty();
}

template<typename T, int K>
typename Tree<T, K>::BFSIterator& Tree<T, K>::BFSIterator::operator++() {
    auto current = node_queue.front();
    node_queue.pop();
    for (auto& child : current->children) {
        node_queue.push(child);
    }
    return *this;
}

template<typename T, int K>
shared_ptr<Node<T>> Tree<T, K>::BFSIterator::operator*() const {
    return node_queue.front();
}

template<typename T, int K>
shared_ptr<Node<T>> Tree<T, K>::BFSIterator::operator->() const {
    return node_queue.front();
}

template<typename T, int K>
typename Tree<T, K>::BFSIterator Tree<T, K>::begin_bfs_scan() {
    return BFSIterator(root);
}

template<typename T, int K>
typename Tree<T, K>::BFSIterator Tree<T, K>::end_bfs_scan() {
    return BFSIterator(nullptr);
}

// DFS iterator implementation
template<typename T, int K>
Tree<T, K>::DFSIterator::DFSIterator(shared_ptr<Node<T>> root) {
    if (root) node_stack.push(root);
}

template<typename T, int K>
bool Tree<T, K>::DFSIterator::operator!=(const DFSIterator& other) const {
    return !node_stack.empty() || !other.node_stack.empty();
}

template<typename T, int K>
typename Tree<T, K>::DFSIterator& Tree<T, K>::DFSIterator::operator++() {
    auto current = node_stack.top();
    node_stack.pop();
    for (auto it = current->children.rbegin(); it != current->children.rend(); ++it) {
        node_stack.push(*it);
    }
    return *this;
}

template<typename T, int K>
shared_ptr<Node<T>> Tree<T, K>::DFSIterator::operator*() const {
    return node_stack.top();
}

template<typename T, int K>
shared_ptr<Node<T>> Tree<T, K>::DFSIterator::operator->() const {
    return node_stack.top();
}

template<typename T, int K>
typename Tree<T, K>::DFSIterator Tree<T, K>::begin_dfs_scan() {
    return DFSIterator(root);
}

template<typename T, int K>
typename Tree<T, K>::DFSIterator Tree<T, K>::end_dfs_scan() {
    return DFSIterator(nullptr);
}

// Implement begin() and end() for range-based for loops (BFS traversal)
template<typename T, int K>
typename Tree<T, K>::BFSIterator Tree<T, K>::begin() {
    return begin_bfs_scan();
}

template<typename T, int K>
typename Tree<T, K>::BFSIterator Tree<T, K>::end() {
    return end_bfs_scan();
}

// Output stream operator for Tree
template<typename T, int K>
ostream& operator<<(ostream& os, const Tree<T, K>& tree) {
    // Simple BFS-based tree output for demonstration
    queue<shared_ptr<Node<T>>> node_queue;
    if (tree.root) node_queue.push(tree.root);
    while (!node_queue.empty()) {
        auto current = node_queue.front();
        node_queue.pop();
        os << current->get_value() << " ";
        for (auto& child : current->children) {
            node_queue.push(child);
        }
    }
    return os;
}

// Explicit template instantiation
template class Tree<int>;
template class Tree<double>;
