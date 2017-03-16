#include "stdafx.h"
#include "list_utils.h"

//заполнение контейнера из файла
std::list<double>& fill_container_with_numbers(std::fstream& file) {
    std::list<double>* list = new std::list<double>();
    file.clear();
    file.seekg(0);
    if (file.is_open())
    {
        std::string line;
        int num;
        while (!file.eof())
        {
            std::getline(file, line);
            try {
                num = std::stoi(line);
                list->push_back(double(num));
            }
            catch (std::exception e) {}
        }
    }
    return *list;
}

//функция по получению последнего отрицательного числа
double get_last_negative(std::list<double>::iterator first, std::list<double>::iterator last) {
    double neg = 0;
    for (std::list<double>::iterator it = first; it != last; ++it) {
        if (*it < 0) {
            neg = *it;
        }
    }
    return neg;
}

//модификация контейнера
void modify(std::list<double>& list) {
    double last_negative = get_last_negative(list.begin(), list.end()) / 2;
    if (last_negative == 0) { throw std::exception("В контейнера нет отрицательных чисел."); }
    for (std::list<double>::iterator it = list.begin(); it != list.end(); ++it) {
        *it = *it + last_negative;
    }
}

//модификация части контейнера
void modify(std::list<double>& list, std::list<double>::iterator first, std::list<double>::iterator last) {
    double last_negative = get_last_negative(first, last) / 2;
    if (last_negative == 0) { throw std::exception("В контейнера нет отрицательных чисел."); }
    for (std::list<double>::iterator it = first; it != last; ++it) {
        *it = *it + last_negative;
    }
}

//структура для модификации элементов через transform
struct transform_functor {
    transform_functor(double last_neg) : last_neg(last_neg) {}
    double operator()(double x1) { return last_neg + x1; }

private:
    double last_neg;
};

//функция для модификации через transform
void modify_transform(std::list<double>& list) {
    double last_negative = get_last_negative(list.begin(), list.end()) / 2;
    if (last_negative == 0) { throw std::exception("В контейнера нет отрицательных чисел."); }
    std::transform(list.begin(), list.end(), list.begin(), transform_functor(last_negative));
}

//структура для модификации через for_each
struct foreach_functor {
    foreach_functor(double last_neg) : last_neg(last_neg) {}
    void operator()(double &x1) { x1 = last_neg + x1; }

private:
    double last_neg;
};

//функция для модификации через for_each
void modify_foreach(std::list<double>& list) {
    double last_negative = get_last_negative(list.begin(), list.end()) / 2;
    if (last_negative == 0) { throw std::exception("В контейнера нет отрицательных чисел."); }
    std::for_each(list.begin(), list.end(), foreach_functor(last_negative));
}

//функция суммирования контейнера
double sum_container(std::list<double> list) {
    double sum = 0;
    std::list<double>::iterator it = list.begin();
    while (it != list.end()) {
        sum += *it;
        ++it;
    }
    return sum;
}

//вычисление среднего арифмитического контейнера
double avg_container(std::list<double> list) {
    double avg = 0;
    if (list.size() != 0) {
        avg = sum_container(list) / list.size();
    }
    return avg;
}

//функция для демонстрация контейнера
void show_container(std::list<double> list) {
    std::list<double>::iterator it = list.begin();
    while (it != list.end()) {
        if (it != list.begin()) {
            std::cout << ", ";
        }
        std::cout << *it;
        ++it;
    }
    std::cout << std::endl;
}