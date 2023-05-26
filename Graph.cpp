#include <vector>
#include <stdio.h>
#include <iostream>
#include <queue>
#include <algorithm>
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
	if (has_vertex(id_v)) throw "Вершина уже существует";
	Vertex v(id_v);
	vertexes.push_back(v);
}

bool Graph::has_edge(int from, int to) const
{
	if (vertexes.size() == 0) return false;
	int index_from = find_vertex(from);
	int index_to = find_vertex(to);
	if (index_from == -1 || index_to == -1) throw "Одной из вершин ребра не найдено";

	for (auto i = vertexes[index_from].edges.begin(); i != vertexes[index_from].edges.end(); i++)
	{
		if (i->id_to == to)
			return true;
	}
	return false;
}

bool Graph::remove_edge(int from, int to)
{
	if (vertexes.size() == 0) return false;
	int index_from = find_vertex(from);
	int index_to = find_vertex(to);
	if (index_from == -1 || index_to == -1) throw "Одной из вершин ребра не найдено";

	for (auto i = vertexes[from].edges.begin(); i != vertexes[from].edges.end(); i++) {
		if (i->id_to == to) vertexes[from].edges.erase(i);
	}

	return true;
}

bool Graph::remove_vertex(int remove_v)
{
	if (vertexes.size() == 0) return false;
	int remove_index = find_vertex(remove_v);
	if (remove_index == -1) throw "Такой вершины нет";

	for (auto v = vertexes.begin(); v != vertexes.end(); v++)
	{
		remove_edge(v->id_v, remove_v);
	}

	vertexes[remove_index].edges.clear();
	vertexes.erase(vertexes.begin() + remove_index);
	return true;
}

void Graph::add_edge(int from, int to, int weight)
{
	int index_from = find_vertex(from);
	int index_to = find_vertex(to);
	if (index_from == -1 || index_to == -1) throw "Одной из вершин ребра нет";

	Edge tmp(to, weight);
	vertexes[index_from].edges.push_back(tmp);
}

void Graph::print() const
{
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
	if (vertexes.size() == 0) throw "Граф пуст";
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

