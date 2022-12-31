#ifndef AVL_TREE_H
#define AVL_TREE_H
#include <cassert>
#include <iostream>
#include <queue>

template <typename T>
struct AVLNode {
    // the default access mode and default inheritance mode are public
    T value;
    int balance;
    AVLNode *left, *right, *parent;
    // kostruktor domyślny
    AVLNode() : value(T()), balance(0),
                left(nullptr), right(nullptr), parent(nullptr) {}
    AVLNode(const T &item) : value(item), balance(0), left(nullptr), right(nullptr), parent(nullptr) {}
    AVLNode(const T &item, AVLNode *p) : value(item), balance(0), left(nullptr), right(nullptr), parent(p) {}
    ~AVLNode() {} // destruktor
};

template <typename T>
class AVLTree {
public:
    AVLNode<T> *root;

public:
    AVLTree() : root(nullptr) {}
    AVLTree(AVLTree &other);
    // ~AVLTree() { clear(); } // trzeba wyczyscic
    bool empty() const { return root == nullptr; }
    T &top() {
        assert(root != nullptr);
        return root->value;
    } // podglad korzenia
    void insert(const T &item);
    void remove(const T &item);
    T *search(const T &item) const {
        auto ptr = search(root, item);
        return ((ptr == nullptr) ? nullptr : &(ptr->value));
    }
    void preorder() { preorder(root); }
    void inorder() { inorder(root); }
    void postorder() { postorder(root); }
    void bfs(); // przejscie poziomami (wszerz)

    T *find_min() const { return (root == nullptr) ? nullptr : find_min(root); }
    T *find_max() const { return (root == nullptr) ? nullptr : find_max(root); }

    void clear() {
        clear(root);
        root = nullptr;
    }

    void display() { display(root, 0); }
    // testing
    bool equals(std::initializer_list<T> other);

    virtual void visit(AVLNode<T> *node) {
        assert(node != nullptr);
        std::cout << "visiting " << node->value <<" node address: "<<node << " node parent: "<< node->parent<< std::endl;
    }

private:
    AVLNode<T> *rotateLeft(AVLNode<T> *a);
    AVLNode<T> *rotateRight(AVLNode<T> *a);
    AVLNode<T> *rotateLeftThenRight(AVLNode<T> *n);
    AVLNode<T> *rotateRightThenLeft(AVLNode<T> *n);
    AVLNode<T> *search(AVLNode<T> *node, const T &item) const;
    AVLNode<T> *deep_copy(AVLNode<T> *node);

    T *find_min(AVLNode<T> *node) const;
    T *find_max(AVLNode<T> *node) const;

    void preorder_testing(AVLNode<T> *node, std::vector<T> &v);
    void clear(AVLNode<T> *node);
    void rebalance(AVLNode<T> *n);
    int height(AVLNode<T> *n);
    void setBalance(AVLNode<T> *n);
    void printBalance(AVLNode<T> *n);
    void display(AVLNode<T> *node, int level);
    void inorder(AVLNode<T> *node);
    void preorder(AVLNode<T> *node);
    void postorder(AVLNode<T> *node);

};

template <typename T>
AVLTree<T>::AVLTree(AVLTree<T> &other) {
    this->root = deep_copy(other.root);
}
template <typename T>
AVLNode<T>* AVLTree<T>::deep_copy(AVLNode<T> *node) {
    if (node == nullptr) return nullptr;

    AVLNode<T> *newNode = new AVLNode<T>(node->value);
    newNode->balance = node->balance;

    newNode->left = deep_copy(node->left);
    if (newNode->left != nullptr)
        newNode->left->parent = newNode;
    newNode->right = deep_copy(node->right);
    if (newNode->right != nullptr) 
        newNode->right->parent = newNode;

    return newNode;
}

template <typename T>
void AVLTree<T>::insert(const T &item) {
    if (root == nullptr) {
        root = new AVLNode<T>(item, NULL);
        return;
    }
    AVLNode<T> *n = root, *parent;
    bool goLeft;

    do {
        if (n->value == item)
            return;
        parent = n;
        goLeft = n->value > item;
        n = goLeft ? n->left : n->right;
    } while (n != nullptr);

    if (goLeft) {
        parent->left = new AVLNode<T>(item, parent);
    } else {
        parent->right = new AVLNode<T>(item, parent);
    }
    rebalance(parent);
}

template <typename T>
void AVLTree<T>::bfs() {
    if (root == nullptr)
        return;
    std::queue<AVLNode<T> *> nodesQueue;
    AVLNode<T> *node = root;
    nodesQueue.push(node);

    while (!nodesQueue.empty()) {
        node = nodesQueue.front();
        nodesQueue.pop();
        visit(node);
        if (node->left != nullptr)
            nodesQueue.push(node->left);
        if (node->right != nullptr)
            nodesQueue.push(node->right);
    }
}

template <typename T>
AVLNode<T> *AVLTree<T>::rotateLeft(AVLNode<T> *node) {
    AVLNode<T> *b = node->right;
    b->parent = node->parent;
    node->right = b->left;

    if (node->right != nullptr) {
        node->right->parent = node;
    }
    b->left = node;
    node->parent = b;

    if (b->parent != nullptr) {
        if (b->parent->right == node) {
            b->parent->right = b;
        } else {
            b->parent->left = b;
        }
    }
    setBalance(node);
    setBalance(b);
    return b;
}

template <typename T>
AVLNode<T> *AVLTree<T>::rotateRight(AVLNode<T> *node) {
    AVLNode<T> *b = node->left;
    b->parent = node->parent;
    node->left = b->right;

    if (node->left != nullptr)
        node->left->parent = node;

    b->right = node;
    node->parent = b;

    if (b->parent != nullptr) {
        if (b->parent->right == node) {
            b->parent->right = b;
        } else {
            b->parent->left = b;
        }
    }

    setBalance(node);
    setBalance(b);
    return b;
}

template <typename T>
AVLNode<T> *AVLTree<T>::rotateLeftThenRight(AVLNode<T> *node) {
    node->left = rotateLeft(node->left);
    return rotateRight(node);
}

template <typename T>
AVLNode<T> *AVLTree<T>::rotateRightThenLeft(AVLNode<T> *node) {
    node->right = rotateRight(node->right);
    return rotateLeft(node);
}

template <typename T>
AVLNode<T> *AVLTree<T>::search(AVLNode<T> *node, const T &item) const {
    if (node == nullptr || node->value == item) {
        return node;
    } else if (item < node->value) {
        return search(node->left, item);
    } else {
        return search(node->right, item);
    }
}

template <typename T>
void AVLTree<T>::clear(AVLNode<T> *node) {
    if (node) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

template <typename T>
T *AVLTree<T>::find_min(AVLNode<T> *node) const {
    while (node->left) {
        node = node->left;
    }
    return &node->value;
}

template <typename T>
T *AVLTree<T>::find_max(AVLNode<T> *node) const {
    while (node->right) {
        node = node->right;
    }
    return &node->value;
}

template <class T>
void AVLTree<T>::remove(const T &item) {
    if (root == nullptr)
        return;

    AVLNode<T>
        *node       = root,
        *parent  = root,
        *delNode = NULL,
        *child   = root;

    while (child != NULL) {
        parent = node;
        node = child;
        child = item >= node->value ? node->right : node->left;
        if (item == node->value)
            delNode = node;
    }

    if (delNode != NULL) {
        delNode->value = node->value;

        child = node->value != NULL ? node->left : node->right;

        if (root->value == item) {
            root = child;
        }
        else {
            if (parent->left == node) {
                parent->left = child;
            }
            else {
                parent->right = child;
            }

            rebalance(parent);
        }
    }
}

template <typename T>
void AVLTree<T>::rebalance(AVLNode<T> *node) {
    setBalance(node);

    if (node->balance == -2) {
        if (height(node->left->left) >= height(node->left->right))
            node = rotateRight(node);
        else
            node = rotateLeftThenRight(node);
    } else if (node->balance == 2) {
        if (height(node->right->right) >= height(node->right->left)) {
            node = rotateLeft(node);

        } else {
            node = rotateRightThenLeft(node);
        }
    }

    if (node->parent != nullptr) {
        rebalance(node->parent);
    } else {
        root = node;
    }
}

template <typename T>
int AVLTree<T>::height(AVLNode<T> *n) {
    if (n == nullptr)
        return -1;
    return 1 + std::max(height(n->left), height(n->right));
}

template <typename T>
void AVLTree<T>::setBalance(AVLNode<T> *node) {
    node->balance = height(node->right) - height(node->left);
}

template <typename T>
void AVLTree<T>::display(AVLNode<T> *node, int level) {
    if (node == nullptr)
        return;
    display(node->right, level + 1);
    std::cout << std::string(3 * level, ' ') << node->value << "(" << node->balance << ")" << std::endl;
    display(node->left, level + 1);
}
template <typename T>
bool AVLTree<T>::equals(std::initializer_list<T> other) {
    std::vector<T> storage;

    preorder_testing(root, storage);

    if (storage.size() != other.size())
        return false;

    int i = 0;
    for (T el : other) {
        if (el != storage.at(i))
            return false;
        i++;
    }
    return true;
}

template <typename T>
void AVLTree<T>::preorder_testing(AVLNode<T> *node, std::vector<T> &v) {
    if (node == nullptr)
        return;
    v.push_back(node->value);
    preorder_testing(node->left, v);
    preorder_testing(node->right, v);
}

template <typename T>
void AVLTree<T>::inorder(AVLNode<T> *node) {
    if (node == nullptr)
        return;
    inorder(node->left);
    visit(node);
    inorder(node->right);
}

template <typename T>
void AVLTree<T>::preorder(AVLNode<T> *node) {
    if (node == nullptr)
        return;
    visit(node);
    preorder(node->left);
    preorder(node->right);
}

template <typename T>
void AVLTree<T>::postorder(AVLNode<T> *node) {
    if (node == nullptr)
        return;
    postorder(node->left);
    postorder(node->right);
    visit(node);
}

#endif
