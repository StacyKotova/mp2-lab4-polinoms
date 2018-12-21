#include "../include/polynomial.h"
#include "../include/utils.h"
#include <cmath>
#include <sstream>

// �������������� ����������
void Polynomial::arrange()
{
	monomials->sort();
}

// ���������� �������� ���������
void Polynomial::combineLikeTerms()
{
	arrange(); // ��������������
	Node<Monomial> *a = monomials->getHead(); // ��������� ������
	if (a != nullptr) // ���� ��� �� �����
		while (a->next != nullptr) // ���� �� ���� ���������
		{
			Node<Monomial> *b = a->next;
			if (a->data.getPow() == b->data.getPow()) // ���� ������� ������� �����
			{
				// ����������� 1�� - ����� �������������
				a->data.setCoeff(a->data.getCoeff() + b->data.getCoeff());
				// �������� 2�� (� ���������, �� �������� �� ������)
				if (b == this->getMonomials()->getTail())
				{
					b = b->prev;
					b->next = nullptr;
				}
				else
				{
					b->prev->next = b->next;
					b->next->prev = b->prev;
				}
			}
			a = b;
		}

	a = monomials->getHead();
	// �������� ��������� ����� (���� ���� ������ ����, �� �� ���������)
	while (a != nullptr)
	{
		if (a->data.getCoeff() == 0)
		{
			// ���� ������
			if (a == this->getMonomials()->getHead())
			{
				if (a->next == nullptr)
					break;
				a = a->next;
				a->prev = nullptr;
			}
			// ���� �����
			else if (a == this->getMonomials()->getTail())
			{
				a = a->prev;
				a->next = nullptr;
			}
			// �����
			else
			{
				a->prev->next = a->next;
				a->next->prev = a->prev;
			}
		}
		a = a->next;
	}
}

// ����������� �� ���������
Polynomial::Polynomial()
{
	monomials = new List<Monomial>();
}

// ����������� (�������� - ������ �������)
Polynomial::Polynomial(const List<Monomial>& monomials)
{
	this->monomials = new List<Monomial>(monomials);
}

// ����������� (�������� - ������)
Polynomial::Polynomial(std::string s)
{
	monomials = new List<Monomial>();
	auto v = splitAndRemoveNullCoeffs(s, ';');
	if (v.size() % 2 == 1)
	{
		throw std::exception();
	}
	else
		for (size_t i = 0; i < v.size(); i += 2)
		{
			double j = 0;
			double f = modf(v[i + 1], &j);
			if (j < 0 || j > 999)
				throw std::exception();
			this->addMonomial(Monomial(v[i], (int)j));
		}
	combineLikeTerms();
}

// ��������� ������ �������
List<Monomial>* Polynomial::getMonomials() const
{
	return monomials;
}

// ���������� ���������
void Polynomial::addMonomial(const Monomial& m)
{
	monomials->push_back(m);
}

// ���������� ��������� +
Polynomial operator+(const Polynomial& p1, const Polynomial& p2)
{
	// ��������� ������ ��������� �����������
	Node<Monomial> *a = p1.getMonomials()->getHead(),
		*b = p2.getMonomials()->getHead();
	Polynomial c;

	// ���� ��� �� �����������
	while (a != nullptr && b != nullptr)
	{
		if (a->data > b->data) // ���� ������� 1�� ������ ������
		{
			c.addMonomial(a->data); // ������ 1�� ������
			a = a->next; // �������� �� 1�� ����������
		}
		else if (a->data < b->data) // ���� ������� 2�� ������ ������
		{
			c.addMonomial(b->data); // ������ 2�� ������
			b = b->next; // �������� �� 2�� ����������
		}
		else // ���� �����
		{
			double cCoeff = a->data.getCoeff() + b->data.getCoeff();
			if (cCoeff != 0) // ���� ����� ����������� �� ����
				c.addMonomial(Monomial(cCoeff, a->data.getPow())); // ��������� �����
			a = a->next; // �������� �� ����� �����������
			b = b->next;
		}
	}

	while (a != nullptr) // ���������� ������������� ������� �� 1�� ����������
	{
		c.addMonomial(a->data);
		a = a->next;
	}

	while (b != nullptr) // ���������� ������������� ������� �� 2�� ����������
	{
		c.addMonomial(b->data);
		b = b->next;
	}

	c.combineLikeTerms(); // ���������� ��������
	return c;
}

// ���������� ��������� -
Polynomial operator-(const Polynomial& p1, const Polynomial& p2)
{
	Polynomial p3 = p2 * -1.0,
		p4 = p1 + p3;
	p4.combineLikeTerms(); // ���������� ��������
	return p4;
}

// ���������� ��������� *
Polynomial operator*(const Polynomial& p1, const Polynomial& p2)
{
	Node<Monomial> *a = p1.getMonomials()->getHead();
	Polynomial c;

	while (a != nullptr) // ���� �� �������� 1� ���������
	{
		Node<Monomial> *b = p2.getMonomials()->getHead(); 
		while (b != nullptr) // ���� �� �������� 1� ���������
		{
			// ���� ������������, �� ����������
			if (!isMultiplicative(a->data.getPow(), b->data.getPow()))
				throw std::overflow_error("��������� ������������!");
			// ������������ ������������ � ������������ �����������
			c.addMonomial(Monomial(a->data.getCoeff() * b->data.getCoeff(),
				a->data.getPow() + b->data.getPow()));
			b = b->next;
		}
		a = a->next;
	}

	c.combineLikeTerms();
	return c;
}

// ���������� ��������� *
Polynomial operator*(const Polynomial& p, double c)
{
	Node<Monomial> *a = p.getMonomials()->getHead();
	Polynomial b;
	if (c != 0)
	{
		while (a != nullptr) // ���� �� �������� ���������
		{
			b.addMonomial(Monomial(a->data.getCoeff() * c,
				a->data.getPow())); // ��������� ������������
			a = a->next;
		}
		b.combineLikeTerms(); // ���������� ��������
		return b;
	}
	else
		return Polynomial();
}

// ���������� ��������� *
Polynomial operator*(double c, const Polynomial& p)
{
	return p * c;
}

// ���������� ��������� ���������� ������
std::ostream& operator<<(std::ostream& os, const Polynomial& p)
{
	Node<Monomial>* i = p.getMonomials()->getHead();
	if (i != nullptr) // ���� ������� ������� �� ����� ������
		while (i->next != nullptr) // ���� ��������� ������� �� ����� ������
		{
			os << i->data << " + "; // ���������� �����, ��������� +
			i = i->next;
		}
	else 
		os << 0; // ������ ������� ����������
	if (i != nullptr) // ���������� ����� ������
		os << i->data;
	return os;
}

// ��������� ������������� ����������
std::string Polynomial::to_string()
{
	// ������ � ��������� �����
	std::string result;
	std::stringstream stream(result);
	stream << *this;
	// ��������� ������ �� ������
	return stream.str();
}