//Bor..

#include <iostream>
#include <string>
#include "Bor.h"
using namespace std;


int satusmenu;
void Menu() {
    cout
            << "Выберете действие:"                 << endl
            << "(0) Выход из програмы."             << endl
            << "(1) Вставка строки в Бор."          << endl
            << "(2) Поиск стрроки в Боре."          << endl
            << "(3) Удаление строки из Бора."       << endl
            << "(4) Вывод всего Бора."              << endl
            << "Ваш выбор: ";
    cin >> satusmenu;
}


int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    string  line;
    node* root = new node();
    string cur_str;
    Menu();

    while (satusmenu != 0) {
        switch (satusmenu) {

            case 1:
                cout << "Введите строку: " << endl;
                cin >> line;
                add(line, root);
                Menu();
                break;

            case 2:
                cout << "Введите строку: " << endl;
                cin >> line;
                has(line, root);
                cout << endl;
                Menu();
                break;

            case 3:
                cout << "Введите строку: " << endl;
                cin >> line;
                remove(line, root);
                Menu();
                break;

            case 4:
                write(root, cur_str);
                Menu();
                break;

            default:
                cout << "Неправильно выбран пункт Меню! " << endl;
                Menu();
                break;

        }
    }
    cout << "Рабаота завершена! " << endl;
}