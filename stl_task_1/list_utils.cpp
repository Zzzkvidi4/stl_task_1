#include "stdafx.h"
#include "list_utils.h"

//���������� ���������� �� �����
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
            catch (std::exception e) {}
        }
    }
    return *list;
}

//����������� ����������
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

//����������� ����� ����������
std::list<int>& modify(std::list<int> &list, std::list<int>::iterator first, std::list<int>::iterator last) {
    int last_negative = 1;
    std::list<int>::iterator it = first;
    while (it != last) {
        if (*it < 0) {
            last_negative = *it / 2;
        }
        ++it;
    }
    if (last_negative == 1) { last_negative = 0; }
    std::list<int>* modified_list = new std::list<int>(list);
    std::list<int>::iterator it1 = modified_list->begin(), it2 = list.begin();
    bool change = false;
    while (it2 != last) {
        if (!change) {
            change = it2 == first;
        }
        if (change) {
            *it1 = *it1 + last_negative;
        }
        ++it1;
        ++it2;
    }
    return *modified_list;
}

//��������� ��� ����������� ��������� ����� transform
struct functor_1 {
    functor_1(int x) : x(x) {}
    int operator()(int x1) { return x + x1; }

private:
    int x;
};

//������� ��� ����������� ����� transform
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

//��������� ��� ����������� ����� for_each
struct functor_2 {
    functor_2(int x) : x(x) {}
    void operator()(int &x1) { x1 = x + x1; }

private:
    int x;
};

//������� ��� ����������� ����� for_each
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

//������� ������������ ����������
bool sum_container(std::list<int> list, int& sum) {
    sum = 0;
    std::list<int>::iterator it = list.begin();
    while (it != list.end()) {
        sum += *it;
        ++it;
    }
    return list.size() != 0;
}

//���������� �������� ��������������� ����������
bool avg_container(std::list<int> list, float& avg) {
    int sum;
    sum_container(list, sum);
    if (list.size() != 0) {
        avg = float(sum) / float(list.size());
    }
    return list.size() != 0;
}