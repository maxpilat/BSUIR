#include<stdio.h>
#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<map>
#include<algorithm>

using namespace std;

struct Tree {
	int data;//поле для инфы
	string info;//поле для инфы
	Tree* left, * right;//поле для инфы
};
//--------------------------------
//--------------------------------
Tree* add(Tree* tree, int inf, string dat) {//функция для добавления ветви в дерево
	if (tree == NULL)//если ветвь путстая
	{
		Tree* t = new Tree;		//создаем новый указатель на структуру
		t->data = inf;//заполняем поле дата
		t->info = dat;//заполняем поле инф
		t->left = t->right = NULL;//указатели на правое и левое ответвления пустые	
		return t;//возвращаем наше новое ответвление
	}
	if (inf < tree->data)//если ключ (число) меньше текущего рассматриваемого элемента
	{
		tree->left = add(tree->left, inf, dat);//вызываем эту же функцию для левого элемента (там меньше, чем текущий)
	}
	if (inf > tree->data)//если ключ (число) больше текущего рассматриваемого элемента
	{
		tree->right = add(tree->right, inf, dat);//вызываем эту же функцию для правого элемента (там больше, чем текущий)
	}
	return tree;//если все мимо, возвращаем дерево как есть
}
//--------------------------------
//--------------------------------
void view_tree(Tree** tree, int l)//просто функция, чтобы перед меню рисовалось дерево
{
	int i;

	if (*tree != NULL)
	{
		view_tree(&((*tree)->right), l + 1);
		for (i = 1; i <= l; i++) cout << "   ";
		cout << (*tree)->data << endl;
		view_tree(&((*tree)->left), l + 1);
	}
}
//--------------------------------
//--------------------------------
void treeprint1(Tree* tree) {
	if (tree != NULL) { //Пока не встретится пустой узел
		cout << tree->data << "-" << tree->info << endl; //Отображаем корень дерева
		treeprint1(tree->left); //Рекурсивная функция для левого поддерева
		treeprint1(tree->right); //Рекурсивная функция для правого поддерева
	}
}
//
void treeprint2(Tree* tree) {
	if (tree != NULL) { //Пока не встретится пустой узел
		treeprint2(tree->left); //Рекурсивная функция для левого поддерева
		treeprint2(tree->right); //Рекурсивная функция для правого поддерева
		cout << tree->data << "-" << tree->info << endl; //Отображаем корень дерева
	}
}
//
void tree_print(Tree* tree)//отображает по возрастанию
{
	if (tree == NULL)//если дерево (поддерево) пустое - ничего
		return;
	tree_print(tree->left);//Рекурсивная функция для левого поддерева
	cout << tree->data << "-" << tree->info << endl;//Отображаем корень дерева
	tree_print(tree->right);//Рекурсивная функция для правого поддерева
}
void print(Tree* tree)//просто для красивого отображения
{
	tree_print(tree);
	cout << endl;
}
//--------------------------------
//--------------------------------
Tree* tree_find(Tree* tree, int key) {//поиск по дереву
	if (tree == NULL) return NULL;//если дерево (поддерево) пустое - ничего
	if (tree->data == key) return tree;//если нашли нужный т.н. лист, то возвращаем указатель на него
	if (key < tree->data) return tree_find(tree->left, key);//если ключ (число) меньше текущего рассматриваемого элемента, вызываем эту же функцию для левого элемента (там меньше, чем текущий)
	else
		return tree_find(tree->right, key);//если ключ (число) больше текущего рассматриваемого элемента, вызываем эту же функцию для правого элемента (там больше, чем текущий)
}

//--------------------------------
//--------------------------------
Tree* Del(Tree* tree, int key) {//удаление элемента из дерева, из методы скопировано
	Tree* Del, * Prev_Del, * R, * Prev_R;
	// Del, Prev_Del – удаляемый узел и его предыдущий (предок); 
	// R, Prev_R – элемент, на который заменяется удаляемый, и его предок;
	Del = tree;
	Prev_Del = NULL;
	//Поиск удаляемого элемента и его предка по ключу key
	while (Del != NULL && Del->data != key) {
		Prev_Del = Del;
		if (Del->data > key)  Del = Del->left;
		else Del = Del->right;
	}
	if (Del == NULL) {				// Элемент не найден
		cout << "No such key" << endl;
		return tree;
	}
	//-------------------------- Поиск элемента R для замены
	if (Del->right == NULL) R = Del->left;
	else
		if (Del->left == NULL) R = Del->right;
		else {
			//Ищем самый правый узел в левом поддереве
			Prev_R = Del;
			R = Del->left;
			while (R->right != NULL) {
				Prev_R = R;
				R = R->right;
			}
			//Формируем связи элемента R и его предка Prev_R
			if (Prev_R == Del)  R->right = Del->right;
			else {
				R->right = Del->right;
				Prev_R->right = R->left;
				R->left = Del->left;
			}
		}
	if (Del == tree) tree = R;			// Удаляя корень, заменяем его на R
	else
		//Поддерево R присоединяем к предку удаляемого узла
		if (Del->data < Prev_Del->data)
			Prev_Del->left = R;				// На левую ветвь
		else	Prev_Del->right = R;				// На правую ветвь
	delete Del;
	return tree;
}
//--------------------------------
//--------------------------------
void get_map(Tree* tree, map < int, string >& g)//просто получает словарь из всех строк и ключей к ним, как в функции просмотра, только тут записывает, а не выдает 
{
	if (tree == NULL)
		return;
	get_map(tree->left, g);
	g[tree->data] = tree->info;
	get_map(tree->right, g);
}
//--------------------------------
void Make_Blns(Tree** tree, int n, int k, vector<int> g, map<int, string> v) {//балансировка из методы
	if (n == k) {
		*tree = NULL;
		return;
	}
	else {
		int m = (n + k) / 2;
		*tree = new Tree;
		(*tree)->data = g[m];
		(*tree)->info = v[g[m]];
		Make_Blns(&(*tree)->left, n, m, g, v);
		Make_Blns(&(*tree)->right, m + 1, k, g, v);
	}
}

void Del_Tree(Tree* t) {//удаление дерева
	if (t != NULL) {//если ветвь существует
		Del_Tree(t->left); //убиваем детей слева (эта же функция, т.е. они тоже убивают всех своих детей и убивают сами себя)			
		Del_Tree(t->right); //убиваем детей справа (эта же функция, т.е. они тоже убивают всех своих детей и убивают сами себя)			
		delete t;//суицид ветки
	}
}

void calculating(Tree* Branch, map < int, int >& m, int level)//индивидуальное (подсчет количества элементов на каждом уровне)
{
	m[level]++;
	if (Branch->left)  calculating(Branch->left, m, level + 1);
	if (Branch->right) calculating(Branch->right, m, level + 1);
}

int main()
{
	setlocale(LC_ALL, "Rus");
	int value, position, x;
	string info;
	map < int, int > m;
	map < int, string > g;
	set<int> v;
	vector<int> a;
	Tree* tree = new Tree;
	Tree* q = new Tree;
	tree = NULL;
	do
	{
		view_tree(&tree, 0);
		cout << endl;
		cout << endl;


		cout << "1. Add element" << endl;
		cout << "2. Delete element" << endl;
		cout << "3. Print the tree method 1" << endl;
		cout << "4. Print the tree method 2" << endl;
		cout << "5. Print the tree from low to high" << endl;
		cout << "6. Balance the tree" << endl;
		cout << "7. Find an element" << endl;
		cout << "8. Individual task" << endl;
		cout << "9. Delete all" << endl;
		cout << "10. Demo filling" << endl;
		cout << "0. Exit" << endl;
		cin >> x;
		switch (x)
		{
		case 1:
			cout << "Key > ";
			cin >> value;
			cout << "Info > ";
			cin >> info;
			tree = add(tree, value, info);
			cout << "\nElement was added...\n\n";
			break;
		case 2:
			cout << "Defenition > ";
			cin >> value;
			tree = Del(tree, value);
			cout << "\nElement was deleted...\n\n";
			break;
		case 3:
			treeprint1(tree);
			cout << endl;
			system("pause");
			break;
		case 4:
			treeprint2(tree);
			cout << endl;
			system("pause");
			break;
		case 5:
			print(tree);
			system("pause");
			break;
		case 6:
			get_map(tree, g);
			for (auto v : g) {
				a.push_back(v.first);
			}
			Make_Blns(&tree, 0, a.size(), a, g);
			break;
		case 7:
			cout << "Defenition > ";
			cin >> value;
			q = tree_find(tree, value);
			cout << "Element " << value << " has been found! The right adress is " << q->right << " The left adress is " << q->left << " Info of the element: " << q->info << endl;
			system("pause");
			break;
		case 8:
		{
			cout << "Level > ";
			calculating(tree, m, 0);
			for (auto i : m)
			{
				cout << "There are " << i.second << " elements on level " << i.first + 1 << endl;
			}
			cout << endl;
			system("pause");
			break;
		}
		case 9:
		{
			Del_Tree(tree);
			cout << " Tree Delete!" << endl;
			tree = NULL;
		}
		case 10:
		{
			tree = add(tree, 7, "g");
			tree = add(tree, 4, "d");
			tree = add(tree, 9, "i");
			tree = add(tree, 10, "j");
			tree = add(tree, 8, "h");
			tree = add(tree, 6, "f");
			tree = add(tree, 5, "e");
			tree = add(tree, 2, "b");
			tree = add(tree, 3, "c");
			tree = add(tree, 1, "a");
			break;
		}

		}
		system("cls");
	} while (x != 0);
}