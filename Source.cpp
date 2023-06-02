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
#include <vector>
#include <chrono>
#include <vector>
#include <stdio.h>
#include <iostream>
#include <queue>
#include <algorithm>
#include "Graph.h"

using namespace std;

int check()
{
	int number;
	while (!(cin >> number) || (cin.peek() != '\n'))
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "Введите целое число:" << endl;
	}
	return number;
}

int get_key()
{
	int key = _getch();
	if ((key == 0) || (key == 224)) key = _getch();
	return key;
};

void my_graph(Graph & G) {
	/*G.add_vertex(1); мой граф
	G.add_vertex(2);
	G.add_vertex(3);
	G.add_vertex(4);
	G.add_vertex(5);
	G.add_vertex(6);
	G.add_vertex(7);

	G.add_edge(1, 2, 3);
	G.add_edge(1, 3, 1);
	G.add_edge(1, 4, 9);
	G.add_edge(4, 2, 8);
	G.add_edge(4, 7, 1);
	G.add_edge(2, 3, 5);
	G.add_edge(3, 2, 2);
	G.add_edge(3, 5, 4);
	G.add_edge(3, 6, 7);
	G.add_edge(6, 7, 2);*/
	/*G.add_vertex(6); //другой граф
    G.add_vertex(8);
    G.add_vertex(4);
    G.add_vertex(3);
    G.add_vertex(5);
    G.add_vertex(12);
    G.add_vertex(9);

    G.add_edge(8, 6, 1);
    G.add_edge(6, 12, 8);
    G.add_edge(4, 8, 2);
    G.add_edge(4, 6, 4);
    G.add_edge(8, 12, 10);
    G.add_edge(8, 5, 7);
    G.add_edge(8, 3, 1);
    G.add_edge(3, 5, 5);
    G.add_edge(3, 9, 3);*/
	G.add_vertex(1); // связный граф
	G.add_vertex(2);
	G.add_vertex(3);
	G.add_vertex(6);
	G.add_vertex(5);
	G.add_vertex(4);

	G.add_edge(1, 5, 3);
	G.add_edge(1, 4, 1);
	G.add_edge(2, 1, 9);
	G.add_edge(4, 2, 8);
	G.add_edge(4, 3, 5);
	G.add_edge(3, 2, 2);
	G.add_edge(3, 5, 4);
	G.add_edge(5, 6, 7);
	G.add_edge(6, 1, 2);
}

void create_graph(Graph& G) {
	while (true) {
		system("cls");
		std::cout << "Меню 2:\n";
		std::cout << "[1] - Добавить вершину\n";
		std::cout << "[2] - Удалить вершину\n";
		std::cout << "[3] - Добавить ребро\n";
		std::cout << "[4] - Удалить ребро\n";
		std::cout << "[ESC] - Выход\n";
		int m = get_key();
		int id_from_del, id_to_del, w, id_to, id_from, id_new, id_del;
		switch (m)
		{
		case 49:
			cout<<"Введите айди добавляемой вершины\n";
			id_new = check();
			try{G.add_vertex(id_new);}
			catch (error e) {
				cout << "Возникла ошибка при добавлении вершины\n";
				e.print();
			}
			get_key();
			break;
		case 50:
			cout << "Введите айди удаляемой вершины\n";
			id_del = check();
			try {
				G.remove_vertex(id_del);
				cout << "Вершина удалена\n";
			}
			catch (error e) {
				cout << "Возникла ошибка при удалении вершины\n";
				e.print();
			}
			get_key();
			break;
		case 51:
			cout << "Введите айди вершины, из которой выходит ребро\n";
			id_from = check();
			cout << "Введите айди вершины, в которую входит ребро\n";
			id_to = check();
			cout << "Введите вес ребра\n";
			w = check();
			try {G.add_edge(id_from, id_to, w);}
			catch (error e) {
				cout << "Возникла ошибка при добавлении ребра\n";
				e.print();
			}
			get_key();
			break;
		case 52:
			cout << "Введите айди вершины, из которой выходит ребро\n";
			id_from_del = check();
			cout << "Введите айди вершины, в которую входит ребро\n";
			id_to_del = check();
			try {
				G.remove_edge(id_from_del, id_to_del);
				cout << "Ребро удалено\n";
			}
			catch (error e) {
				cout << "Возникла ошибка при удалении ребра\n";
				e.print();
			}
			get_key();
			break;
		case 27:
			return;
			break;
		}
	}
}

void shortest_way(Graph& G) {
	system("cls");
	cout << "Введите айди вершины, от которой ищем расстояние\n";
	int id_from = check();
	cout << "Введите айди вершины, в которую идём\n";
	int id_to = check();
	try { 
		vector<Vertex> way = G.shortest_path(id_from, id_to);
		cout <<"Длина пути:"<<way[way.size() - 1].d << "\n";
		for (auto i = way.begin(); i != way.end(); i++) {
			cout<< i->id_v << "(" << i->d << ")  ";
		}
	}
	catch (error e) {
		cout << "Возникла ошибка при поиске кратчайшего пути\n";
		e.print();
	}
}

void obhod(Graph& G) {
	cout << "Введите айди вершины, от которой начинается обход\n";
	int id_from = check();
	cout << "Обход в ширину:\n";
	vector<Vertex> walk = G.walk_in_width(id_from);
	for (auto i = walk.begin(); i != walk.end(); i++) {
		cout << i->id_v << "  ";
	}
}

void task(Graph& G) {
	try {
		vector<Vertex> vertexes = G.get_vertexes();
		if (vertexes.size() == 0) throw error("Пустой граф");
		vector<float> average_d;
		for (auto i = vertexes.begin(); i != vertexes.end(); i++) {
			double sum = 0;
			for (auto j = vertexes.begin(); j != vertexes.end(); j++) {
				if (i->id_v != j->id_v) {
					try {
						vector<Vertex> way = G.shortest_path(i->id_v, j->id_v);
						sum += way[way.size() - 1].d;
					}
					catch (error e) {
						throw error("Граф не является связным");
					}
				}
			}
			average_d.push_back(sum / (vertexes.size() - 1));
		}
		float min = average_d[0];
		int min_i = 0;
		for (int i = 0; i < average_d.size(); i++) {
			if (average_d[i] < min)
			{
				min = average_d[i];
				min_i = i;
			}
		}
		cout << vertexes[min_i].id_v << " - айди вершины, которую нужно превратить в склад\n";
	}
	catch (error e) {
		e.print();
	}
}

int main() {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "RUS");
	Graph G;
	system("cls");
	while (true) {
		system("cls");
		std::cout << "Меню:\n";
		std::cout << "[1] - Использовать заданный граф\n";
		std::cout << "[2] - Создать/изменить граф вручную\n";
		std::cout << "[3] - Найти кратчайший маршрут\n";
		std::cout << "[4] - Обход графа\n";
		std::cout << "[5] - Выполнить задание\n";
		std::cout << "[ESC] - Выход\n";
		std::cout << "Граф: \n";
		try {
			G.print();
		}
		catch(error e){
			e.print();
		}
		int m = get_key();
		switch (m)
		{
		case 49:
			my_graph(G);
			break;
		case 50:
			create_graph(G);
			get_key();
			break;
		case 51:
			shortest_way(G);
			get_key();
			break;
		case 52:
			obhod(G);
			get_key();
			break;
		case 53:
			task(G);
			get_key();
			break;
		case 27:
			return 0;
			break;
		}
	}
}
