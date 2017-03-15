// stl_task_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <time.h> 
#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <algorithm>
#include <time.h>
#include <limits.h>

std::string file_name = "";
std::fstream* file;
std::list<int>* list;

void print_message(std::string msg)
{
	std::cout << msg << std::endl;
	system("pause");
	system("cls");
}

void print_menu()
{
    system("cls");
	std::cout << "1. Заполнение текстового файла числами" << std::endl;
	std::cout << "2. Заполнение контейнера из файла" << std::endl;
	std::cout << "3. Преобразование контейнера" << std::endl;
	std::cout << "4. Сумма" << std::endl;
	std::cout << "5. Среднее арифметическое" << std::endl;
	std::cout << "6. Вывод" << std::endl;
	std::cout << "0. Выход" << std::endl;
    if (list == NULL) { std::cout << "Внимание, список не существует! Некоторые действия недоступны!" << std::endl; }
}

void getChoice(int min, int max, int& choice_number) {
	std::string choice = "";
	try {
		std::getline(std::cin, choice);
		choice_number = std::stoi(choice);
		if ((choice_number < min) || (choice_number > max))
		{
			print_message("Вы должны ввести число от " + std::to_string(min) + " до " + std::to_string(max) +"!");
		}
	}
	catch (std::invalid_argument e)
	{
		print_message("Вы должны ввести число!");
	}
	catch (std::out_of_range e)
	{
		print_message("Выход за границы типа!");
	}
}

int main_menu() {
	std::string choice = "";
	int choice_number = -1;
	while ((choice_number < 0) || (choice_number > 7))
	{
		print_menu();
		getChoice(0, 7, choice_number);
	}
	return choice_number;
}

std::fstream& fill_file_with_numbers(int n, int m, std::string filename)
{
	srand(time(NULL));
	std::fstream* fout = new std::fstream(filename, std::fstream::in | std::fstream::out | std::fstream::trunc);
	if (fout->is_open()) {
		int random_number;
		for (int i = 1; i <= n; ++i) {
			random_number = std::rand() % (2 * m) - m;
			*fout << random_number << std::endl;
		}
	}
	return *fout;
}

struct Random {
public:
	explicit Random(int m) { max = m; }
	int operator()();
private:
	int max;
};

int Random::operator()(){  
	return (std::rand()) % (2 * max) - max; 
}

std::fstream& fill_file_with_numbers_generate(int n, int m, std::string filename)
{
	srand(time(NULL));
	std::fstream* fout = new std::fstream(filename, std::fstream::in | std::fstream::out | std::fstream::trunc);
	if (fout->is_open()) {
		std::list<int> buf_list(n);
		std::generate(buf_list.begin(), buf_list.end(), Random(m));
		for (std::list<int>::iterator it = buf_list.begin(); it != buf_list.end(); ++it)
			*fout << *it << std::endl;
	}
	return *fout;
}

std::list<int>& fill_container_with_numbers(std::fstream& file) {
	std::list<int>* list = new std::list<int>();
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
				list->push_back(num);
			}
			catch(std::exception e){}
		}
	}
	return *list;
}

std::list<int>& modify(std::list<int> lst) {
	std::list<int>* modified_list = new std::list<int>(lst.begin(), lst.end());
	int last_negative = 1;
	std::list<int>::reverse_iterator it = lst.rbegin();
	while ((last_negative == 1) && (it != lst.rend())) {
		if (*it < 0) {
			last_negative = *it / 2;
		}
		++it;
	}
	if (last_negative == 1) { last_negative = 0; }
	for (std::list<int>::iterator it = modified_list->begin(); it != modified_list->end(); ++it) {
		*it = *it + last_negative;
	}
	return *modified_list;
}

std::list<int>& modify(std::list<int> *list, std::list<int>::iterator first, std::list<int>::iterator last) {
	int last_negative = 1;
	std::list<int>::iterator it = first;
	while (it != last) {
		if (*it < 0) {
			last_negative = *it / 2;
		}
		++it;
	}
	if (last_negative == 1) { last_negative = 0; }
    std::list<int>* modified_list = new std::list<int>(*list);
    std::list<int>::iterator it1 = modified_list->begin(), it2 = list->begin();
    bool change = false;
    while (it2 != last) {
        if (!change) {
            change = it2 == first;
        }
        if (change) {
            *it1 = *it1 + last_negative;
        }
        ++it1;
        ++it2;
    }
	return *modified_list;
}

struct functor_1 {
	functor_1(int x) : x(x) {}
	int operator()(int x1) { return x + x1; }

private:
	int x;
};

std::list<int>& modify_transform(std::list<int> lst) {
	std::list<int>* modified_list = new std::list<int>(lst.size());
	int last_negative = 1;
	std::list<int>::reverse_iterator it = lst.rbegin();
	while ((last_negative == 1) && (it != lst.rend())) {
		if (*it < 0) {
			last_negative = *it / 2;
		}
		++it;
	}
	if (last_negative == 1) { last_negative = 0; }
	std::transform(lst.begin(), lst.end(), modified_list->begin(), functor_1(last_negative));
	return *modified_list;
}

struct functor_2 {
	functor_2(int x) : x(x) {}
	void operator()(int &x1) { x1 = x + x1; }

private:
	int x;
};

std::list<int>& modify_foreach(std::list<int> lst) {
	std::list<int>* modified_list = new std::list<int>(lst.begin(), lst.end());
	int last_negative = 1;
	std::list<int>::reverse_iterator it = lst.rbegin();
	while ((last_negative == 1) && (it != lst.rend())) {
		if (*it < 0) {
			last_negative = *it / 2;
		}
		++it;
	}
	if (last_negative == 1) { last_negative = 0; }
	std::for_each(modified_list->begin(), modified_list->end(), functor_2(last_negative));
	return *modified_list;
}

bool sum_container(std::list<int> list, int& sum) {
    sum = 0;
    std::list<int>::iterator it = list.begin();
    while (it != list.end()) {
        sum += *it;
        ++it;
    }
    return list.size() != 0;
}

void sum_container_action() {
    system("cls");
    int sum;
    if (!sum_container(*list, sum)) {
        std::cout << "Контейнер пуст." << std::endl;
    } else {
        std::cout << "Сумма чисел в контейнере = " << sum << std::endl;
    }
    system("pause");
}

bool avg_container(std::list<int> list, float& avg) {
    int sum;
    sum_container(list, sum);
    if (list.size() != 0) {
        avg /= list.size();
    }
    return list.size() != 0;
}

void avg_container_action() {
    system("cls");
    float avg;
    if (avg_container(*list, avg)) {
        std::cout << "Среднее арифметическое элементов контейнера = " << avg << std::endl;
    } else {
        std::cout << "" << std::endl;
    }
    system("pause");
}

bool show_container(std::list<int> list) {
    if ((list.size() == 0)) {
        return false;
    } else {
        std::list<int>::iterator it = list.begin();
        while (it != list.end()) {
            std::cout << *it << std::endl;
            ++it;
        }
        return true;
    }
}

void show_container_action() {
    system("cls");
    if (!show_container(*list)) {
        std::cout << "Контейнер пуст!" << std::endl;
    }
    system("pause");
}

bool get_fill_params(std::string& file_name, int& size, int& max) {
    std::cout << "Введите имя файла (если файл существует, он будет перезаписан. Пустая строка - отмена.):" << std::endl;
    std::getline(std::cin, file_name);
    if (file_name == "") {
        return false;
    }
    size = -1;
    while ((size < 1) || (size >= INT_MAX)) {
        std::cout << "Введите количество чисел:" << std::endl;
        getChoice(1, INT_MAX, size);
    }
    max = -1;
    while ((max < 1) || (max >= INT_MAX)) {
        std::cout << "Введите правую границу для генерации чисел:" << std::endl;
        getChoice(1, INT_MAX, max);
    }
    return true;
}

void fill_file_action() {
    system("cls");
    std::cout << "Выберите один из пунктов меню:" << std::endl;
    std::cout << "1. Генерация файла через цикл." << std::endl;
    std::cout << "2. Генерация файла через generate." << std::endl;
    std::cout << "0. Выход." << std::endl;
    int choice_number = -1;
    while ((choice_number < 0) || (choice_number > 2)) {
        getChoice(0, 2, choice_number);
    }
    switch (choice_number) {
    case 1: {
        system("cls");
        int size = -1, max = -1;
        if (get_fill_params(file_name, size, max)) {
            file = &fill_file_with_numbers(size, max, file_name);
        }
        break;
    }
    case 2: {
        system("cls");
        int size = -1, max = -1;
        if (get_fill_params(file_name, size, max)) {
            file = &fill_file_with_numbers_generate(size, max, file_name);
        }
        break;
    }
    default: break;
    }

}

void fill_container_action() {
    if (file_name == "") {
        std::cout << "Введите имя файла (Пустая строка - отмена.):" << std::endl;
        std::getline(std::cin, file_name);
        if (file_name == "") {
            return;
        }
        file = new std::fstream(file_name, std::fstream::in | std::fstream::out);
    }
    list = &fill_container_with_numbers(*file);
}

void modify_container_action() {
    system("cls");
    std::cout << "Выберите один из пунктов меню:" << std::endl;
    std::cout << "1. Модификация через modify(list)." << std::endl;
    std::cout << "2. Модификация через modify(first, last)." << std::endl;
    std::cout << "3. Модификация через modify_transform(list)." << std::endl;
    std::cout << "4. Модификация через modify_for_each(list)." << std::endl;
    std::cout << "0. Выход." << std::endl;
    int choice_number = -1;
    while ((choice_number < 0) || (choice_number > 4)) {
        getChoice(0, 4, choice_number);
    }
    switch (choice_number) {
    case 1: {
        *list = modify(*list);
        break;
    }
    case 2: {
        int size = list->size();
        std::cout << "Введите позицию начала изменения от 1 до " + std::to_string(size) << std::endl;
        int begin = -1;
        getChoice(1, size, begin);
        std::cout << "Введите позицию конца изменения от " + std::to_string(begin) + " до " + std::to_string(size) << std::endl;
        int end = -1;
        getChoice(begin, size, end);
        std::list<int>::iterator first, last, it = list->begin();
        int i = 1;
        while (i <= end) {
            if (i == begin) { first = it; }
            if (i == end) { last = it; }
            ++i;
            ++it;
        }
        *list = modify(list, first, last);
        break;
    }
    case 3: {
        *list = modify_transform(*list);
        break;
    }
    case 4: {
        *list = modify_foreach(*list);
        break;
    }
    }
}

void create_menu_action(int choice) {
	switch (choice) {
	    case 1: {
            fill_file_action();
            break;
	    }
        case 2: {
            fill_container_action();
            break;
        }
        case 3: {
            if (list != NULL) modify_container_action();
            break;
        }
        case 4: {
            if (list != NULL) sum_container_action();
            break;
        }
        case 5: {
            if (list != NULL) avg_container_action();
            break;
        }
        case 6: {
            if (list != NULL) show_container_action();
            break;
        }
        default: {break; }
	}
}

int main()
{
	setlocale(LC_ALL, "russian");
    int choice_number = -1;
    while (choice_number != 0) {
        choice_number = main_menu();
        create_menu_action(choice_number);
    }
    if (file != NULL) {
        file->close();
    }
    return 0;
}

