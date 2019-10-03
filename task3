/*
Напишите код, который вернёт медиану из трёх чисел. int median3(int v1, int v2, int v3)
*/

/*
Сложность по времени и по памяти - O(1)
*/

#include <iostream>

int median3(int v1, int v2, int v3) {
    if (v1 < v2) {
        return v2 < v3 ? v2 : (v1 < v3 ? v3 : v1);
    }
    else {
        return v1 < v3 ? v1 : (v2 < v3 ? v3 : v2);
    }
}

int main() {
    std::cout << median3(1,2,3) << std::endl;
    std::cout << median3(1,3,2) << std::endl;
    std::cout << median3(2,1,3) << std::endl;
    std::cout << median3(2,3,1) << std::endl;
    std::cout << median3(3,1,2) << std::endl;
    std::cout << median3(3,2,1) << std::endl;

    std::cout << std::endl;

    std::cout << median3(2,1,1) << std::endl;
    std::cout << median3(1,2,1) << std::endl;
    std::cout << median3(1,1,2) << std::endl;

    std::cout << std::endl;

    std::cout << median3(1,1,1) << std::endl;
}
