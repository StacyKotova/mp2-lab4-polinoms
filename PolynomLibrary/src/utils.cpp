/*
	��������������� �������
*/


#include "../include/utils.h"
#include <sstream>

// ��������, ����� �� ���� ����� a � b �������� ��� ������������
bool isMultiplicative(int a, int b)
{
	if (a < 0 || a > 999) // �������� �������� ����� a
		throw std::exception("�������� ���������� a ������ ���� �� 0 �� 999");

	if (b < 0 || b > 999) // �������� �������� ����� b
		throw std::exception("�������� ���������� b ������ ���� �� 0 �� 999");

	if (a > 9 && a < 99) // ���������� � ����������� ���������� ��������
		b = b % 100;
	else if (a < 9)
		b = b % 10;

	while (a > 0) // ���� ��������� �� ��� �������
	{
		if (a % 10 + b % 10 > 9) // ���� ������������, ����� �� �������
			return false; 
		a = a / 10; // ������� � ���������� ������� ����� a
		b = b / 10; // ������� � ���������� ������� ����� b
	}

	return true;
}

// ���������� �� ������ s ��������� �������� (����������� - ������ delim)
std::vector<double> splitAndRemoveNullCoeffs(const std::string &s, char delim) 
{
	std::stringstream ss(s); // ����� �����
	std::string item; // �������� ������������ ��������
	std::vector<double> elems; // �������������� ������
	
	int i = 1;
	while (std::getline(ss, item, delim)) // ���� ������ �� ���������
	{
		double a = atof(item.c_str()); // ����������� ������ � ������������ �����
		if (a || i % 2 == 0) // ���� �� 0 (�� ���� ���� �� �����, ���� ���� - �� ������� ������ �� �����)
		{
			elems.push_back(a); // ���������� � ������
			i++;
		}
	}
	
	// ���� ������ �������� �� ����� ������ ��������, �� ������ ������� ��������
	if (elems.size() < 2)
	{
		elems.clear();
		elems.push_back(0);
		elems.push_back(0);
	}

	return elems;
}