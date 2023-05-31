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

vector<Vertex> Graph::nearest_v(int id_v)
{
	if (vertexes.size() == 0) throw "Âåðøèí íåò";
	int index = find_vertex(id_v);
	if (index == -1) throw "Âåðøèíà íå íàéäåíà";

	vector<Vertex> v_neighbours;

	for (auto i = vertexes[index].edges.begin(); i != vertexes[index].edges.end(); i++)
	{
		int v = find_vertex(i->id_to);
		if (v != -1)
			v_neighbours.push_back(vertexes[v]);
	}
	return v_neighbours;
}

void Graph::initialize()
{
	for (auto i = vertexes.begin(); i != vertexes.end(); i++)
	{
		i->color = white;
		i->id_prev = INT_MAX;
	}
}

vector<Vertex> Graph::search_in_width(Vertex& start_v)
{
	vector<Vertex> way;
	queue<Vertex> Q;
	vertexes[find_vertex(start_v.id_v)].color = gray;
	Q.push(vertexes[find_vertex(start_v.id_v)]);
	while (Q.empty() == false)
	{
		Vertex u = Q.front();
		Q.pop();
		way.push_back(u);
		vector<Vertex> v_neighbours = neighbours(u.id_v);
		for (auto v = v_neighbours.begin(); v != v_neighbours.end(); v++)
		{
			if (v->color == white)
			{
				int id = find_vertex(v->id_v);
				if (id != 0)
				{
					vertexes[id].color = gray;
					vertexes[id].id_prev = u.id_v;
				}
				Q.push(vertexes[id]);


			}
		}
		vertexes[find_vertex(u.id_v)].color = black;
	}
	return way;
}

vector<Vertex> Graph::walk_in_width(int id_first)
{

	this->initialize();
	int index_first = find_vertex(id_first);
	return search_in_width(vertexes[index_first]);
}

void Graph::relax(Vertex& u, Vertex& v)
{
	double w = 0;
	auto current = u.edges.begin();
	auto end = u.edges.end();

	while (current != end)
	{
		if (current->id_to == v.id_v)
			w = current->weight;
		current++;
	}
	if (v.d > u.d + w)
	{
		vertexes[find_vertex(v.id_v)].d = u.d + w;
		vertexes[find_vertex(v.id_v)].id_prev = u.id_v;
	}
}

void Graph::initialize_for_dijkstra(int from)
{
	for (auto i = this->vertexes.begin(); i != this->vertexes.end(); i++)
	{
		i->d = INT_MAX;
		i->id_prev = INT_MAX;
	}
	this->vertexes[from].d = 0;
}

void Graph::sort(queue<Vertex>& Q)
{
	for (int i = 1; i <= Q.size(); i++)
	{
		int min_i = -1; // индекс минимального элемента в очереди
		double min_val = INT_MAX;
		for (int j = 0; j < Q.size(); j++)
		{
			Vertex cur = Q.front();
			Q.pop();
			if (cur.d <= min_val && j <= Q.size()-i)
			{
				min_i = j;
				min_val = cur.d;
			}
			Q.push(cur);
		}
		// вставка последнего в конец очереди
		Vertex min_v (INT_MAX);
		for (int j = 0; j < Q.size(); j++)
		{
			Vertex a = Q.front();
			Q.pop();
			if (j != min_i)
				Q.push(a);
			else
				min_v = a;
		}
		Q.push(min_v); 
	}
}

void Graph::deikstra(int from)
{
	initialize_for_dijkstra(from);
	vector<Vertex> S;
	queue<Vertex> Q;

	for (auto v = vertexes.begin(); v != vertexes.end(); v++)
	{
		Q.push(vertexes[find_vertex(v->id_v)]);
	}

	while (!Q.empty())
	{
		sort(Q);
		Vertex u = Q.front();
		Q.pop();
		S.push_back(u);
		vector<Vertex> near_v = nearest_v(u.id_v);
		for (auto v = near_v.begin(); v != near_v.end(); v++)
		{
			relax(u, vertexes[find_vertex(v->id_v)]);
		}
		queue<Vertex> tmp;
		while (!Q.empty())
		{
			Vertex u = Q.front();
			for (auto v = vertexes.begin(); v != vertexes.end(); v++)
			{
				if (u.id_v == v->id_v)
					tmp.push(vertexes[find_vertex(v->id_v)]);
			}
			Q.pop();
		}
		Q = tmp;
	}

}

vector<Vertex> Graph::shortest_path(int id_from, int id_to)
{
	if (vertexes.size() == 0) throw error("Пустой граф");;
	int index_from = find_vertex(id_from);
	int index_to = find_vertex(id_to);
	if (index_from == -1 || index_to == -1) throw error("Одной из вершин ребра не найдено");

	deikstra(vertexes[index_from].id_v);

	vector<Vertex> way;

	while (index_to != index_from)
	{

		way.push_back(vertexes[index_to]);
		int id_prev = vertexes[index_to].id_prev;
		index_to = find_vertex(id_prev);

	}
	way.push_back(vertexes[index_from]);
	for (int i = 0; i < way.size() / 2; i++)
	{
		swap(way[i], way[(way.size() - 1) - i]);
	}
	return way;
}