#ifndef RANDOM_BINARY_TREE
#define RANDOM_BINARY_TREE
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <queue>
#include <stack>

template <typename T>
struct BSTNode {
    T value;
    BSTNode *left, *right;
    BSTNode() : value(T()), left(nullptr), right(nullptr) {}
    BSTNode(const T &item) : value(item), left(nullptr), right(nullptr) {}
    ~BSTNode() {} // destruktor
};

template <typename T>
class RandomBinaryTree {
    BSTNode<T> *root;

  public:
    RandomBinaryTree() : root(nullptr) {} // konstruktor domyślny
    ~RandomBinaryTree() { clear(); }      // trzeba wyczyścić
    bool empty() const { return root == nullptr; }
    T &top() {
        assert(root != nullptr);
        return root->value;
    } // podgląd korzenia
    void insert(const T &item) { root = insert(root, item); }
    // void remove(const T& item); // na razie nie usuwamy elementów
    T *search(const T &item) const {
        auto ptr = search(root, item);
        return ((ptr == nullptr) ? nullptr : &(ptr->value));
    }
    void preorder() { preorder(root); }
    void inorder() { inorder(root); }
    void postorder() { postorder(root); }
    void iter_preorder();
    void iter_inorder();   // trudne
    void iter_postorder(); // trudne
    void bfs();            // przejście poziomami (wszerz)
    void clear() {
        clear(root);
        root = nullptr;
    }

    void display() { display(root, 0); }
    unsigned int calc_leafs() { return calc_leafs(root); }
    unsigned int calc_leafs_iter() { return iter_calc_leafs(root); }
    unsigned int calc_total() { return calc_total(root); }
    unsigned int iter_calc_total() { return iter_calc_total(root); }
    T find_min() { return find_min(root); }
    T find_max() { return find_max(root); }
    T iter_find_min() { return iter_find_min(root); }
    T iter_find_max() { return iter_find_max(root); }

  private:
    void clear(BSTNode<T> *node);
    BSTNode<T> *insert(BSTNode<T> *node, const T &item); // zwraca nowy korzeń
    BSTNode<T> *search(BSTNode<T> *node, const T &item) const;
    void preorder(BSTNode<T> *node);
    void inorder(BSTNode<T> *node);
    void postorder(BSTNode<T> *node);
    void display(BSTNode<T> *node, int level);
    virtual void visit(BSTNode<T> *node) {
        assert(node != nullptr);
        std::cout << "visiting " << node->value << std::endl;
    }

    unsigned int calc_leafs(BSTNode<T> *node);
    unsigned int iter_calc_leafs(BSTNode<T> *node);
    unsigned int calc_total(BSTNode<T> *node);
    unsigned int iter_calc_total(BSTNode<T> *node);
    T find_min(BSTNode<T> *node);
    T find_max(BSTNode<T> *node);
    T iter_find_min(BSTNode<T> *node);
    T iter_find_max(BSTNode<T> *node);
};

template <typename T>
void RandomBinaryTree<T>::clear(BSTNode<T> *node) {
    if (node == nullptr)
        return;
    clear(node->left);
    clear(node->right);
    delete node;
}
template <typename T>
void RandomBinaryTree<T>::display(BSTNode<T> *node, int level) {
    if (node == nullptr)
        return;
    display(node->right, level + 1);
    std::cout << std::string(3 * level, ' ') << node->value << std::endl;
    display(node->left, level + 1);
}

template <typename T>
BSTNode<T> *RandomBinaryTree<T>::insert(BSTNode<T> *node, const T &item) {
    if (node == nullptr) {
        return new BSTNode<T>(item);
    }
    if (std::rand() % 2) { // można lepiej
        node->left = insert(node->left, item);
    } else {
        node->right = insert(node->right, item);
    }
    return node; // zwraca nowy korzen
}

template <typename T>
BSTNode<T> *RandomBinaryTree<T>::search(BSTNode<T> *node, const T &item) const {
    if (node == nullptr || node->value == item) {
        return node;
    }
    T *ptr;
    ptr = search(node->left, item);
    if (ptr == nullptr) {
        ptr = search(node->right, item);
    }
    return ptr;
}

template <typename T>
unsigned int RandomBinaryTree<T>::calc_leafs(BSTNode<T> *node) {
    if (node == nullptr)
        return 0;
    if (node->left == nullptr && node->right == nullptr)
        return 1;
    else
        return calc_leafs(node->left) + calc_leafs(node->right);
}

template <typename T>
unsigned int RandomBinaryTree<T>::iter_calc_leafs(BSTNode<T> *node) {
    if (node == nullptr)
        return 0;
    std::queue<BSTNode<T> *> nodesQueue;
    nodesQueue.push(node);

    unsigned int count = 0;

    while (!nodesQueue.empty()) {
        node = nodesQueue.front();
        nodesQueue.pop();
        if (node->left != nullptr)
            nodesQueue.push(node->left);
        if (node->right != nullptr)
            nodesQueue.push(node->right);
        if (node->left == nullptr && node->right == nullptr)
            count++;
    }
    return count;
}
template <typename T>
unsigned int RandomBinaryTree<T>::calc_total(BSTNode<T> *node) {
    if (node == nullptr)
        return 0;
    return (node->value + calc_total(node->left) + calc_total(node->right));
}
template <typename T>
unsigned int RandomBinaryTree<T>::iter_calc_total(BSTNode<T> *node) {
    if (root == nullptr)
        return 0;
    unsigned int count = 0;
    std::stack<BSTNode<T> *> nodeStack;
    nodeStack.push(node);
    while (!nodeStack.empty()) {
        node = nodeStack.top();
        nodeStack.pop();
        count += node->value;
        if (node->right != nullptr)
            nodeStack.push(node->right);
        if (node->left != nullptr)
            nodeStack.push(node->left);
    }
    return count;
}
template <typename T>
T RandomBinaryTree<T>::find_min(BSTNode<T> *node) {
    if (node == nullptr)
        return std::numeric_limits<T>::max();
    T minValue = node->value;
    T left = find_min(node->left);
    T right = find_min(node->right);
    if (left < minValue)
        minValue = left;
    if (right < minValue)
        minValue = right;
    return minValue;
}

template <typename T>
T RandomBinaryTree<T>::find_max(BSTNode<T> *node) {
    if (node == nullptr)
        return std::numeric_limits<T>::min();
    T maxValue = node->value;
    T left = find_max(node->left);
    T right = find_max(node->right);
    if (left > maxValue)
        maxValue = left;
    if (right > maxValue)
        maxValue = right;
    return maxValue;
}
template <typename T>
T RandomBinaryTree<T>::iter_find_min(BSTNode<T> *node) {
    assert(node != nullptr);
    std::stack<BSTNode<T> *> S; // wskaźniki do węzłów
    T minValue = std::numeric_limits<T>::max();
    S.push(node);
    while (!S.empty()) {
        node = S.top(); // podglądamy
        S.pop();        // usuwamy ze stosu
        if (node->value < minValue)
            minValue = node->value;
        if (node->right != nullptr) // najpierw prawe poddrzewo!
            S.push(node->right);
        if (node->left != nullptr)
            S.push(node->left);
    }
    return minValue;
}

template <typename T>
T RandomBinaryTree<T>::iter_find_max(BSTNode<T> *node) {
    assert(node != nullptr);
    std::stack<BSTNode<T> *> S; // wskaźniki do węzłów
    T maxValue = std::numeric_limits<T>::min();
    S.push(node);
    while (!S.empty()) {
        node = S.top(); // podglądamy
        S.pop();        // usuwamy ze stosu
        if (node->value > maxValue)
            maxValue = node->value;
        if (node->right != nullptr) // najpierw prawe poddrzewo!
            S.push(node->right);
        if (node->left != nullptr)
            S.push(node->left);
    }
    return maxValue;
}
#endif
