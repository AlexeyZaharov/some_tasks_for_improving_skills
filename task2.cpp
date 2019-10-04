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
    // node() { ... }
    T data;
    node *next;
};

template <typename T>
void revers_list(node<T> * root) {
    node<T> * cur = root, * prev = nullptr, * next = nullptr;

    while (cur != nullptr) {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }

    root = prev;
}
