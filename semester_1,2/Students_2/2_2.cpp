//..Lab_1..

#include <iostream>
#include <istream>
#include <string>
#include <fstream>
#include <vector>
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

vector <student*> students;

ofstream fout;
ifstream fin;


//Меню..
int satusmenu;

void menu()
{
	cout << endl <<"Выберете действие:" << endl
		 << "(0) Выход из програмы." << endl
		 << "(1) Добавить студента." << endl
		 << "(2) Найти студента." << endl
		 << "(3) Удалить студента." << endl
		 << "Ваш выбор: ";
	cin >> satusmenu;
}


//Добавление студента..
void add_student()
{
	fout.open("students.txt", ofstream::app);

	student* current_student = new student();
	students.push_back(current_student);

	cout << "Введите Фамилию студента:" << endl;
	cin >> current_student -> surname;
	cout << "Введите инициалы студента: " << endl;
	cin >> current_student -> name;
	cout << "Введите дату рождения студента: " << endl;
	cin >> current_student -> date_of_birth;
	cout << "Введите номер группы студента: " << endl;
	cin >> current_student -> group;
	cout << "Введите оценку по физике студента: " << endl;
	cin >> current_student -> phys;
	cout << "Введите оценку по математике студента: " << endl;
	cin >> current_student -> math;
	cout << "Введите оценку по химии студента: " << endl;
	cin >> current_student -> chem;
	cout << "Введите оценку по информатике студента: " << endl;
	cin >> current_student -> inf;

	fout		<< "Фамилия: " << current_student->surname << "; Инициалы: " << current_student->name << "; Дата рождения: " 
				<< current_student->date_of_birth << "; Номер группы: " << current_student->group << "; Оценка по физике: " 
				<< current_student->phys << "; Оценка по математике: " << current_student->math << "; Оценка по химии: " 
				<< current_student->chem << "; Оценка по информатике: " << current_student->inf << endl;

	fout.close();
}


//Поиск студента..
void search_student()
{
	fin.open("students.txt", ofstream::app);
	cout << "Введите фамилию студента: ";
	string str;
	string search_str;
	cin >> search_str;

	while (!fin.eof())
	{
		fin >> str;
		if (str == search_str)
		{
			cout << "Фамилия: " << str;
			getline(fin, str);
			cout << str << endl;
		
		}
	}

	fin.close();
}


//Удаление студента..
void delete_student()
{
	fout.open("students.txt", ofstream::app);

	cout << "Введите фамилию студента: ";
	string str;
	string search_str;
	cin >> search_str;

	while (!fin.eof())
	{
		fin >> str;
		if (str == search_str)
		{
			getline(fin, str);
			fin.clear();

		}
	}

	fout.close();
}


int main()
{
	system("chcp 1251>nul");
	menu();

	while (satusmenu != 0) {
		switch (satusmenu) {

		case 1:
			add_student();
			menu();
			break;

		case 2:
			search_student();
			menu();
			break;

		case 3:
			delete_student();
			menu();
			break;

		default:
			cout << "Неправильно выбран пункт Меню! " << endl;
			break;

		}

	}
	return 0;
}