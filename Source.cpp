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

size_t lcg() {
	static size_t x = 0;
	x = (1021 * x + 24631) % 10;
	return x;
}

int get_key()
{
	int key = _getch();
	if ((key == 0) || (key == 224)) key = _getch();
	return key;
};

int main() {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "RUS");
	Graph G;

	while (true) {

		system("cls");
		std::cout << "Меню:\n";
		std::cout << "[1] - Случайно сгенерированный граф порядка 10\n";
		std::cout << "[2] - Создать граф вручную\n";
		std::cout << "[3] - Найти кратчайший маршрут\n";
		std::cout << "[4] - Выполнить задание\n";
		std::cout << "[5] - Изменить граф\n";
		std::cout << "[ESC] - Выход\n";

		try {
			G.print();
		}
		catch(error){

		}
		int m = get_key();

		switch (m)
		{
		case 49:
			//random_graph();
			get_key();
			break;
		case 50:
			
			get_key();
			break;
		case 51:
			
			get_key();
			break;
		case 52:
			
			get_key();
			break;
		case 53:

			get_key();
			break;
		case 27:
			return 0;
			break;
		}
	}
}
