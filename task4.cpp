/*
Дан массив целых чисел, нужно найти непустой подотрезок (непрерывную подпоследовательность)
с заданной суммой X, либо сказать, что это невозможно.
*/

#include <iostream>
#include <vector>
#include <unordered_map>

// Объяснение - сначала комментарии в main, потом в find_sum,
// потом в find_subsegment с 3 параметрами, затем - с 7 параметрами

auto find_subsegment(const std::vector<int>& v, const int& sum, const int& koef) {
    size_t i = 1, j = 0;

    int cur_sum = koef * v[0];

    for (; i < v.size(); ++i) {

        //если заданная сумма больше текущей, необходимо сузить "окно"

        if (cur_sum > koef * sum) {
            while (cur_sum > koef * sum) {
                cur_sum -= koef*v[j++];
            }
        }

        if (cur_sum == koef * sum) {
            break;
        }

        // если текущая сумма меньше заданной, расширяем "окно"

        cur_sum += koef*v[i];
    }

    if (cur_sum == koef * sum) {
        return std::pair<size_t, size_t>(j,i);
    }
    else {
        return std::pair<size_t, size_t>(0,0);
    }
}

auto find_subsegment(const std::vector<int> &v, size_t begin, size_t end,
        std::unordered_map<int, size_t>& left_amounts,
        std::unordered_map<int, size_t>& right_amounts,
        const int &left_sum, const int& right_sum) {

    // так как на прошлом шаге не обнаружилась заданная сумма, то это значит, что ни v[begin], ни v[end - 1]
    // не принадлежат подотрезку с заданной суммой. С другой стороны, мы к заданной сумме можем добавить значение
    // v[begin] или v[end - 1], чтобы "расширить окно" и найти заданную сумму. Главное, помнить, сколько раз мы
    // расширяли это окно, чтобы затем лишние элементы не попали в подотрезок

    if (begin >= end) {
        return std::pair<size_t, size_t>(0, 0);
    }

    // действуем следующим образом: добавиляем не попавший в подотрезок левый элемент к заданной сумме и ищем его
    // в таблице левых сумм. Если нашли, то наш подинтервал начинается с элемента, следуещего после begin и до значения
    // таблицы с ключом новой суммы

    if (left_amounts.find(left_sum + v[begin]) != left_amounts.end()) {
        return std::pair<size_t, size_t>(begin + 1, left_amounts[left_sum + v[begin]] + 1);
    }

    // Аналогично для правых сумм

    if (right_amounts.find(right_sum + v[end - 1]) != right_amounts.end()) {
        return std::pair<size_t, size_t>(right_amounts[right_sum + v[end - 1]], end - 1);
    }

    return find_subsegment(v, begin + 1, end - 1, left_amounts, right_amounts,
            left_sum + v[begin], right_sum + v[end - 1]);
}

auto find_sum(const std::vector<int>& v, const int& sum) {
    int new_sum = 0, max = v[0], min = v[0];

    // находим минимум и максимум

    for (auto& i : v) {
        max = max > i ? max : i;
        min = min < i ? min : i;
    }

    // если все числа имеют один знак, то сумма будет монотонно возрастать
    // или монотонно убывать при движении по массиву, в этом случае
    // достаточно одного прохода по массиву для нахождения заданной суммы

    if (max * min >= 0) {

        // если сумма равна нулю при условии "монотонности" массива, то единственный вариант
        // найти такую сумму - найти нулевой элемент

        if (sum == 0) {
            for (int i = 0; i < v.size(); ++i) {
                if (v[i] == 0)
                    return std::pair<size_t, size_t>(i, i + 1);
            }
        }

        // иначе нужно искать, двигая "окно" по массиву
        // koef - костыль, чтобы не писать отдельные функции для неотрицательного и
        // неположительного массива: он либо 1, либо -1 (всегда будем искать положительную
        // сумму для неотрицательных элементов)
        // нужен для того, чтобы понимать, следует ли расширять "окно" или сужать его

        int koef = sum / std::abs(sum);
        return find_subsegment(v, sum, koef);
    }
    else {

        // если числа различны по знаку, используем две хеш-таблицы: левые суммы и правые суммы
        // ключами таблицы левых сумм будут суммы от 1 до k элемента, k меняется от 1 до v.size(),
        // значениями таблицы будут индекс крайнего правого элемента (k);
        // аналогично для таблицы правых сумм, только суммы будут от k до v.size(), k меняется от 1 до v.size()

        std::unordered_map<int, size_t> left_amounts, right_amounts;
        int left_sum = 0, right_sum = 0;

        for (size_t i = 0; i < v.size(); ++i) {
            left_sum += v[i];
            left_amounts[left_sum] = i;

            right_sum += v[v.size() - 1 - i];
            right_amounts[right_sum] = v.size() - 1 - i;
        }

        // если среди найденных сумм нашлась заданная сумма, возвращаем значения полуинтервала
        // [begin_index, end_index) такого, что сумма всех чисел с индексами данного полуинтервала равна заданной сумме

        if (left_amounts.find(sum) != left_amounts.end()) {
            return std::pair<size_t, size_t>(0, left_amounts[sum] + 1);
        }

        if (right_amounts.find(sum) != right_amounts.end()) {
            return std::pair<size_t, size_t>(right_amounts[sum], v.size());
        }

        // если среди данных таблиц суммы не нашлось, ищем дальше

        return find_subsegment(v, 0, v.size(), left_amounts, right_amounts, sum, sum);
    }
}

int main() {
    std::vector<int> v = {-9,0,3,100,-7,5,6};

    int sum = 98;

    // Сложность алгоритма в случае "монотонного" массива (все числа имеют один и тот же
    // знак либо нулевые) - O(n), достаточно двух проходов по массиву: одного для поиска минимума
    // и максимума, второго - для поиска заданной суммы; сложность по памяти - O(1);
    // Если массив не монотонный - O(n), но придется использовать O(n) памяти

    auto pair = find_sum(v, sum);

    if (pair.first == pair.second) {
        std:: cout << "It is impossible";
    }
    else {
        for (size_t i = pair.first; i < pair.second; ++i) {
            std:: cout << v[i] << " ";
        }
    }
}
