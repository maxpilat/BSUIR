#include<iostream>
#include<fstream>
#include<vector>
#include<queue>
#include<string>
#include<windows.h>

using namespace std;

int search_vertex(vector<vector<int> >g, int edge, int start)
{
	for (int i = 0; i < g.size(); i++)
	{
		if ((g[i][edge] == 1 || g[i][edge] == -1) && i != start)
			return i;
	}
}


vector<int> search_component(int n, vector<vector<int> >graph, int del, bool check)
{
	vector<int> visit(n, 0);

	if (check)
	{
		visit[del] = -1;
	}

	int num = 1;
	for (int i = 0; i < n; i++)
	{
		if (visit[i] == 0)
		{
			queue<int> q;
			q.push(i);
			visit[i] = num;
			while (!q.empty())
			{
				int vertex = q.front();

				for (int k = 0; k < graph[vertex].size(); k++)
				{
					if (graph[vertex][k] == 1 || graph[vertex][k] == -1)
					{
						int tmp = search_vertex(graph, k, vertex);
						if (visit[tmp] == 0)
						{
							visit[tmp] = num;
							q.push(tmp);
							vertex = q.front();
						}
					}

				}

				q.pop();
			}
			num++;
		}
	}
	visit.push_back(num);
	return visit;
}


int component_KOL(int n, vector<vector<int> >graph, int del, bool check)
{

	vector<int> visit = search_component(n, graph, del, check);
	return visit.back();

}

vector<int> vector_del(int n, vector<vector<int> >graph, int del, bool check)
{

	vector<int> visit = search_component(n, graph, del, check);
	visit.pop_back();
	return visit;

}


const int TEST_KOL = 3;

int main()
{
	for (int test_num = 1; test_num <= TEST_KOL; test_num++)
	{
		ifstream in(to_string(test_num) + ".txt");
		vector<vector<int> > graph;

		int n;
		in >> n;
		for (int i = 0; i < n; i++)
		{
			int k;
			in >> k;
			vector<int> tmp;
			for (int j = 0; j < k; j++)
			{
				int m;
				in >> m;
				tmp.push_back(m);
			}
			graph.push_back(tmp);
		}

		bool del_vector = false;
		int del = 0;
		int num = component_KOL(graph.size(), graph, del, del_vector);
		vector<int> visit = vector_del(graph.size(), graph, del, del_vector);
		

		cout << "TEST #" << test_num << endl << '\n';



		for (int del = 0; del < graph.size(); del++)
		{
			vector<vector<int> > graph_del = graph;
			


			for (int j = 0; j < graph_del[del].size(); j++)
			{
				if (graph_del[del][j] == 1 || graph_del[del][j] == -1)
				{

					graph_del[del][j] = 0;

				}
			}


			bool del_vector = true;
			int num_del = component_KOL(graph_del.size(), graph_del, del, del_vector);
			vector<int> visit = vector_del(graph_del.size(), graph_del, del, del_vector);

			if (num_del > num)
			{
				
				cout << "Vertex_ " << del << endl;
				
			}

		}

		cout << endl;
		in.close();
		
	}
	
	system("pause");
	system("cls");
	return 0;
}