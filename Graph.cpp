#include <vector>
#include <stdio.h>
#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#include <forward_list>
#include <stdio.h>
#include "stdio.h"
#include <stdlib.h>
#include <string>
#include <ctype.h>
#include <math.h>
#include <locale.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <iostream>
#include "errors.h"
#include "Graph.h"
using namespace std;

void Graph::delete_graph()
{
	for (auto v = vertexes.begin(); v != vertexes.end(); v++)
	{
		v->edges.clear();
	}
	vertexes.clear();
}

Graph::~Graph()
{
	delete_graph();
}

bool Graph::has_vertex(int id_v) const
{
	if (vertexes.size() == 0) return false;
	for (auto i = vertexes.begin(); i != vertexes.end(); i++)
	{
		if (i->id_v == id_v)
			return true;
	}
	return false;
}

int Graph::find_vertex(int id_v) const
{
	if (vertexes.size() == 0) return -1;
	for (auto i = vertexes.begin(); i != vertexes.end(); i++)
	{
		if (i->id_v == id_v)
			return int(i - vertexes.begin());
	}
	return -1;
}

void Graph::add_vertex(int id_v)
{
	if (has_vertex(id_v)) throw error("Уже существует такая вершина");
	Vertex v(id_v);
	vertexes.push_back(v);
}

bool Graph::has_edge(int id_from, int id_to) const
{
	if (vertexes.size() == 0) return false;
	int index_from = find_vertex(id_from);
	int index_to = find_vertex(id_to);
	if (index_from == -1 || index_to == -1) throw error("Одной из вершин ребра не найдено");

	for (auto i = vertexes[index_from].edges.begin(); i != vertexes[index_from].edges.end(); i++)
	{
		if (i->id_to == id_to)
			return true;
	}
	return false;
}

bool Graph::remove_edge(int id_from, int id_to)
{
	if (vertexes.size() == 0) return false;
	int index_from = find_vertex(id_from);
	int index_to = find_vertex(id_to);
	if (index_from == -1 || index_to == -1) throw error("Одной из вершин ребра не найдено");

	for (auto i = vertexes[id_from].edges.begin(); i != vertexes[id_from].edges.end(); i++) {
		if (i->id_to == id_to) vertexes[id_from].edges.erase(i);
	}

	return true;
}

bool Graph::remove_vertex(int remove_v)
{
	if (vertexes.size() == 0) return false;
	int remove_index = find_vertex(remove_v);
	if (remove_index == -1) throw error("Такой вершины нет");

	for (auto v = vertexes.begin(); v != vertexes.end(); v++)
	{
		remove_edge(v->id_v, remove_v);
	}

	vertexes[remove_index].edges.clear();
	vertexes.erase(vertexes.begin() + remove_index);
	return true;
}

void Graph::add_edge(int id_from, int id_to, int weight)
{
	int index_from = find_vertex(id_from);
	int index_to = find_vertex(id_to);
	if (index_from == -1 || index_to == -1) throw error("Одной из вершин ребра нет");
	Edge tmp(id_to, weight);
	vertexes[index_from].edges.push_back(tmp);
}

void Graph::print() const
{
	if (vertexes.size() == 0) throw error("Пустой граф");
	for (auto i = vertexes.begin(); i != vertexes.end(); i++)
	{
		cout << i->id_v << ": ";
		for (auto j = i->edges.begin(); j != i->edges.end(); j++)
		{
			cout << j->id_to << ", ";
		}
		cout << endl;
	}
}

int Graph::order() const
{
	return vertexes.size();
}

int Graph::degree() const
{
	if (vertexes.size() == 0) throw error("Граф пуст");
	int deg = -1;
	for (auto i = vertexes.begin(); i != vertexes.end(); i++)
	{
		int counter = 0;
		for (auto j = i->edges.begin(); j != i->edges.end(); j++)
		{
			counter++;
		}
		for (auto k = vertexes.begin(); k != vertexes.end(); k++)
		{
			for (auto n = k->edges.begin(); n != k->edges.end(); n++)
			{
				if (n->id_to == i->id_v) counter++;
			}
		}
		if (counter > deg) deg = counter;
	}
	return deg;
}

vector<Edge> Graph::shortest_path(int id_from, int id_to)
{
	vector<Edge> path;
	//проверка на отрицательные ребра
	for (auto i = vertexes.begin(); i != vertexes.end(); i++)
	{
		for (auto j = i->edges.begin(); j != i->edges.end(); j++)
		{
			if (j->weight < 0) throw error("Алгоритм Дейкстры не может корректно работать с отрицательными весами");
		}
	}

	if (vertexes.size() == 0) throw error("Пустой граф");
	int index_from = find_vertex(id_from);
	int index_to = find_vertex(id_to);
	if (index_from == -1 || index_to == -1) throw error("Одной из вершин ребра не найдено");

	for (auto v = vertexes.begin(); v != vertexes.end(); v++)
	{
		v->mark = 2147483646;
		v->id_prev = 2147483646;
	}
	vertexes[find_vertex(id_from)].mark = 0;
	vertexes[find_vertex(id_from)].id_prev = 0;

	vector<Vertex> S; // множество обработанных вершин
	queue <Vertex> Q; // приоритетная очередь обработки

	while (!Q.empty())
	{
		//sort_queue(Q);
		//print_queue(Q);
		Vertex u = Q.front();
		Q.pop();
		S.push_back(u);
		vector<Vertex> v_neighbour;// = neighbour_of_vertex(u.id_v);
		for (auto i = u.edges.begin(); i != u.edges.end(); i++) {
			i->
		}

		for (auto v = v_neighbour.begin(); v != v_neighbour.end(); v++)
		{
			relax(u, *v);
		}
		Q = update_queue(Q);
	}
}