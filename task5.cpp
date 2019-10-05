/*
Дан массив из нулей и единиц. Нужно определить, какой максимальный 
по длине подинтервал единиц можно получить, удалив ровно один элемент массива.
*/

/*
Сложность по времени - O(n) - всего один проход по массиву
Сложность по памяти - O(1), так как требуется всего три итератора
*/


#include <iostream>
#include <vector>

size_t find_max_unit_interval(const std::vector<int> &v) {

    // ищем 3 нуля: крайний слева (left), крайний справа (right) и тот,
    // который между ними (between). Изначально ставим 3 ноля перед всем вектором
    // и ставим указатели на них

    int left = -3, between = -2, right = -1;

    // находим максимальный подинтервал как количество элементов в отрезке
    // между левым и правым нулем за вычетом 3 нулей (левого, серединного и правого):
    // max = (right - left + 1) - 3

    size_t max = right - left - 2;

    // ищем нули

    for (int t = right + 1; t < v.size(); ++t) {

        // если нашли ноль, обновляем позиции левого, серединного и правого нулей и считаем
        // количество максимального единичного подинтервала

        if (v[t] == 0) {
            left = between;
            between = right;
            right = t;
            max = max > right - left - 2 ? max : right - left - 2;
        }
    }

    // ставим ноль за вектором, чтобы не потерять интервал, заканчивающийся на единицу

    left = between;
    between = right;
    right = v.size();


    return max = max > right - left - 2 ? max : right - left - 2;
}

int main() {
    std::vector<int> v[]{ {0},
                           {1},
                           {0,0},
                           {0,1},
                           {1,0},
                           {1,1},
                           {0,0,0},
                           {0,0,1},
                           {0,1,0},
                           {1,0,0},
                           {0,1,1},
                           {1,0,1},
                           {1,1,0},
                           {0,0,0,0},
                           {0,0,0,1},
                           {0,0,1,0},
                           {0,1,0,0},
                           {1,0,0,0},
                           {0,0,1,1},
                           {0,1,0,1},
                           {1,0,0,1},
                           {1,0,1,0},
                           {1,1,0,0},
                           {0,1,1,1},
                           {1,1,1,0},
                           {1,1,1,1}
                           };

    for (auto& i : v) {
        for (auto& j : i) {
            std::cout << j;
        }
        std::cout << "-->" << find_max_unit_interval(i) << std::endl << std::endl;
    }

}