/*
Дана строка (возможно, пустая), состоящая из букв A-Z:
AAAABBBCCXYZDDDDEEEFFFAAAAAABBBBBBBBBBBBBBBBBBBBBBBBBBBB
Нужно написать функцию RLE, которая на выходе даст строку вида:
A4B3C2XYZD4E3F3A6B28
И сгенерирует ошибку, если на вход пришла невалидная строка.
*/


/*
Сложность по времени - O(n) - достаточно одного прохода по строке
Сложность по памяти - O(n) - требуется новая строка
*/

#include <iostream>
#include <string>

bool RLE(std::string &str) {
    std::string s{};
    size_t i = 0, count = 0;
    bool success = !str.empty();

    while (i < str.size()) {
        s += str[i];
        while (i + 1 < str.size() && str[i] == str[i + 1]) {
            ++count;
            ++i;
        }

        s += count ? std::to_string(count + 1) : "";
        count = 0;
        ++i;
    }

    str = s;

    return success;
}

int main() {
    std::string str{};

    std::cin >> str;

    if (RLE(str)) {
        std::cout << str;
    }
    else {
        std::cout << "Not valid string";
    }

    return 0;
}
