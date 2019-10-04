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

void change_string(std::string &str) {
    std::string s{};
    size_t i = 0, j = 0, k = 0;
    bool success = true;

    while (i < str.size()) {
        if (str[i] < 65 || str[i] > 90) {
            s = "Not valid string";
            success = false;
            break;
        }

        s += str[i];
        while (i + 1 < str.size() && str[i] == str[i + 1]) {
            if (str[i] < 65 || str[i] > 90) {
                s = "Not valid string";
                success = false;
                break;
            }
            ++k;
            ++i;
        }

        if (!success)
            break;

        s += k ? std::to_string(k + 1) : "";
        k = 0;
        ++i;
    }

    str = s;
}

int main() {
    std::string str{};

    std::cin >> str;

    change_string(str);

    std::cout << str;

    return 0;
}