#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>
using namespace std;


struct Reises
{
	int number = 0;
	string finish_place;
	int time_1;
	int time_2;
};
Reises list[100];



//Добавление рейсов..
int AddReis(int last_numb)
{
	string path("Reises.txt");
	ofstream file(path, ofstream::app);

	cout << "Добавление рейса.." << endl;
	cout << "Введите количество рейсов: ";
	int n;
	cin >> n;
	int temp = n;
	for (int numb = last_numb; numb < n + last_numb; numb++, temp--)
	{
		if (file.is_open())
		{
			if (temp > 0)
			{
				cout << "Введите пункт назначения, время отбытия, время прибытия: ";
				cout << "Рейс №" << numb << endl;
				list[numb].number = numb;
				cin >> list[numb].finish_place >> list[numb].time_1 >> list[numb].time_2;
				file << list[numb].number << endl << list[numb].finish_place << endl << list[numb].time_1 << endl << list[numb].time_2 << endl << endl;
				last_numb = numb + 1;
			}
		}
		else {
			cout << "error!" << endl;
		}
	}
	file.close();
	return last_numb;
}


//Просмотр рейсов..
void Read()
{
	cout << "Просмотр рейсов.." << endl;
	string line;
	string path("Reises.txt");
	ifstream file(path);

	if (file.is_open())
	{
		int tab = 0;
		while (!file.eof())
		{
			file >> line;
			cout << line << endl;
			line.clear();
			tab++;
			if (tab == 4)
			{
				cout << endl;
				tab = 0;
			}
		}
	}
	else
	{
		cout << "error!" << endl;
	}
	file.close();
}


//Линейный поиск..
void LinearSearch(int last_numb)
{
	cout << "Введите время прибытия: ";
	int cur_time; cin >> cur_time;
	for (int i = 0; i < last_numb; i++)
	{
		if (list[i].time_2 == cur_time)
		{
			cout << list[i].number << endl << list[i].finish_place << ", " << list[i].time_1 << ", " << list[i].time_2 << endl;
		}
	}
}


//Вывод в файл..
void ToFile(int e)
{
	string path("Reises.txt");
	ofstream file(path);

	for (int numb = 0; numb <= e; numb++)
	{
		file << list[numb].number << endl << list[numb].finish_place << endl << list[numb].time_1 << endl << list[numb].time_2 << endl << endl;
	}
	file.close();
}


//Quicksort сортировка рейсов..
void Quicksort(int b, int e)
{
	int index = floor(e / 2);
	int l = b, r = e, piv = list[index].time_2;

	while (l <= r)
	{  
		while (list[l].time_2 < piv)
		{
			l++;
		}
		while (list[r].time_2 > piv)
		{
			r--;
		}
		if (l <= r)
		{
			swap(list[l], list[r]);
			l++;
			r--;
		}
	}
	if (b < r)
		Quicksort(b, r);
	if (e > l)
		Quicksort(l, e);
}


//Метод прямого выбора..
void DirectChoose(int size)
{
	int min; Reises temp; 
	for (int i = 0; i < size - 1; i++)
	{
		min = i; 
		
		for (int j = i + 1; j < size; j++)  
		{
			if (list[j].time_2 < list[min].time_2) 
				min = j;     
		}
		swap(list[i], list[min]);
	}
	for (int i = 0; i < size; i++)
	{
		cout << list[i].number << endl << list[i].finish_place << ", " << list[i].time_1 << ", " << list[i].time_2 << endl;
	}
}


//Индивидуальное задание..
void ex(int last_numb)
{
	cout << "Введите пункт назначения: ";
	string finish_place; cin >> finish_place;
	cout << "Введите время прибытия: ";
	int cur_time; cin >> cur_time;

	for (int i = 0; i < last_numb; i++)
	{
		if ((list[i].finish_place == finish_place) && (list[i].time_2 < cur_time))
		{
			cout << list[i].number << endl << list[i].finish_place << ", " << list[i].time_1 << ", " << list[i].time_2 << endl;
		}
	}
}


//Двоичный поиск рейсов в отсортированном массиве..
int BinarSearch(int l, int r)
{
	cout << "Введите время прибытия: ";
	int cur_time; cin >> cur_time;
	int piv = 0;

	while (1)
	{
		piv = floor(r / 2);
		if (cur_time < list[piv].time_2)
		{
			r = piv - 1;
		}
		if (cur_time > list[piv].time_2)
		{
			l = piv + 1;
		}
		else
		{
			cout << list[piv].number << endl << list[piv].finish_place << ", " << list[piv].time_1 << ", " << list[piv].time_2 << endl;
			return 1;
		}
		if (l > r)
		{
			cout << "Такого рейса нет..";
			return -1;
		}
	}
}


int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "Выберите действие: 1)Добавление рейса; 2)Просмотр рейсов; 3)Линейный поиск; 4)Быстрая сортировка; 5)Метод прямого выбора; 6)Индивидуальный вариант;  7)Бинарный поиск; 8)Выход;";
	int n; cin >> n;
	int last_numb = 0;
	while (n != 8)
	{
		switch (n)
		{
		case 1:
			last_numb = AddReis(last_numb);
			break;
		case 2:
			Read();
			break;
		case 3:
			LinearSearch(last_numb);
			break;
		case 4:
			Quicksort(0, last_numb-1);
			ToFile(last_numb-1);
			break;
		case 5:
			DirectChoose(last_numb);
			break;
		case 6:
			ex(last_numb);
			break;
		case 7:
			BinarSearch(0, last_numb-1);
			break;
		}
		cout << "Выберите действие: 1)Добавление рейса; 2)Просмотр рейсов; 3)Линейный поиск; 4)Быстрая сортировка; 5)Метод прямого выбора; 6)Индивидуальный вариант;  7)Бинарный поиск; 8)Выход;";
		cin >> n;
	}
	return 0;
}


