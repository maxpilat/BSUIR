#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <Windows.h>
#include <queue>

using namespace std;

vector <vector<int>> list(60);
int n = 60;

vector<int> bfs(int s)
{
	vector<int> dist(n, n);
	dist[s] = 0;
	queue<int> q;
	q.push(s);

	while (!q.empty()) {
		int v = q.front();
		q.pop();
		for (int u : list[v]) {
			if (dist[u] > dist[v] + 1) {
				dist[u] = dist[v] + 1;
				q.push(u);
			}
		}
	}

	return dist;
}

int main()
{
	setlocale(LC_ALL, "rus");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	vector <string> stations;


	string str;
	ifstream f1("stations.txt");
	while (!f1.eof())
	{
		str = "";
		getline(f1, str);
		stations.push_back(str);
	}
	str = "";

	ifstream f2("list.txt");
	int i = 0, c = 0;
	char ch;
	while (f2.get(ch) && i < list.size())
	{
		if (ch != '\n' && ch != ' ')
		{
			str += ch;
		}
		if (ch == ' ' || ch == '\n')
		{
			c = stoi(str);
			list[i].push_back(c);
			str = "";
		}
		if (ch == '\n')
		{
			i++;
		}
	}
	c = stoi(str);
	list[i].push_back(c);

	
	for (int i = 0; i < stations.size(); i++)
	{
		cout << stations[i] << endl;
	}

	str = "";
	string a, b;
	ifstream f3("spbmetro.in");
	getline(f3, a);
	getline(f3, b);
	cout << a << endl << b << endl;


	int aIndex = 0;
	int bIndex = 0;
	for (int i = 0; i < stations.size(); i++)
	{
		if (stations[i] == a)
		{
			aIndex = i;
		}
		if (stations[i] == b)
		{
			bIndex = i;
		}
	}

	vector<int> res = bfs(aIndex);

	ofstream f4("spbmetro.out");
	f4 << res[bIndex];
	cout << res[bIndex];

}



