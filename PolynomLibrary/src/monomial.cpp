#include "../include/monomial.h"
#include <sstream>
#include <string>

// ����������� �� ���������
Monomial::Monomial()
{

}

// ����������� � �����������
Monomial::Monomial(double coeff, int pow)
{
	this->coeff = coeff;
	this->pow = pow;
}

// ��������� ������������
double Monomial::getCoeff() const
{
	return this->coeff;
}

// ��������� �������
int Monomial::getPow() const
{
	return this->pow;
}

// ��������� ������������
void Monomial::setCoeff(double coeff)
{
	this->coeff = coeff;
}

// ��������� �������
void Monomial::setPow(int pow)
{
	this->pow = pow;
}

// ���������� ��������� <
bool operator<(const Monomial& m1, const Monomial& m2)
{
	return m1.pow < m2.pow;
}

// ���������� ��������� >
bool operator>(const Monomial& m1, const Monomial& m2)
{
	return m1.pow > m2.pow;
}

// ���������� ��������� ==
bool operator==(const Monomial& m1, const Monomial& m2)
{
	return m1.pow == m2.pow;
}

// ���������� ��������� ���������� ������
std::ostream& operator<<(std::ostream& os, const Monomial& m)
{
	// ����� ������������ (���� ��� ������� �������, ��������� ������ �����������)
	os << m.getCoeff();

	if (m.getPow() != 0)
	{
		os << " * ";

		// ��������� �������� x, y, z
		int pow = m.getPow();
		int x = pow / 100;
		int y = (pow / 10) % 10;
		int z = pow % 10;

		// ����� �������� x, y, z (��������� �������� ����� ���������)
		if (x == 1)
			os << "x";
		else if (x > 1)
			os << "x^" << x;

		if (x > 0 && (y > 0 || z > 0))
			os << "*";

		if (y == 1)
			os << "y";
		else if (y > 1)
			os << "y^" << y;

		if (y > 0 && z > 0)
			os << "*";

		if (z == 1)
			os << "z";
		else if (z > 1)
			os << "z^" << z;
	}

	return os;
}