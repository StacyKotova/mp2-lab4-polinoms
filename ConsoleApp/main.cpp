#include "polynomial.h"
#include <iostream>
#include <string>

int main()
{
	setlocale(LC_CTYPE, "Russian");

	std::cout << "������:\n";
	std::cout << "��� �������� 4 * x ^ 4 * y ^ 2 * z ������ ����� 4; 421\n";
	std::cout << "��� �������� x*y*z + y*z ^ 5 ������ ����� 1; 111; 1; 15\n";
	std::cout << "�� ���� ��� ������� ������ ������ ����� - ����������� ��� ���������, \n����� ����� � �������, ����� ����� �� 0 �� 999 - ����������\n";
	std::cout << "105 = x ^ 1 y ^ 0 z ^ 5\n";
	std::cout << "256 = x ^ 2 y ^ 5 z ^ 6\n";
	std::cout << "8 = z ^ 8\n";
	std::cout << "60 = y ^ 6\n";
	std::cout << "200 = x ^ 2\n";

	while (true)
	{
		try
		{
			std::cout << "������� ��������� p ��� exit ��� ������: ";
			std::string s1;
			std::cin >> s1;

			if (s1 == "exit")
				break;

			Polynomial p = Polynomial(s1);
			std::cout << "��������� p: " << p << std::endl;
			while (true)
			{
				bool b = true;
				try
				{
					std::string s;
					std::cout << "������� ����� ��������: 0 - ��������, 1 - ���������, "
						<< "2 - ���������, 3 - ��������� �� ���������: ";

					std::cin >> s;
					if (!(s == "0" || s == "1" || s == "2" || s == "3"))
					{
						throw std::exception();
					}

					int op = atoi(s.c_str());

					if (op < 0 || op > 3)
						throw std::exception();
					else
					{
						if (op < 3)
						{
							while (true)
							{
								try
								{
									std::cout << "������� ��������� q ��� exit ��� ������: ";
									std::string s2;
									std::cin >> s2;
									if (s2 == "exit")
										break;

									Polynomial q = Polynomial(s2), r;
									std::cout << "��������� q: " << q << std::endl;
									std::cout << "��������� �������� ";
									if (op == 0)
									{
										std::cout << "p + q: ";
										r = p + q;
									}
									else if (op == 1)
									{
										std::cout << "p - q: ";
										r = p - q;
									}
									else
									{
										std::cout << "p * q: ";
										r = p * q;
									}
									std::cout << r << std::endl;
									b = false;
									break;
								}
								catch (std::overflow_error& e)
								{
									std::cout << e.what() << std::endl;
								}
								catch (std::exception&)
								{
									std::cout << "�������� ������ �����! ��������� ����." << std::endl;
								}
							}
							if (!b)
								break;
						}
						else
						{
							while (true)
							{
								try
								{
									std::string s;
									std::cout << "������� ��������� �: ";
									std::cin >> s;

									double c = atof(s.c_str());

									Polynomial r = p * c;
									std::cout << "��������� �������� p * c: " << r << std::endl;
									b = false;
									break;
								}
								catch (std::exception&)
								{
									std::cout << "�������� ������ �����! ��������� ����." << std::endl;
								}
							}
							if (!b)
								break;
						}
						break;
					}
				}
				catch (std::exception&)
				{
					std::cout << "������� ����� �� 0 �� 3!" << std::endl;
					std::cin.clear();
				}
			}
		}
		catch (std::exception&)
		{
			std::cout << "�������� ������ �����! ��������� ����." << std::endl;
		}
	}
}