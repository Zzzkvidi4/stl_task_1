#pragma once

//заполнение контейнера из файла
std::list<int>& fill_container_with_numbers(std::fstream& file);

//модификация контейнера
std::list<int>& modify(std::list<int> lst);

//модификация части контейнера
std::list<int>& modify(std::list<int> &list, std::list<int>::iterator first, std::list<int>::iterator last);

//функция для модификации через transform
std::list<int>& modify_transform(std::list<int> lst);

//функция для модификации через for_each
std::list<int>& modify_foreach(std::list<int> lst);

//функция суммирования контейнера
bool sum_container(std::list<int> list, int& sum);

//вычисление среднего арифмитического контейнера
bool avg_container(std::list<int> list, float& avg);