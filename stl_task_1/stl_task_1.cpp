// stl_task_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <time.h> 
#include "iostream"
#include "string"
#include "fstream"
#include "list"
#include "algorithm"

void print_message(std::string msg)
{
	std::cout << msg << std::endl;
	system("pause");
	system("cls");
}

void print_menu()
{
	std::cout << "1. Заполнение текстового файла числами" << std::endl;
	std::cout << "2. Заполнение контейнера из файла" << std::endl;
	std::cout << "3. Преобразование всего контейнера" << std::endl;
	std::cout << "4. Преобразование части контейнера" << std::endl;
	std::cout << "5. Сумма" << std::endl;
	std::cout << "6. Среднее арифметическое" << std::endl;
	std::cout << "7. Вывод" << std::endl;
	std::cout << "0. Выход" << std::endl;
}

int main_menu() {
	std::string choice = "";
	int choice_number = -1;
	while ((choice_number < 0) || (choice_number > 7))
	{
		print_menu();
		try {
			std::getline(std::cin, choice);
			choice_number = std::stoi(choice);
			if ((choice_number < 0) || (choice_number > 7))
			{
				print_message("Вы должны ввести число от 0 до 7!");
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

std::fstream& fill_file_with_numbers_generate(int n, int m, std::string filename)
{
	srand(time(NULL));
	std::fstream* fout = new std::fstream(filename, std::fstream::in | std::fstream::out | std::fstream::trunc);
	if (fout->is_open()) {
		std::list<int> buf_list(n);
		std::generate(buf_list.begin(), buf_list.end(), std::rand);
		for (std::list<int>::iterator it = buf_list.begin(); it != buf_list.end(); ++it)
			*fout << (*it) % (2 * m) - m << std::endl;
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

std::list<int>& modify(std::list<int>::iterator first, std::list<int>::iterator last) {
	std::list<int>* modified_list = new std::list<int>(first, last);
	int last_negative = 1;
	std::list<int>::iterator it = first;
	while (it != last) {
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



int main()
{
	setlocale(LC_ALL, "russian");
	//main_menu();
	std::fstream& f1 = fill_file_with_numbers(5, 4, "some_buf.txt");
	std::fstream& f2 = fill_file_with_numbers_generate(5, 4, "2.txt");
	std::list<int>& list = fill_container_with_numbers(f1);
	std::list<int>& modified_list = modify(list);
	std::list<int>& modified_list_2 = modify_transform(list);
	std::list<int>& modified_list_3 = modify_foreach(list);
	std::cout << "Some string" << std::endl;
	f2.close();
	std::fstream f("some_buf.txt");
	int num;
	if (f.is_open())
	{
		std::cout << "открыт" << std::endl;
		while (!f.eof())
		{
			try {
				f >> num;
				std::cout << num << std::endl;
			}
			catch(std::exception e){}
		}
	}
	else
	{
		std::cout << "не открыт" << std::endl;
	}
	f1.close();
	f.close();
	system("pause");
    return 0;
}

