/*
Имеется односвязный список, заданный ссылкой head на первый элемент.
Предложите и реализуйте алгоритм, который осуществляет разворот списка:
получается новый список, элементы которого следуют в обратном порядке
относительно исходного списка.
*/

/*
Сложность по времени - O(n)
Сложность по памяти - O(1)
*/

#include <iostream>
#include <string>

template <typename T>
struct node {
    T data;
    node *next;

    explicit node(const T& _data) {
        data = _data;
        next = nullptr;
    }
};

template <typename T>
class my_list {
    node<T>* root;

public:
    my_list() : root(nullptr) {}

    my_list(std::initializer_list<T>&& init_list) {
        root = nullptr;
        node<T>* cur = root;

        for (auto& i : init_list) {
            if (!root) {
                root = new node<T>(i);
                cur = root;
            }
            else {
                cur->next = new node<T>(i);
                cur = cur->next;
            }
        }
    }

    void revers_list() {
        node<T> * cur = root, * prev = nullptr, * next = nullptr;

        while (cur != nullptr) {
            next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }

        root = prev;
    }

    void print() {
        node<T>* cur = root;

        if (!cur) return;

        while(cur->next) {
            std::cout << cur->data << " -> ";
            cur = cur->next;
        }

        std::cout << cur->data << std::endl;
    }

    ~my_list() {
        while (root != nullptr) {
            node<T>* next = root->next;
            delete root;
            root = next;
        }
    }
};



int main() {
    my_list list1{1,2,3,4,5};
    my_list list2{1,2,3};
    my_list list3{1,2};
    my_list list4{1};
    my_list<int> list5;

    std::cout << "---------------" << std::endl;
    list1.print();
    list1.revers_list();
    list1.print();
    std::cout << "---------------" << std::endl;

    std::cout << "---------------" << std::endl;
    list2.print();
    list2.revers_list();
    list2.print();
    std::cout << "---------------" << std::endl;

    std::cout << "---------------" << std::endl;
    list3.print();
    list3.revers_list();
    list3.print();
    std::cout << "---------------" << std::endl;

    std::cout << "---------------" << std::endl;
    list4.print();
    list4.revers_list();
    list4.print();
    std::cout << "---------------" << std::endl;

    std::cout << "---------------" << std::endl;
    list5.print();
    list5.revers_list();
    list5.print();
    std::cout << "---------------" << std::endl;
}
