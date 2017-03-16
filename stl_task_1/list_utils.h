#pragma once

//���������� ���������� �� �����
std::list<int>& fill_container_with_numbers(std::fstream& file);

//����������� ����������
std::list<int>& modify(std::list<int> lst);

//����������� ����� ����������
std::list<int>& modify(std::list<int> &list, std::list<int>::iterator first, std::list<int>::iterator last);

//������� ��� ����������� ����� transform
std::list<int>& modify_transform(std::list<int> lst);

//������� ��� ����������� ����� for_each
std::list<int>& modify_foreach(std::list<int> lst);

//������� ������������ ����������
bool sum_container(std::list<int> list, int& sum);

//���������� �������� ��������������� ����������
bool avg_container(std::list<int> list, float& avg);