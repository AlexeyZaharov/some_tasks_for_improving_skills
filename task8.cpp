/*
Дан массив точек с целочисленными координатами (x, y).
Определить, существует ли вертикальная прямая, делящая
точки на 2 симметричных относительно этой прямой множества.
*/

/*
Сложность по времени - зависит от сортировки, в среднем - O(nlogn). Необходимо сформировать хеш-таблицу (O(n)),
отсортировать точки (O(nlogn)) и один раз пройтись по всем точкам (O(n))
Сложность по памяти - O(n), так как формируем хеш-таблицу
*/

#include <iostream>
#include <unordered_map>
#include <vector>

bool is_possible_to_make_partition(const std::vector<std::pair<int, int>> & v) {

    // заводим хеш-таблицу, ключами в которой будут значения координат y точек,
    // а элементами таблицы - значения координат x точек

    std::unordered_map<int, std::vector<int>> map;
    bool is_possible = true;

    for (auto& i : v) {
        map[i.first].push_back(i.second);
    }

    // необходимо отсортировать элементы таблицы, чтобы быстро определять позицию
    // возможной симметрической вертикали (в таком случае координата x данной вертикали
    // будет определяться как координата крайней левой точки плюс половина расстояния
    // от этой точки до крайней правой, притом крайними точками будем считать такие пары:
    // самая левая - самая правая, вторая слева - вторая справа и т.д.

    for (auto& elem : map) {
        std::sort(elem.second.begin(), elem.second.end());
    }

    double x_symmetrical_vertical = 0;
    bool is_initilize = false;

    for (auto& elem : map) {
        size_t size = elem.second.size();
        for (size_t i = 0; i < int(size / 2); ++i) {

            // считаем координату вертикали, симметрической для данной пары точек

            double x_line = elem.second[i] + (elem.second[size - 1 - i] - elem.second[i]) / 2;

            // затем проверяем, совпадает ли координата данной вертикали с той, что является
            // симметрической для остальных точек

            if (!is_initilize) {
                x_symmetrical_vertical = x_line;
                is_initilize = true;
            }
            else {
                is_possible = x_symmetrical_vertical == x_line;

                if (!is_possible) {
                    break;
                }
            }
        }

        // если количество точек на данной координате нечетно, то серединная точка
        // должна лежать на вертикали

        if (is_possible && size % 2 != 0) {
            if (!is_initilize) {
                x_symmetrical_vertical = elem.second[int(size / 2)];
                is_initilize = true;
            }
            else {
                is_possible = x_symmetrical_vertical != elem.second[(size + 1) / 2];
            }
        }

        if (!is_possible) {
            break;
        }
    }

    return is_possible;
}

int main() {
    std::vector<std::pair<int, int>> v{
            std::pair<int, int>(1,1),
            std::pair<int, int>(1,7),
            std::pair<int, int>(2,2),
            std::pair<int, int>(2,6),
            std::pair<int, int>(1,4),
    };

    std::cout << is_possible_to_make_partition(v);
}
