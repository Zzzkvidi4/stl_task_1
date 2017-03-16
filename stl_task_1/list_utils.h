#pragma once

//заполнение контейнера из файла
std::list<double>& fill_container_with_numbers(std::fstream& file);

//модификация контейнера
void modify(std::list<double>& list);

//модификация части контейнера
void modify(std::list<double>& list, std::list<double>::iterator first, std::list<double>::iterator last);

//функция для модификации через transform
void modify_transform(std::list<double>& list);

//функция для модификации через for_each
void modify_foreach(std::list<double>& list);

//функция суммирования контейнера
double sum_container(std::list<double> list);

//вычисление среднего арифмитического контейнера
double avg_container(std::list<double> list);

//функция для демонстрация контейнера
void show_container(std::list<double> list);