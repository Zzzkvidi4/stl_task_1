// stl_task_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include "list_utils.h"
#include "file_utils.h"
#include "help_utils.h"

std::string file_name = "";
std::fstream* file;
std::list<int>* list;
/* Задача 10С - к элементам контейнера list добавить половину последнего отрицательного элемента*/

//функция для отображения главного меню
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

//функция главного меню с возвратом выбора
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

//действие по суммированию контейнера
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

//действие по вычислению среднего арифметического
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

//функция для демонстрация контейнера
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

//действие для демонстрации контейнера
void show_container_action() {
    system("cls");
    if (!show_container(*list)) {
        std::cout << "Контейнер пуст!" << std::endl;
    }
    system("pause");
}

//действие по заполнению файла
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
            if (file != NULL) {
                file->close();
            }
            file = &fill_file_with_numbers(size, max, file_name);
        }
        break;
    }
    case 2: {
        system("cls");
        int size = -1, max = -1;
        if (get_fill_params(file_name, size, max)) {
            if (file != NULL) {
                file->close();
            }
            file = &fill_file_with_numbers_generate(size, max, file_name);
        }
        break;
    }
    default: break;
    }

}

//действие по заполнению контейнера
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

//действие по модификации контейнера
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
        *list = modify(*list, first, last);
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

//выполнение пунктов меню
void create_menu_actions(int choice) {
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
        create_menu_actions(choice_number);
    }
    if (file != NULL) {
        file->close();
    }
    return 0;
}

