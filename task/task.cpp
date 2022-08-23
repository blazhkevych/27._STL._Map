/*Используя библиотеку STL, написать программу формирования
частотного словаря появления отдельных слов в некотором тексте.
Предусмотреть следующую функциональность:
• Чтение исходного текста из файла;
• Вывод информации обо всех словах;
• Вывод информации о наиболее часто встречающемся слове;
• Запись результата в файл.
При разработке программы использовать ассоциативный контейнер
map*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <Windows.h>
#include <conio.h>

using namespace std;

int main()
{
	SetConsoleCP(1251);
	/*
	Задает кодовую страницу ввода, используемую консолью, связанной с вызывающим процессом.
	Консоль использует страницу входного кода для преобразования ввода с клавиатуры
	в соответствующее символьное значение.
	*/
	SetConsoleOutputCP(1251);
	/*
	Задает выходную кодовую страницу, используемую консолью, связанной с вызывающим процессом.
	Консоль использует свою кодовую страницу вывода для преобразования символьных значений,
	записанных различными функциями вывода, в изображения, отображаемые в окне консоли.
	*/

	cout << "Введите путь к файлу: ";
	string pathToFile;
	cin >> pathToFile;

	ifstream f_read(pathToFile, ios::in);

	if (!f_read.is_open()) // Если открытие файла завершилось неудачей - выходим.
	{
		cout << "File opening error!\n";
		return 0;
	}

	string str{ istreambuf_iterator<char>(f_read), istreambuf_iterator<char>() }; // Вычитываем весь текстовый файл.

	// Привести все буквы один регистр верхний или нижний.
	transform(str.begin(), str.end(), str.begin(), tolower);

	map<string, int > Words;
	stringstream ss(str);
	string buf;

	while (ss >> buf)
	{
		int found = buf.find_first_of(" ./*-+~!@#$%^&*()_+`1234567890-=|\\{}[]:\";',./<>?");
		while (found >= 0)
		{
			buf.erase(found, 1);
			found = buf.find_first_of(" ./*-+~!@#$%^&*()_+`1234567890-=|\\{}[]:\";',./<>?");
		}
		if (!buf.empty())
		{
			bool coincidence{ false }; // Совпадение.
			for (map<string, int >::iterator it = Words.begin(); it != Words.end(); it++)
			{
				if (it->first == buf) // Входящее слово совпало с словом из списка.
				{
					it->second++;
					coincidence = true;
				}
			}
			if (coincidence == false) // Если совпадений не было, добавляем.
			{
				Words.insert(map<string, int >::value_type(buf, 1));
			}
		}
	}
	f_read.close();

	map<string, int>::iterator result;

	while (true)
	{
		system("cls");
		cout << "\tГлавное меню.\n"
			"\n1. Вывод информации обо всех словах."
			"\n2. Вывод информации о наиболее часто встречающемся слове."
			"\n3. Запись результата в файл и выход."
			<< endl;
		int choice_mainMenu{};
		cout << "\n >>> : ";
		cin >> choice_mainMenu;
		switch (choice_mainMenu)
		{
		case 1:
			system("cls");
			cout << "Главное меню."
				"\n\t1. Вывод информации обо всех словах."
				<< endl;

			// Вывод содержимого контейнера.
			for (map<string, int >::iterator it = Words.begin(); it != Words.end(); it++)
				cout << it->first << " - " << it->second << endl;

			cout << "\nГотово !" << endl
				<< "\nДля продолжения нажмите любую клавишу." << endl;
			_getch();
			break;
		case 2:
		{
			system("cls");
			cout << "Главное меню."
				"\n\t2. Вывод информации о наиболее часто встречающемся слове."
				<< endl;

			result = max_element(Words.begin(), Words.end(),
				[](const pair<string, int>& a, const pair<string, int>& b)->bool { return a.second < b.second; });
			cout << result->first << " - " << result->second << "\n";

			cout << "\nГотово !" << endl
				<< "\nДля продолжения нажмите любую клавишу." << endl;
			_getch();
			break;
		}
		case 3:
		{
			system("cls");
			cout << "Главное меню."
				"\n\t3. Запись результата в файл и выход."
				<< endl;

			// Создаём выходной файловый поток и присоединяем к нему файл, который открывается на запись в текстовом режиме.
			ofstream out("2.txt", ios_base::out | ios_base::trunc);
			if (!out.is_open()) // Если открытие файла завершилось неудачей - выходим.
			{
				cout << "Error!\n";
				return 0;
			}

			for (map<string, int >::iterator it = Words.begin(); it != Words.end(); it++)
			{
				out << it->first << " - " << it->second << "\n";
			}

			out << "\n" << "Наиболее часто встречающееся слово:" << "\n"
				<< result->first << " - " << result->second << "\n";

			out.close(); // Закрываем файловый поток.

			cout << "\nГотово !" << endl;
			return 0;
		}
		default:
			cout << "Ошибка ввода !" << endl;
			break;
		}
	}
}