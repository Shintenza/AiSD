#ifndef BST_H
#define BST_H
#include <cassert>
#include <iostream>
#include <limits>

template <typename T>
struct BSTNode {
    // the default access mode and default inheritance mode are public
    T value;
    BSTNode *left, *right;
    BSTNode *parent; // używane w pewnych zastosowaniach
    //  kostruktor domyślny
    BSTNode() : value(T()), left(nullptr), right(nullptr), parent(nullptr) {}
    // konstruktor zwykły
    BSTNode(const T &item) : value(item), left(nullptr), right(nullptr), parent(nullptr) {}
    ~BSTNode() {} // destruktor
};

template <typename T>
class BinarySearchTree {
    BSTNode<T> *root;

  public:
    BinarySearchTree() : root(nullptr) {} // konstruktor domyślny
    // ~BinarySearchTree() { clear(); }      // trzeba wyczyscic
    bool empty() const { return root == nullptr; }
    T &top() {
        assert(root != nullptr);
        return root->value;
    } // podgląd korzenia
    void insert(const T &item) { root = insert(root, item); }
    void remove(const T &item); // usuwanie przez złączanie
    // Szukając element dostajemy wskaźnik do elementu lub nullptr.
    T *search(const T &item) const {
        auto ptr = search(root, item);
        return ((ptr == nullptr) ? nullptr : &(ptr->value));
    }
    BSTNode<T> *debug_search(const T &item) const {
        auto ptr = search(root, item);
        return (ptr == nullptr) ? nullptr : ptr;
    }
    T *iter_search(const T &item) const { // wg libavl
        for (auto node = root; node != nullptr;) {
            if (item == node->value) {
                return &(node->value);
            } else if (item < node->value) {
                node = node->left;
            } else {
                node = node->right;
            }
        }
        return nullptr;
    }
    T *find_min() const {
        if (root == nullptr)
            return nullptr;
        return find_min(root);
    }
    T *find_max() const {
        if (root == nullptr)
            return nullptr;
        return find_max(root);
    }

    T *find_successor(const T &item) const {
        auto ptr = find_successor(root, item);
        return (ptr == nullptr) ? nullptr : &(ptr->value);
    }
    T * find_predecessor(const T& item) const {
        auto ptr = find_predecessor(root, item);
        return (ptr == nullptr) ? nullptr : &(ptr->value);
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

    // Metody bezpośrednio odwołujące się do node.
    // Mogą działać na poddrzewie.
    void clear(BSTNode<T> *node);
    BSTNode<T> *insert(BSTNode<T> *node, const T &item);       // zwraca nowy korzeń
    BSTNode<T> *search(BSTNode<T> *node, const T &item) const; // zwraca węzeł
    BSTNode<T> *remove(BSTNode<T> *node);                      // zwraca nowy korzeń poddrzewa
    BSTNode<T> *find_successor(BSTNode<T> *node, const T &item) const;
    BSTNode<T> *find_predecessor(BSTNode<T> *node, const T &item) const;
    T *find_min(BSTNode<T> *node) const;
    T *find_max(BSTNode<T> *node) const;
    void preorder(BSTNode<T> *node);
    void inorder(BSTNode<T> *node);
    void postorder(BSTNode<T> *node);
    void display(BSTNode<T> *node, int level);
    virtual void visit(BSTNode<T> *node) {
        assert(node != nullptr);
        std::cout << "visiting " << node->value << std::endl;
    }
};

template <typename T>
void BinarySearchTree<T>::display(BSTNode<T> *node, int level) {
    if (node == nullptr)
        return;
    display(node->right, level + 1);
    std::cout << std::string(3 * level, ' ') << node->value << std::endl;
    display(node->left, level + 1);
}

template <typename T>
BSTNode<T> *BinarySearchTree<T>::insert(BSTNode<T> *node, const T &item) {
    if (node == nullptr) {
        return new BSTNode<T>(item);
    }
    if (item < node->value) {
        node->left = insert(node->left, item);
        node->left->parent = node;
    } else {
        node->right = insert(node->right, item);
        node->right->parent = node;
    }
    return node; // zwraca nowy korzeń
}

template <typename T>
BSTNode<T> *BinarySearchTree<T>::search(BSTNode<T> *node, const T &item) const {
    if (node == nullptr || node->value == item) {
        return node;
    } else if (item < node->value) {
        return search(node->left, item);
    } else {
        return search(node->right, item);
    }
}
template <typename T>
void BinarySearchTree<T>::remove(const T &item) { // usuwanie przez złączanie
    // Najpierw znajdujemy wezel i jego rodzica.
    BSTNode<T> *node = root;
    BSTNode<T> *prev = nullptr;
    while (node != nullptr) {
        if (node->value == item)
            break;
        prev = node;
        if (item < node->value) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    // Szukamy przyczyny przerwania pętli while.
    if (node != nullptr && node->value == item) {
        // node ma być usunięty.
        if (node == root) {
            root = remove(node);
        } else if (prev->left == node) {
            prev->left = remove(node);
        } else {
            prev->right = remove(node);
        }
    } else if (root != nullptr) {
        ;    // klucza nie znaleziono
    } else { // root == nullptr
        ;    // drzewo jest puste
    }
}

template <typename T>
BSTNode<T> *BinarySearchTree<T>::remove(BSTNode<T> *node) {
    // Mamy usunąć węzeł i zwrócić nowy korzeń poddrzewa.
    assert(node != nullptr);
    BSTNode<T> *new_root;
    if (node->right == nullptr) { // node nie ma prawego dziecka
        new_root = node->left;
    } else if (node->left == nullptr) { // node nie ma lewego dziecka
        new_root = node->right;
    } else {                             // obecne lewe i prawe dziecko
        new_root = node;                 // zapisujemy stary korzeń
        node = node->left;               // idziemy w lewo
        while (node->right != nullptr) { // idziemy w prawo do końca
            node = node->right;
        }
        node->right = new_root->right; // prawe poddrzewo przełączone
        node = new_root;               // węzeł do usunięcia
        new_root = node->left;         // nowy korzeń
    }
    delete node;
    return new_root;
}

template <typename T>
T *BinarySearchTree<T>::find_min(BSTNode<T> *node) const {
    while (node->left) {
        node = node->left;
    }
    return &node->value;
}

template <typename T>
T *BinarySearchTree<T>::find_max(BSTNode<T> *node) const {
    while (node->right) {
        node = node->right;
    }
    return &node->value;
}
template <typename T>
BSTNode<T> *BinarySearchTree<T>::find_successor(BSTNode<T> *node, const T &item) const {
    BSTNode<T> *wantedNode = search(node, item);
    if (wantedNode->right != nullptr) {
        BSTNode<T> *tmpNode = wantedNode->right;
        while (tmpNode->left != nullptr) {
            tmpNode = tmpNode->left;
        }
        return tmpNode;
    }
    BSTNode<T> *parent = wantedNode->parent;
    while (parent != nullptr && wantedNode == parent->right) {
        wantedNode = parent;
        parent = wantedNode->parent;
    }
    return parent;
}
template <typename T>
BSTNode<T> *BinarySearchTree<T>::find_predecessor(BSTNode<T> *node, const T &item) const {
    BSTNode<T> *wantedNode = search(node, item);
    if (wantedNode->left !=nullptr) {
        BSTNode<T> *tmpNode = wantedNode->left;
        while (tmpNode->right != nullptr) {
            tmpNode = tmpNode->right;
        }
        return tmpNode;
    }
    BSTNode<T>* parent = wantedNode->parent;
    while (parent != nullptr && wantedNode == parent->left) {
        wantedNode = parent;
        parent = wantedNode->parent;
    }
    return parent;
}

#endif
