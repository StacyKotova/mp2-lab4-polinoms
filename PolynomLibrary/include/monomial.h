#ifndef MONOMIAL_H
#define MONOMIAL_H

#include <string>

// ����� "��������"
class Monomial
{
	double coeff; // �����������
	int pow; // ���������� x, y, z

public:
	// ����������� �� ���������
	Monomial();
	// ����������� � �����������
	Monomial(double coeff, int pow);
	
	// ��������� ������������
	double getCoeff() const;
	// ��������� �������
	int getPow() const;
	// ��������� ������������
	void setCoeff(double coeff);
	// ��������� �������
	void setPow(int pow);

	// ���������� ���������� ��������� <, >, =
	friend bool operator<(const Monomial& m1, const Monomial& m2);
	friend bool operator>(const Monomial& m1, const Monomial& m2);
	friend bool operator==(const Monomial& m1, const Monomial& m2);
	// ���������� ��������� ���������� ������
	friend std::ostream& operator<<(std::ostream& os, const Monomial& m);
};

#endif /* MONOMIAL_H */