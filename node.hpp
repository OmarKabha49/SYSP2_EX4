#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include <memory>

using namespace std;

template<typename T>
class Node {
public:
    T value;
    vector<shared_ptr<Node<T>>> children;

    Node(const T& val) : value(val), children() {}

    T get_value() const {
        return value;
    }
};

#endif // NODE_HPP
