#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include "list.h"
#include "monomial.h"
#include <string>

// ����� "���������"
class Polynomial
{
	// ������ ����������
	List<Monomial>* monomials;

	// �������������� ����������
	void arrange();
	// ���������� �������� ���������
	void combineLikeTerms();

public:
	// ����������� �� ���������
	Polynomial();
	// ����������� (�������� - ������ �������)
	Polynomial(const List<Monomial>& monomials);
	// ����������� (�������� - ������)
	Polynomial(std::string s);
	
	// ��������� ������ �������
	List<Monomial>* getMonomials() const;
	// ���������� ���������
	void addMonomial(const Monomial& m);
	
	// ���������� �������������� ����������
	friend Polynomial operator+(const Polynomial& p1, const Polynomial& p2);
	friend Polynomial operator-(const Polynomial& p1, const Polynomial& p2);
	friend Polynomial operator*(const Polynomial& p1, const Polynomial& p2);
	friend Polynomial operator*(const Polynomial& p, double c);
	friend Polynomial operator*(double c, const Polynomial& p);
	// ���������� ��������� ���������� ������
	friend std::ostream& operator<<(std::ostream& os, const Polynomial& p);

	// ��������� ������������� ����������
	std::string to_string();
};

#endif /* POLYNOMIAL_H */