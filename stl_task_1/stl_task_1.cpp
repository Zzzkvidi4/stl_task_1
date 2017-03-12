// stl_task_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
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

std::ofstream& fill_file_with_numbers(int n, int m, std::string filename)
{
	std::ofstream* fout = new std::ofstream(filename);
	if (fout->is_open()) {
		int random_number;
		for (int i = 1; i <= n; ++i) {
			random_number = std::rand() % (2 * m) - m;
			*fout << random_number << std::endl;
		}
	}
	return *fout;
}

std::ofstream& fill_file_with_numbers_generate(int n, int m, std::string filename)
{
	std::ofstream* fout = new std::ofstream(filename);
	if (fout->is_open()) {
		std::list<int> buf_list(n);
		std::generate(buf_list.begin(), buf_list.end(), std::rand);
		for (std::list<int>::iterator it = buf_list.begin(); it != buf_list.end(); ++it)
			*fout << (*it) % (2 * m) - m << std::endl;
	}
	return *fout;
}


int main()
{
	setlocale(LC_ALL, "russian");
	//main_menu();
	std::ofstream& f1 = fill_file_with_numbers(5, 4, "some.txt");
	std::ofstream& f2 = fill_file_with_numbers_generate(5, 4, "2.txt");
	std::cout << "Some string" << std::endl;
	f1.close();
	f2.close();
	std::ifstream f("some.txt");
	int num;
	if (f.is_open())
	{
		std::cout << "открыт" << std::endl;
		while (!f.eof())
		{
			f >> num;
			std::cout << num << std::endl;
		}
	}
	else
	{
		std::cout << "не открыт" << std::endl;
	}
	f.close();
	system("pause");
    return 0;
}

