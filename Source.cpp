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
	G.add_vertex(1);
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
	G.add_edge(6, 7, 2);

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
			try { G.remove_vertex(id_del); }
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
			try { G.add_edge(id_from, id_to, w); }
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
			try { G.remove_edge(id_from_del, id_to_del); }
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
		int sum = -1;
		for (auto i = way.begin(); i != way.end(); i++) {
			for (auto j = i->edges.begin(); j != i->edges.end(); j++) {
				if (j->id_to == (i++)->id_v) sum += j->weight;
				i--;
			}
		}
		cout << "Кратчайший путь составляет:"<< sum <<"\n";
	}
	catch (error e) {
		cout << "Возникла ошибка при поиске кратчайшего пути\n";
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
		std::cout << "[4] - Выполнить задание\n";
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
			
			get_key();
			break;
		case 27:
			return 0;
			break;
		}
	}
}
