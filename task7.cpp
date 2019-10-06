/*
Есть отсортированный массив из N чисел от 1 до N (все числа различные). Массив перемешали и 1 число выкинули.
Как найти число, которое удалили?
Дополнение: если выкинули два числа?
В обоих пунктах память O(1)
Дополнение - а если выкинули 3 числа?
*/

/*
Сложность для одного числа: по памяти O(1), по времени - 2 прохода по массиву для подсчета сумм - O(n)
Сложность для двух чисел: по памяти O(1), по времени - O(nlogn) в среднем случае (время быстрой сортировки)
Сложность для трех чисел: по памяти O(n), по времени - 1 проход по массиву - O(n)
*/


#include <iostream>
#include <vector>
#include <unordered_set>

int find_lost_number(const std::vector<int>& v, const int& original_sum) {

    // если выкинули одно число, его легко можно найти, вычтя из суммы чисел оригинального массива
    // сумму чисел нового массива

    int sum = 0;

    for (auto& i : v) {
        sum += i;
    }

    return original_sum - sum;
}

std::pair<int, int> find_two_lost_number(std::vector<int>&& v, const int& original_sum) {

    // если выкинули два числа, их тоже можно легко найти, отсортировав массив

    std::sort(v.begin(), v.end());
    std::pair<int, int> numbers(0,0);


    // и находя числа, которые должны быть в массиве, но их нет:
    // легко найти, так как на месте i-ого индекса должно стоять
    // число i + 1

    for (size_t i = 0, index = 0; i < v.size() + 2; ++i) {

        // если на этом месте стоит другое число, то добавляем это число в пару потерянных чисел

        if (v[index] - (i + 1) != 0) {
            if (numbers.first == 0) {
                numbers.first = i + 1;
                continue;
            }
            else {
                numbers.second = i + 1;
                break;
            }
        }

        // а если совпадают, проверяем другие числа массива
        
        ++index;
    }

    return numbers;
}

std::unordered_set<int> find_three_lost_number(const std::vector<int>& v) {

    // подобным образом три выкинутых числа не найти (так второе и третье выкинутые числа нельзя
    // однозначно определить, выбрав первое выкинутое число). Следовательно, заведем множество,
    // состоящее из исходных элементов

    std::unordered_set<int> original_v;

    for (size_t i = 0; i < v.size() + 3; ++i) {
        original_v.insert(i+1);
    }

    // Затем удалим из множества все те элементы, которые присутствуют в перемешанном массиве

    for (auto& i : v) {
        original_v.erase(i);
    }

    // оставшиеся элементы и будут числами, которые из массива выкинули

    return original_v;
}

int main() {
    // пусть исходный массив равен {1, 2, 3, 4, 5, 6}. Сумма числе = 21

    int lost_number = find_lost_number({2,3,4,5,6}, 21);
    auto pair_of_lost_numbers = find_two_lost_number({3,4,5,6}, 21);
    auto set_of_lost_numbers = find_three_lost_number({4,5,6});

    std::cout << lost_number << std::endl;
    std::cout << pair_of_lost_numbers.first << ' ' << pair_of_lost_numbers.second << std::endl;

    for (auto& i : set_of_lost_numbers) {
        std::cout << i << ' ';
    }

    std::cout << std::endl << "-----------" << std::endl;

    lost_number = find_lost_number({1,2,3,4,5}, 21);
    pair_of_lost_numbers = find_two_lost_number({1,2,3,4}, 21);
    set_of_lost_numbers = find_three_lost_number({1,2,3});

    std::cout << lost_number << std::endl;
    std::cout << pair_of_lost_numbers.first << ' ' << pair_of_lost_numbers.second << std::endl;

    for (auto& i : set_of_lost_numbers) {
        std::cout << i << ' ';
    }

    std::cout << std::endl << "-----------" << std::endl;

    lost_number = find_lost_number({1,2,4,5,6}, 21);
    pair_of_lost_numbers = find_two_lost_number({1,3,5,6}, 21);
    set_of_lost_numbers = find_three_lost_number({1,3,5});

    std::cout << lost_number << std::endl;
    std::cout << pair_of_lost_numbers.first << ' ' << pair_of_lost_numbers.second << std::endl;

    for (auto& i : set_of_lost_numbers) {
        std::cout << i << ' ';
    }
}
