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
	std::cout << "1. ���������� ���������� ����� �������" << std::endl;
	std::cout << "2. ���������� ���������� �� �����" << std::endl;
	std::cout << "3. �������������� ����� ����������" << std::endl;
	std::cout << "4. �������������� ����� ����������" << std::endl;
	std::cout << "5. �����" << std::endl;
	std::cout << "6. ������� ��������������" << std::endl;
	std::cout << "7. �����" << std::endl;
	std::cout << "0. �����" << std::endl;
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
				print_message("�� ������ ������ ����� �� 0 �� 7!");
			}
		}
		catch (std::invalid_argument e)
		{
			print_message("�� ������ ������ �����!");
		}
		catch (std::out_of_range e)
		{
			print_message("����� �� ������� ����!");
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

