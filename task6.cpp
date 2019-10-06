/*
Написать проверку является ли дерево бинарным деревом поиска bool is_binary_search_tree(const Node * root).

P.S. Запрограммировался и в качестве простого дерева случайно написал бинарное дерево поиска со всеми его операциям,
поэтому пришлось создавать фукции shake_tree4, чтобы дерево не было бинарным
*/

/*
Сложность по времени - O(n), где n - количество элементов в дереве. Достаточно совершить in-order проход по
дереву, чтобы проверить свойства бинарного дерева поиска
Сложность по памяти - O(1)
*/

#include <iostream>
#include <queue>
#include <vector>

template <typename T>
struct node {
    T data;
    node* left;
    node* right;

    explicit node(const T& _data) {
        data = _data;
        left = nullptr;
        right = nullptr;
    }
};

template <typename T>
class binary_tree {
    node<T>* root;

    std::pair<node<T>*, node<T>* > find_element(node<T>* root, node<T>* parent, const T& data) const {
        if (root != nullptr) {
            if (data == root->data) {
                return std::pair<node<T>*, node<T>* > (root, parent);
            }
            else if (data < root->data) {
                return find_element(root->left, root, data);
            }
            else {
                return find_element(root->right, root, data);
            }
        }
        else {
            return std::pair<node<T>*, node<T>* > (nullptr, nullptr);
        }
    }

    void delete_node_with_two_child(node<T>* parent, node<T>* node_of_next_data) {
        node<T>* first_parent = parent;

        while (node_of_next_data->left != nullptr) {
            parent = node_of_next_data;
            node_of_next_data = node_of_next_data->left;
        }

        if (parent == first_parent) {
            parent->right = node_of_next_data->right;
        }
        else {
            parent->left = node_of_next_data->right;
        }

        std::swap(node_of_next_data->data, first_parent->data);

        delete node_of_next_data;
    }

    void delete_node_with_one_child(node<T>* parent, node<T>* elem, node<T>* next) {
        if (parent) {
            if (elem == parent->right) {
                parent->right = next;
            }
            else {
                parent->left = next;
            }

            delete elem;
        }
        else {
            parent = elem;
            elem = next;
            delete parent;
        }
    }

    void print(const node<T>* node) const {
        if (node) {
            print(node->left);

            std::cout << node->data << ' ';

            print(node->right);
        }
    }

public:
    binary_tree() : root(nullptr) {}

    binary_tree(const std::initializer_list<T>& init_list) {
        root = nullptr;

        for (auto& i : init_list) {
            add_element(i);
        }
    }

    void add_element(const T& data) {
        if (!root) {
            root = new node<T>(data);
            return;
        }

        node<T>* cur = root;

        while (cur->left != nullptr || cur->right != nullptr) {
            if (data < cur->data) {
                if (cur->left) {
                    cur = cur->left;
                }
                else {
                    break;
                }
            }
            else {
                if (cur->right) {
                    cur = cur->right;
                }
                else {
                    break;
                }
            }
        }

        if (data < cur->data) {
            cur->left = new node<T>(data);
        }
        else {
            cur->right = new node<T>(data);
        }
    }

    const node<T>* find_element(const T& data) const {
        return find_element(root, nullptr, data).first;
    }

    void delete_element(const T& data) {
        auto pair = find_element(root, nullptr, data);
        node<T>* elem = pair.first;
        node<T>* parent = pair.second;

        if (elem != nullptr) {
            if (elem->left != nullptr && elem->right != nullptr) {
                delete_node_with_two_child(elem, elem->right);
            }
            else {
                if (elem->left != nullptr) {
                    delete_node_with_one_child(parent, elem, elem->left);
                }
                else if (elem->right != nullptr) {
                    delete_node_with_one_child(parent, elem, elem->right);
                }
                else {
                    if (elem == parent->right) {
                        parent->right = nullptr;
                    }
                    else {
                        parent->left = nullptr;
                    }
                    delete elem;
                }
            }
        }
    }

    const node<T>* get_root() const{
        return root;
    }

    void print() const {
        if (root) {
            print(root->left);

            std::cout << root->data << ' ';

            print(root->right);

            std::cout << std::endl;
        }
    }

    void shake_tree1() {
        std::swap(root->left, root->right);
    }

    void shake_tree2() {
        std::swap(root->left->left, root->left->right);
    }

    void shake_tree3() {
        std::swap(root->right->left, root->right->right);
    }

    void shake_tree4() {
        std::swap(root->left->left, root->right->right);
    }

    ~binary_tree() {
        std::queue<node<T>*> queue;

        if (root) {
            queue.push(root);
        }

        while(!queue.empty()) {
            node<T>* cur = queue.front();

            if (cur->right) {
                queue.push(cur->right);
            }

            if (cur->left) {
                queue.push(cur->left);
            }

            queue.pop();

            delete cur;
        }
    }
};

template <typename T>
bool is_binary_search_tree(const node<T>* root) {
    bool binary_search_tree = true;

    if (root == nullptr || (root->left == nullptr && root->right == nullptr)) {
        return binary_search_tree;
    }

    if (root->left != nullptr) {
        binary_search_tree = binary_search_tree &&
                root->left->data < root->data;
    }

    if (root->right != nullptr) {
        binary_search_tree = binary_search_tree &&
                             root->right->data >= root->data;
    }

    return binary_search_tree && is_binary_search_tree(root->left) && is_binary_search_tree(root->right);
}

template <typename T>
bool is_binary_search_tree(const binary_tree<T>& tree) {
    return is_binary_search_tree(tree.get_root());
}

int main() {
    binary_tree<int> tree({1,0,-100,4, 300, 2, 2, 0});
    bool success = is_binary_search_tree(tree);
    if (success) {
        std::cout << "Is binary search tree:" << std::endl;
    }
    else {
        std::cout << "Not is binary search tree:" << std::endl;
    }
    tree.print();


    tree.shake_tree1(); // первый раз меняем местами поддеревья
    success = is_binary_search_tree(tree);
    if (success) {
        std::cout << "Is binary search tree:" << std::endl;
    }
    else {
        std::cout << "Not is binary search tree:" << std::endl;
    }
    tree.print();
    tree.shake_tree1(); // второй раз восстанавливаем свойство дерева. Аналогично для остальных перемешек

    tree.shake_tree2();
    success = is_binary_search_tree(tree);
    if (success) {
        std::cout << "Is binary search tree:" << std::endl;
    }
    else {
        std::cout << "Not is binary search tree:" << std::endl;
    }
    tree.print();
    tree.shake_tree2();

    tree.shake_tree3();
    success = is_binary_search_tree(tree);
    if (success) {
        std::cout << "Is binary search tree:" << std::endl;
    }
    else {
        std::cout << "Not is binary search tree:" << std::endl;
    }
    tree.print();
    tree.shake_tree3();

    tree.shake_tree4();
    success = is_binary_search_tree(tree);
    if (success) {
        std::cout << "Is binary search tree:" << std::endl;
    }
    else {
        std::cout << "Not is binary search tree:" << std::endl;
    }
    tree.print();
    tree.shake_tree4();

    success = is_binary_search_tree(tree);
    if (success) {
        std::cout << "Is binary search tree:" << std::endl;
    }
    else {
        std::cout << "Not is binary search tree:" << std::endl;
    }
    tree.print();
}
