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

using namespace std;

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

	while (true) {

		system("cls");
		std::cout << "Меню:\n";
		std::cout << "[1] - Случайно сгенерированный граф порядка 10\n";
		std::cout << "[2] - Создать граф\n";
		std::cout << "[3] - Сортировка обратно отсортированного массива\n";
		std::cout << "[4] - Время сортировки\n";
		std::cout << "[ESC] - Выход\n";

		int m = get_key();

		switch (m)
		{
		case 49:
			
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
		case 27:
			return 0;
			break;
		}
	}
}
