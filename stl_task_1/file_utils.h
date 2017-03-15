#pragma once

//функция заполнения файла числами с использованием цикла
std::fstream& fill_file_with_numbers(int n, int m, std::string filename);

//заполнение файла числами с использованием generate
std::fstream& fill_file_with_numbers_generate(int n, int m, std::string filename);

//функция для получения параметров для заполнения файла
bool get_fill_params(std::string& file_name, int& size, int& max);