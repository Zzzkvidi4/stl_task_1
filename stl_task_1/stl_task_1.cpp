// stl_task_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include "list_utils.h"
#include "file_utils.h"
#include "help_utils.h"

std::string file_name = "";
std::fstream* file;

/* Задача 10С - к элементам контейнера list добавить половину последнего отрицательного элемента*/

//функция для отображения главного меню
void print_menu(std::list<double> list)
{
    system("cls");
	std::cout << "1. Заполнение текстового файла числами" << std::endl;
	std::cout << "2. Заполнение контейнера из файла" << std::endl;
	std::cout << "3. Преобразование контейнера" << std::endl;
	std::cout << "4. Сумма" << std::endl;
	std::cout << "5. Среднее арифметическое" << std::endl;
	std::cout << "6. Вывод" << std::endl;
	std::cout << "0. Выход" << std::endl;
    if (list.size() == 0) { std::cout << "Внимание, список не существует! Некоторые действия недоступны!" << std::endl; }
}

//функция главного меню с возвратом выбора
int main_menu(std::list<double> list) {
	std::string choice = "";
	int choice_number = -1;
	while ((choice_number < 0) || (choice_number > 7))
	{
		print_menu(list);
		getChoice(0, 7, choice_number);
	}
	return choice_number;
}

//действие по суммированию контейнера
void sum_container_action(std::list<double> list) {
    system("cls");
    if (list.size() == 0) {
        std::cout << "Контейнер пуст." << std::endl;
    } else {
        show_container(list);
        std::cout << "Сумма чисел в контейнере = " << sum_container(list) << std::endl;
    }
    system("pause");
}

//действие по вычислению среднего арифметического
void avg_container_action(std::list<double> list) {
    system("cls");
    if (list.size() == 0) {
        std::cout << "Контейнер пуст." << std::endl;
    } else {
        show_container(list);
        std::cout << "Среднее арифметическое чисел в контейнере = " << avg_container(list) << std::endl;
    }
    system("pause");
}

//действие для демонстрации контейнера
void show_container_action(std::list<double> list) {
    system("cls");
    if (list.size() == 0) {
        std::cout << "Контейнер пуст!" << std::endl;
    } else {
        show_container(list);
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
	file->close();
	file_name = "";
}

//действие по заполнению контейнера
void fill_container_action(std::list<double>& list) {
    if (file_name == "") {
        std::cout << "Введите имя файла (Пустая строка - отмена.):" << std::endl;
        std::getline(std::cin, file_name);
        if (file_name == "") {
            return;
        }
        file = new std::fstream(file_name, std::fstream::in | std::fstream::out);
    }
    if (list.size() != 0) { list.clear(); }
    list = fill_container_with_numbers(*file);
	file->close();
	file_name = "";
}

//действие по модификации контейнера
void modify_container_action(std::list<double> list) {
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
    std::cout << "Контейнер до модификации:" << std::endl;
    show_container(list);
    std::cout << "Контейнер после модификации:" << std::endl;
    std::list<double> modified_list(list);
    try {
        switch (choice_number) {
        case 1: {
            modify(modified_list);
            break;
        }
        case 2: {
            int size = modified_list.size();
            int begin = -1;
			while ((begin < 1) || (begin > size)) {
				std::cout << "Введите позицию начала изменения от 1 до " + std::to_string(size) << std::endl;
				getChoice(1, size, begin);
			}
            
            int end = -1;
			while ((end <= begin) || (end > size + 1)) {
				std::cout << "Введите позицию конца изменения от " + std::to_string(begin + 1) + " до " + std::to_string(size + 1) << std::endl;
				getChoice(begin + 1, size + 1, end);
			}
            std::list<double>::iterator first, last, it = modified_list.begin();
            int i = 1;
            while (i <= end) {
                if (i == begin) { first = it; }
                if (i == end) { last = it; }
                ++i;
				if (it != modified_list.end()) { ++it; }
            }
            modify(modified_list, first, last);
            break;
        }
        case 3: {
            modify_transform(modified_list);
            break;
        }
        case 4: {
            modify_foreach(modified_list);
            break;
        }
        default: {break; }
        }
    }
    catch (std::exception e) {
        std::cout << e.what() << std::endl;
    }
    show_container(modified_list);
    system("pause");
}

//выполнение пунктов меню
void create_menu_actions(int choice, std::list<double>& list) {
	switch (choice) {
	    case 1: {
            fill_file_action();
            break;
	    }
        case 2: {
            fill_container_action(list);
            break;
        }
        case 3: {
            if (list.size() != 0) modify_container_action(list);
            break;
        }
        case 4: {
            if (list.size() != 0) sum_container_action(list);
            break;
        }
        case 5: {
            if (list.size() != 0) avg_container_action(list);
            break;
        }
        case 6: {
            if (list.size() != 0) show_container_action(list);
            break;
        }
        default: {break; }
	}
}

int main()
{
    std::list<double> list;
	setlocale(LC_ALL, "russian");
    int choice_number = -1;
    while (choice_number != 0) {
        choice_number = main_menu(list);
        create_menu_actions(choice_number, list);
    }
    if (file != NULL) {
        file->close();
    }
    return 0;
}

