// stl_task_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"
#include "string"

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


int main()
{
	setlocale(LC_ALL, "russian");
	main_menu();
	std::cout << "Some string" << std::endl;
	system("pause");
    return 0;
}

