#ifndef LIST_H
#define LIST_H

/*
	����� "���������� ������"
*/

#include "node.h"

template<typename T>
class List
{
	Node<T> *head, *tail; // ��������� � �������� ��������

public:
	// ����������� ������
	List()
	{
		head = tail = nullptr;
	}

	// ��������� ���������� ��������
	Node<T>* getHead()
	{
		return head;
	}

	// ��������� ��������� ��������
	Node<T>* getTail()
	{
		return tail;
	}

	// ���������� �������� item � ������
	void push_back(const T& item)
	{
		Node<T> *tmp = new Node<T>;
		tmp->next = nullptr;
		tmp->data = item;

		if (head != nullptr)
		{
			tmp->prev = tail;
			tail->next = tmp;
			tail = tmp;
		}
		else
		{
			tmp->prev = nullptr;
			head = tail = tmp;
		}
	}

	void clear()
	{
		head = tail = nullptr;
	}

	// ���������� ������
	void sort()
	{
		Node<T> *i = head;
		if (i != nullptr)
			while (i->next != nullptr)
			{
				Node<T> *j = i->next;
				while (j != nullptr)
				{
					if (i->data < j->data)
					{
						T tmp = i->data;
						i->data = j->data;
						j->data = tmp;
					}
					j = j->next;
				}
				i = i->next;
			}
	}
};

#endif /* LIST_H */