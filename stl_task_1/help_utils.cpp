#include "stdafx.h"
#include "help_utils.h"

//функция для вывода сообщений
void print_message(std::string msg)
{
    std::cout << msg << std::endl;
    system("pause");
}

//функция получения одного из вариантов между min и max
void getChoice(int min, int max, int& choice_number) {
    std::string choice = "";
    try {
        std::getline(std::cin, choice);
        choice_number = std::stoi(choice);
        if ((choice_number < min) || (choice_number > max))
        {
            print_message("Вы должны ввести число от " + std::to_string(min) + " до " + std::to_string(max) + "!");
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