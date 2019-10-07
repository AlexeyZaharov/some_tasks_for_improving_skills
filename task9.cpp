/*
Дан текст T и строка S. Требуется найти подстроку S' в T такую,
что она совпадает с S с точностью до перестановки букв.
*/

/*
Сложность по времени - O(n), где n - количество букв в тексте. Достаточно одного прохода по тексту
Сложность по памяти - O(m), где m - количество букв в подстроке. Необходимы два мультимножества
*/

#include <iostream>
#include <unordered_set>

std::pair<size_t, size_t> substring(const std::string& text, const std::string& substr) {

    // достаточно простое решение, если завести два мультимножества:

    if (text.size() < substr.size()) {
        return std::pair<size_t, size_t>(0,0);
    }

    // одно, состоящее из букв подстроки

    std::unordered_multiset<char> original_str;

    for (auto& i : substr) {
        original_str.insert(i);
    }

    // второе, необходимое для проверки, остались ли буквы, которых нет в подстроке массива

    std::unordered_multiset<char> remaining_letters(original_str);

    // простота в том, что задано число букв, поэтому ставим необходимое "окно" на начало массива
    // и смотрим, какие буквы оттуда можно взять для соответствия заданной подстроки

    for (size_t i = 0; i < substr.size(); ++i) {
        if (original_str.find(text[i]) != original_str.end()) {
            remaining_letters.erase(text[i]);
        }
    }

    // если начало массива не совпало с подстрокой, идем дальше, двигая "окно" фиксированного размера

    size_t i = substr.size();

    // двигаем окно до тех пор, пока не пройдем весь массив или до тех пор, пока все необходимые буквы для создания
    // подстроки будут найдены

    for (; !remaining_letters.empty() && i < text.size(); ++i) {

        // при движении "окна" крайняя слева буква исчезает, поэтому, если она участвовала в создании подстроки,
        // ее нужно снова добавить в мультимножества необходимых букв

        if (original_str.find(text[i - substr.size()]) != original_str.end()) {
            remaining_letters.insert(text[i - substr.size()]);
        }

        // если новая буква участвует в создании подстроки, убираем ее из мультимножества необходимых букв

        if (original_str.find(text[i]) != original_str.end()) {
            remaining_letters.erase(text[i]);
        }
    }

    // в случае успеха возвращаем позиции начала и конца "окна", иначе пару (0, 0)

    if (remaining_letters.empty()) {
        return std::pair<size_t, size_t>(i - substr.size(), i);
    }
    else {
        return std::pair<size_t, size_t>(0, 0);
    }
}

void check_results(const std::string& text, const std::string substr, const std::pair<size_t, size_t>& pair) {
    std::cout << "Substr:" << std::endl << substr <<
              std::endl << "In text:" << std::endl << text << std::endl << std::endl;

    if (pair != std::pair<size_t, size_t>(0,0)) {
        std::cout << "Is found" << std::endl;

        std::cout << text << std::endl;

        std::cout << std::string(pair.first, '-') << substr <<
                  std::string(text.size() - pair.second, '-') << std::endl;
    }
    else {
        std::cout << "Is not found";
    }
}

int main() {

    std::string text("Hello, world!");
    std::string substr("Hello, world!");
    auto pair = substring(text, substr);
    check_results(text, substr, pair);

    std::cout << std::endl << std::endl;

    text = "Hello, world!";
    substr = "!d";
    pair = substring(text, substr);
    check_results(text, substr, pair);

    std::cout << std::endl << std::endl;

    text = "Hello, world!";
    substr = "elHl";
    pair = substring(text, substr);
    check_results(text, substr, pair);

    std::cout << std::endl << std::endl;

    text = "Hello, world!";
    substr = "!o,w lHerdlol";
    pair = substring(text, substr);
    check_results(text, substr, pair);

    std::cout << std::endl << std::endl;

    text = "Hello, world!";
    substr = ",r loow";
    pair = substring(text, substr);
    check_results(text, substr, pair);

    std::cout << std::endl << std::endl;

    text = "Hello, world!";
    substr = "elk";
    pair = substring(text, substr);
    check_results(text, substr, pair);
}
