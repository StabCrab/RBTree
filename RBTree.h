#ifndef RBTREE_H
#define RBTREE_H
#include "cstdlib"
#include "stdexcept"

template<typename T>
class RBtree {
    class Node{
    public:
        Node(const size_t key, const T value) : key(key), value(value) {};
        const size_t key;
        T value;
        Node *left = nullptr, *right = nullptr;
    };

public:
    RBtree();

    RBtree(const RBtree &copyRBtree);

    RBtree(RBtree &&copyRBtree) noexcept;

    RBtree &operator=(const RBtree &otherRBtree);

    RBtree &operator=(RBtree &&otherRBtree) noexcept;

    ~RBtree();

    void add(std::size_t key, T value);

    void deleteFirstNodeByKey(std::size_t key);

    void deleteAllNodesByKey(std::size_t key);

    Node &find(std::size_t key);

    Node &findNodeWithMaxKey();

    Node &findNodeWithMinKey();

    std::size_t size() const;

    Node *node();

    const Node *node() const;

    bool isEmpty();

private:
    std::size_t _size;
    Node *root;

    Node &privateFind(std::size_t key, Node* currentNode);

};

template<typename T>
RBtree<T>::RBtree() : _size(0), root(nullptr) {}

template<typename T>
RBtree<T>::RBtree(const RBtree &copyRBtree) :
        root(new Node(copyRBtree.root)),
        _size(copyRBtree._size) {}

template<typename T>
RBtree<T>::RBtree(RBtree &&copyRBtree) noexcept {
    root = copyRBtree.root;
    _size = copyRBtree._size;

    copyRBtree.root = nullptr;
}

template<typename T>
RBtree<T> &RBtree<T>::operator=(const RBtree &otherRBtree) {
    if (this == &otherRBtree) {
        return *this;
    }

    root = new Node(otherRBtree.root);
    _size = otherRBtree._size;

    return *this;
}

template<typename T>
RBtree<T> &RBtree<T>::operator=(RBtree &&otherRBtree) noexcept {
    if (this == &otherRBtree) {
        return *this;
    }

    root = otherRBtree.root;
    _size = otherRBtree._size;

    otherRBtree.root = nullptr;

    return *this;
}

template<typename T>
RBtree<T>::~RBtree() {
    delete root;
    root = nullptr;
};

template<typename T>
typename RBtree<T>::Node &RBtree<T>::find(std::size_t key)
{
    if (root == nullptr)
    {
        throw std::invalid_argument("RBtree is empty");
    }
    return privateFind(key, root);
}

template<typename T>
typename RBtree<T>::Node &RBtree<T>::findNodeWithMaxKey() {
    if (root == nullptr) {
        throw std::invalid_argument("RBtree is empty");
    }

    Node *bufNode = root->left;
    while (bufNode->left != nullptr) {
        bufNode = bufNode->left;
    }
    return bufNode;
}

template<typename T>
typename RBtree<T>::Node &RBtree<T>::findNodeWithMinKey() {
    if (root == nullptr) {
        throw std::invalid_argument("RBtree is empty");
    }

    Node *bufNode = root->right;
    while (bufNode->right != nullptr) {
        bufNode = bufNode->right;
    }
    return bufNode;
}

template<typename T>
void RBtree<T>::add(const std::size_t key, const T value)
{
    if (_size == 0)
    {
        root = new Node(key, value);
    }
    else{
        Node *bufNode = root;
        while (true)
        {
            if (key < bufNode->key) {
                if (bufNode->left == nullptr)
                {
                    bufNode->left = new Node(key, value);
                    break;
                }
                else{
                    bufNode = bufNode->left;
                    continue;
                }
            }
            else
                {
                if (bufNode->right == nullptr)
                {
                    bufNode->right = new Node(key, value); // TODO: проверка на утечку памяти
                    break;
                }
                else {
                    bufNode = bufNode->right;
                    continue;
                }
            }
        }
    }
    _size++;
}

template<typename T>
void RBtree<T>::deleteFirstNodeByKey(const std::size_t key)
{
    Node *bufNode = find(key);
    delete bufNode;
    // TODO: проверка корректности
}

template<typename T>
void RBtree<T>::deleteAllNodesByKey(const std::size_t key)
{
    try {
        Node *bufNode;
        while (true) {
            bufNode = find(key);
            delete bufNode;
        }
    }
    catch (...) {
        // TODO: добавить exception и обдумать конструкцию
    }
}

template<typename T>
std::size_t RBtree<T>::size() const
{
    return _size;
}

template<typename T>
typename RBtree<T>::Node *RBtree<T>::node()
{
    return root;
}

template<typename T>
const typename RBtree<T>::Node *RBtree<T>::node() const
{
    return root;
}

template<typename T>
bool RBtree<T>::isEmpty()
{
    return !_size;
}

template<typename T>
typename RBtree<T>::Node &RBtree<T>::privateFind(std::size_t key, Node *currentNode)
{
    if (currentNode->key == key)
    {
        return *currentNode;
    }
    else if (currentNode->key > key)
    {
        return privateFind(key, currentNode->left);
    }
    else if (currentNode->key < key, currentNode->left)
    {
        return privateFind(key, currentNode->right);
    }
    else throw std::invalid_argument("Key not found");
}


#endif //RBTREE_H