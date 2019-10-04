#include <iostream>
#include <vector>

// Объяснение - сначала комментарии в main, потом в find_sum,
// потом в find_subsegment с 3 параметрами, затем - с 5 параметрами

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

auto find_subsegment(const std::vector<int> &v, size_t begin, size_t end, const int &cur_sum, const int &sum) {

    if (begin >= end) return std::pair<size_t, size_t>(0, 0);

    if (cur_sum == sum) {
        return std::pair<size_t, size_t>(begin,end);
    }

    // если найденная сумма не равна заданной, пытаемся сузить "окно" сначала
    // слева направо, потом справа налево

    int new_sum = cur_sum;
    for (size_t i = begin; i < end - 1; ++i) {
        new_sum -= v[i];
        if (new_sum == sum) {
            return std::pair<size_t, size_t>(i + 1,end);
        }
    }

    // потом справа налево

    new_sum = cur_sum;
    for (int i = end - 1; i > begin; --i) {
        new_sum -= v[i];
        if (new_sum == sum) {
            return std::pair<size_t, size_t>(begin,i);
        }
    }

    // если заданной суммы не оказалось в проверенных случаях, это значит, что
    // v[begin] и v[end - 1] не принадлежат подотрезку с заданной суммой (так
    // как мы проверили все возможные "окна" с данными элементами)
    // в таком случае пытаемся найти подотрезок в массиве [begin + 1; end - 1]

    new_sum = cur_sum - v[begin] - v[end - 1];

    return find_subsegment(v, begin + 1, end - 1, new_sum, sum);
}

auto find_sum(const std::vector<int>& v, const int& sum) {
    int new_sum = 0, max = v[0], min = v[0];

    // считаем сумму всех чисел массива, находя минимум и максимум

    for (auto& i : v) {
        new_sum += i;
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
        // сумму для неотрицательную элементов)
        // нужен для того, чтобы понимать, следует ли расширять "окно" или сужать его

        int koef = sum / std::abs(sum);
        return find_subsegment(v, sum, koef);
    }
    else {

        // если числа различны по знаку, используем динамическое программирование

        return find_subsegment(v, 0, v.size(), new_sum, sum);
    }
}

int main() {
    std::vector<int> v = {-9,0,3,100,-7,5,6};

    int sum = 96;

    // Сложность алгоритма в случае "монотонного" массива (все числа имеют один и тот же
    // знак либо нулевые) - O(n), достаточно двух проходов по массиву: одного для поиска минимума
    // и максимума, второго - для поиска заданной суммы;
    // Если массив не монотонный - O(n^2), так как придется дважды проходить по каждому "окну" размером
    // n, n-2, n-4, ...
    // В обоих случаях сложность по памяти - O(1)

    auto pair = find_sum(v, sum);

    for (size_t i = pair.first; i < pair.second; ++i) {
        std:: cout << v[i] << " ";
    }
}
