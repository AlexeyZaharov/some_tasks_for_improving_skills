/*
 Есть два сортированных списка (массива). Нужно написать функцию, которая делает новый сортированный
 список с объединением или пересечением элементов этих двух списков (два варианта задачи, выберите любой или оба сразу).
Пример:
1-ый список: 1, 2, 2, 5, 7, 14
2-й список: 4, 6, 6, 7, 9, 14, 15
Объединение: 1, 2, 2, 4, 5, 6, 6, 7, 7, 9, 14, 14, 15
Пересечение: 7, 14
 */

#include <iostream>
#include <vector>

template <typename T>
int bin_search(const std::vector<T>& v, const size_t& _begin, const size_t& _end, const T& value) {
    size_t begin = _begin;
    size_t end = _end;
    size_t middle = begin + (end - begin) / 2;

    while (begin < end && v[middle] != value) {
        if (v[middle] > value) {
            end = middle - 1;
            middle = begin + (end - begin) / 2;
        }
        else {
            begin = middle + 1;
            middle = begin + (end - begin) / 2;
        }
    }

    return v[middle] == value ? middle : -1;
}

template <typename T>
std::vector<T> make_intersection(const std::vector<T>& v1, const std::vector<T>& v2) {
    std::vector<T> intersection;

    if (v1.size() < v2.size()) {
        for (auto& i : v1) {
            size_t begin_index = 0;
            size_t end_index = 0;

            while (end_index <= v2.size() && v2[end_index] < i) {
                begin_index = end_index;
                end_index = end_index == 0 ? 1 : 2 * end_index;
            }

            if (end_index <= v2.size()) {
                if(bin_search(v2, begin_index, end_index, i) != -1) {
                    intersection.push_back(i);
                }
            }
            else {
                if(bin_search(v2, begin_index, v2.size(), i) != -1) {
                    intersection.push_back(i);
                }
            }
        }
    }
    else {
        for (auto& i : v2) {
            size_t begin_index = 0;
            size_t end_index = 0;

            while (end_index <= v1.size() && v1[end_index] < i) {
                begin_index = end_index;
                end_index = end_index == 0 ? 1 : 2 * end_index;
            }

            if (end_index <= v1.size()) {
                if(bin_search(v1, begin_index, end_index, i) != -1) {
                    intersection.push_back(i);
                }
            }
            else {
                if(bin_search(v2, begin_index, v1.size(), i) != -1) {
                    intersection.push_back(i);
                }
            }
        }
    }

    return intersection;
}

template <typename T>
std::vector<T> make_union (const std::vector<T>& v1, const std::vector<T>& v2) {
    std::vector<T> _union;



    for (size_t i = 0, j = 0; i < v1.size() && i < v2.size();) {
        if (v1[i] < v2[j]) {
            _union.push_back(v1[i++]);
        }
        else if (v1[i] > v2[j]) {
            _union.push_back(v2[j++]);
        }
        else {
            _union.push_back(v1[i]);
            ++i;
            ++j;
        }
    }

    return _union;
}

int main() {
    std::vector<int> v1{1,2,2,5,15};
    std::vector<int> v2{1,6,6,9,14,15};

    std::vector<int> intersection = make_intersection(v1, v2);
    std::vector<int> _union = make_union(v1, v2);

    for(auto& i : intersection) {
        std::cout << i << ' ';
    }

    std::cout << std::endl;

    for(auto& i : _union) {
        std::cout << i << ' ';
    }
}
