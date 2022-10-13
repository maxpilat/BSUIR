#include <iostream>
#include <string>
using namespace std;


struct student
{
	string surname;
	string name;
	string date_of_birth;
	int group = 0;
	int phys = 0;
	int math = 0;
	int chem = 0;
	int inf = 0;
};


int main()
{
	system("chcp 1251>nul");
	int number;
	cout << "Введите количество студентов: ";
	cin >> number;
	student arr[100];

	for (int i = 0; i < number; ++i) 
	{
		cout << "Введите Фамилию " << i + 1 << " студента:" << endl;
		cin >> arr[i].surname;
		cout << "Введите инициалы " << i + 1 << " студента: " << endl;
		cin >> arr[i].name;
		cout << "Введите дату рождения " << i + 1 << " студента: " << endl;
		cin >> arr[i].date_of_birth;
		cout << "Введите номер группы " << i + 1 << " студента: " << endl;
		cin >> arr[i].group;
		cout << "Введите оценку по физике " << i + 1 << " студента: " << endl;
		cin >> arr[i].phys;
		cout << "Введите оценку по математике " << i + 1 << " студента: " << endl;
		cin >> arr[i].math;
		cout << "Введите оценку по химии " << i + 1 << " студента: " << endl;
		cin >> arr[i].chem;
		cout << "Введите оценку по информатике " << i + 1 << " студента: " << endl;
		cin >> arr[i].inf;
	}

	for (int i = 0; i < number; ++i)
	{
		if (arr[i].surname[0] == 'A' && (arr[i].math == 8 || arr[i].math == 9))
		{
			cout << "Фамилия: " << arr[i].surname << ". Инициалы: " << arr[i].name << " Дата рождения: " << arr[i].date_of_birth << ". Номер группы: " << arr[i].group << endl;
		}
	}

	return 0;
}
