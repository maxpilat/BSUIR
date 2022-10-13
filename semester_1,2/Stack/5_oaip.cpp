#include <iostream>
#include <stack>
#include<stdio.h>

using namespace std;


struct comp
{
	int Data;
	comp* next;
};


//Случайное заполнение стека..
comp* create(comp** top, int amount_of_elements)
{
	for (int i = 0; i < amount_of_elements; i++)
	{
		comp* q;
		q = new comp();
		q->Data = rand() % 10;
		if (top == NULL)
		{
			*top = q;
		}
		else
		{
			q->next = *top;
			*top = q;
		}
	}
	return *top;
}


//Вывод стека..
void show(comp* top)
{
	comp* q = top;
	while (q)
	{
		cout << (q->Data);
		q = q->next;
	}
	cout << endl;
}

//Индивидуальное задание.. (поменять крайние элементы стека местами)
comp* ex(comp* top)
{
	comp* q = top;

	while (q->next->next != NULL)
	{
		q = q->next;
	}
	comp* temp = top;
	top = q->next;
	top->next = temp->next;
	temp->next = NULL;
	q->next = temp;
	return top;
}

//Сортировка по адресу..
void adressSort(comp** top)
{
	comp* t = NULL, * t1, * r;
	if ((*top)->next->next == NULL) return;
	do {
		for (t1 = *top; t1->next->next != t; t1 = t1->next)
			if (t1->next->Data > t1->next->next->Data) {
				r = t1->next->next;
				t1->next->next = r->next;
				r->next = t1->next;
				t1->next = r;
			}
		t = t1->next;
	} while ((*top)->next->next != t);
}

//Сортировка по содержимому..
void dstaSort(comp* top)
{
	comp* t = NULL, * t1;
	int r;
	do {
		for (t1 = top; t1->next != t; t1 = t1->next)
		{
			if (t1->Data > t1->next->Data)
			{
				r = t1->Data;
				t1->Data = t1->next->Data;
				t1->next->Data = r;
			}
		}
		t = t1;
	} while (top->next != t);
}


//Добавление элемента в стек..
comp* push(comp* p, int value)
{
	comp* temp = new comp;
	temp->Data = value;
	temp->next = p;
	return temp;
}

//Удаление элемента из стека..
comp* pop(comp* p)
{
	comp* temp = p;
	p = p->next;
	delete temp;
	return p;
}

//Очистка стека..
void clear(comp** p) {
	comp* temp;
	while (*p != NULL) {
		temp = *p;
		*p = (*p)->next;
		delete temp;
	}
}


int main()
{
	setlocale(LC_ALL, "rus");

	comp* top = NULL;

	cout << "Выберите действие:" << endl
		<< "1)Случайное заполнение стека;" << endl
		<< "2)Добавление элемента в стек;" << endl
		<< "3)Вывод стека;" << endl
		<< "4)Индивидуальное задание;" << endl
		<< "5)Сортировка стека по адресу;" << endl
		<< "6)Сортировка стека по содержимому;" << endl
		<< "7)Удаление элемента из стека;" << endl
		<< "8)Очистка стека;" << endl
		<< "9)Выход;" << endl;

	int choice; cin >> choice;
	while (true)
	{
		switch (choice)
		{
		case 1:
			int amount_of_elements; cout << "Введите количество элементов стека: "; cin >> amount_of_elements;
			top = create(&top, amount_of_elements);
			break;
		case 2:
			int value; cout << "Введите содержимое элемента: " << endl; cin >> value;
			top = push(top, value);
			break;
		case 3:
			show(top);
			break;
		case 4:
			top = ex(top);
			break;
		case 5:
			top = push(top, 1);
			adressSort(&top);
			int a;
			top = pop(top);
			break;
		case 6:
			dstaSort(top);
			break;
		case 7:
			top = pop(top);
			break;
		case 8:
			clear(&top);
			break;
		case 9:
			clear(&top);
			return 0;
		}
		cout << "Выберите действие:" << endl
			<< "1)Случайное заполнение стека;" << endl
			<< "2)Добавление элемента в стек;" << endl
			<< "3)Вывод стека;" << endl
			<< "4)Индивидуальное задание;" << endl
			<< "5)Сортировка стека по адресу;" << endl
			<< "6)Сортировка стека по содержимому;" << endl
			<< "7)Удаление элемента из стека;" << endl
			<< "8)Очистка стека;" << endl
			<< "9)Выход;" << endl;
		cin >> choice;
	}
	return 0;
}