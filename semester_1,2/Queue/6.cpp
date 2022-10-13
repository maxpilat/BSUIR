#include <iostream>
#include <queue>
using namespace std;


//Добавление элемента в конец очереди..
void push_back(queue <int> &q)
{
	int a; cin >> a;
	q.push(a);
}

//Добавление элемента в начало очереди..
void push_front(queue <int> &q)
{
	int size = q.size() + 1;
	int* temp = new int [size];

	int a; cin >> a;
	temp += a;
	while (!q.empty())
	{
		temp += q.front();
		q.pop();
	}
	for (int i = 0; i < size + 1; i++)
	{
		q.push(temp[i]);
	}
	delete[] temp;
}

//Просмотр очереди с конца..
void print_back(queue <int> q)
{
	int size = q.size();
	int* temp = new int[size];

	for (int i = 0; i < size; i++)
	{
		temp[i] = q.front();
		q.pop();
		q.push(temp[i]);
	}
	for (int i = size - 1; i >= 0; i--)
	{
		cout << temp[i] << " ";
	}
	cout << endl;
	delete[] temp;
}

//Просмотр очереди с начала..
void print_front(queue <int> q)
{
	int size = q.size();
	int* temp = new int[size];

	for (int i = 0; i < size; i++)
	{
		temp[i] = q.front();
		q.pop();
		q.push(temp[i]);
	}
	for (int i = 0; i < size; i++)
	{
		cout << temp[i] << " ";
	}
	cout << endl;
	delete[] temp;

}

//Индивидуальное задание..
void ex(queue <int> &q)
{
	int size = q.size();
	int* temp = new int[size];
	int front = q.front();
	q.pop();

	for (int i = 0; i < size - 1; i++)
	{
		temp[i] = q.front();
		q.pop();
	}
	int last = temp[size - 2];
	temp[size - 2] = front;
	q.push(last);

	for (int i = 0; i < size - 1; i++)
	{
		q.push(temp[i]);
	}
	delete[] temp;
}


int main()
{
	setlocale(LC_ALL, "RU");

	queue <int> q;

	cout << "Выберите действие: " << endl
		<< "1 .Добавить элемент в конец очереди;" << endl
		<< "2. Добавить элемент в начало очереди;" << endl
		<< "3. Вывести очередь с конца;" << endl
		<< "4 .Вывести очередь с начала;" << endl
		<< "5. Индивидуальный вариант;" << endl
		<< "6. Выход;" << endl;

	int choose; cin >> choose;
	while (choose != 6)
	{
		switch (choose)
		{
		case 1:
			push_back(q);
			break;
		case 2:
			push_front(q);
			break;
		case 3:
			print_back(q);
			break;
		case 4:
			print_front(q);
			break;
		case 5:
			ex(q);
			break;
		case 6:
			return 0;
		default:
			cout << "Неправильно выбрано действие..";
			break;
		}

		cout << "Выберите действие: " << endl
			<< "1 .Добавить элемент в конец очереди;" << endl
			<< "2. Добавить элемент в начало очереди;" << endl
			<< "3. Вывести очередь с конца;" << endl
			<< "4 .Вывести очередь с начала;" << endl
			<< "5. Индивидуальный вариант;" << endl
			<< "6. Выход;" << endl;
		cin >> choose;
	}
}

