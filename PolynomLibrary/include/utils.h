#ifndef UTILS_H
#define UTILS_H

/*
	��������������� �������
*/

#include <string>
#include <vector>

// ��������, ����� �� ���� ����� a � b �������� ��� ������������
bool isMultiplicative(int a, int b);

// ���������� �� ������ s ��������� �������� ������������� (����������� - ������ delim)
std::vector<double> splitAndRemoveNullCoeffs(const std::string &s, char delim);

#endif /* UTILS_H */