#include "stdafx.h"
#include "file_utils.h"
#include "help_utils.h"

//функция заполнения файла числами с использованием цикла
std::fstream& fill_file_with_numbers(int n, int m, std::string filename)
{
    srand(time(NULL));
    std::fstream* fout = new std::fstream(filename, std::fstream::in | std::fstream::out | std::fstream::trunc);
    if (fout->is_open()) {
        double random_number;
        for (int i = 1; i <= n; ++i) {
            random_number = double(std::rand() % (2 * m) - m);
            *fout << random_number << std::endl;
        }
    }
    return *fout;
}

//структура для генерации рандомных чисел в диапазоне [-m, m]
struct Random {
public:
    Random(int m) { max = m; }
    double operator()();
private:
    int max;
};

double Random::operator()() {
    return double((std::rand()) % (2 * max) - max);
}

//заполнение файла числами с использованием generate
std::fstream& fill_file_with_numbers_generate(int n, int m, std::string filename)
{
    srand(time(NULL));
    std::fstream* fout = new std::fstream(filename, std::fstream::in | std::fstream::out | std::fstream::trunc);
    if (fout->is_open()) {
        std::list<double> buf_list(n);
        std::generate(buf_list.begin(), buf_list.end(), Random(m));
        for (std::list<double>::iterator it = buf_list.begin(); it != buf_list.end(); ++it)
            *fout << *it << std::endl;
    }
    return *fout;
}

//функция для получения параметров для заполнения файла
bool get_fill_params(std::string& file_name, int& size, int& max) {
    std::cout << "Введите имя файла (если файл существует, он будет перезаписан. Пустая строка - отмена.):" << std::endl;
    std::getline(std::cin, file_name);
    if (file_name == "") {
        return false;
    }
    size = -1;
    while ((size < 1) || (size >= INT_MAX)) {
        std::cout << "Введите количество чисел:" << std::endl;
        getChoice(1, INT_MAX, size);
    }
    max = -1;
    while ((max < 1) || (max >= INT_MAX)) {
        std::cout << "Введите правую границу для генерации чисел:" << std::endl;
        getChoice(1, INT_MAX, max);
    }
    return true;
}