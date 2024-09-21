﻿#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <fstream>
#include <conio.h>
#include <map>
#include <ctime>
#include <string>
#include <sstream>
#include <list>
#include <sstream>
#include <cstring>

using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n------------------------------------------------------------------------\n"

const std::map<int, std::string> VIOLATIONS =
{
	{1, "Ремень безопасности"},
	{2, "Парковка в неположенном месте"},
	{3, "Пересечение сплошной"},
	{4, "Превышение скорости"},
	{5, "Отсутствие водительского удостоверение"},
	{6, "Отсутствие права управления автомобилем"},
	{7, "Отсутствие страховки"},
	{8, "Проезд на красный свет"},
	{9, "Выезд на встречную полосу"},
	{10, "Дрифт на перекрестке"},
	{11, "Езда в нетрезвом состоянии"},
	{12, "Оскорбление офицера"},
	{13, "Внесение изменений в конструкцию автомобиля"},
	{14, "Перевозка негабаритного груза"},
	{15, "Превышение максимальной нагрузки на ось"},
	{16, "Перевозка ребенка без кресла"},
};

class Crime
{
	//std::string license_plate;
	int id;
	std::string place;
	tm time;
public:
	/*const std::string& get_licence_plate()const
	{
		return license_plate;
	}*/
	int get_violation_id()const
	{
		return id;
	}
	const std::string& get_violation()const
	{
		return VIOLATIONS.at(id);
	}
	const std::string& get_place()const
	{
		return place;
	}
	const std::string get_time()const
	{
		/*std::string result = asctime(&time);
		result.pop_back();
		return result;*/
		const int SIZE = 256;
		char formatted[SIZE]{};
		strftime(formatted, SIZE, "%R %e.%m.%Y", &time);
		return formatted;
	}
	const time_t get_timestamp()const
	{
		tm copy = time;
		return mktime(&copy);
	}
	/*void set_licence_plate(const std::string& license_plate)
	{
		this->license_plate = license_plate;
	}*/
	void set_violation_id(int id)
	{
		this->id = id;
	}
	void set_place(const std::string& place)
	{
		this->place = place;
	}
	void set_time(const std::string& time)
	{
		//1. Создаем врем. строку для того, чтобы пропарсить полученную строку 
		char* time_buffer = new char[time.size() + 1] {};
		//2. Копируем полученную строку в буфер:
		strcpy(time_buffer, time.c_str());
		//Функция strcpy(dst, src); копирует содержимое строки-источника в строку получателя

		//3. Создаем массив для хранения элементов времени
		int time_elements[5]{};
		int i = 0;
		char delimiters[] = ":./ ";
		for (char* pch = strtok(time_buffer, delimiters); pch; pch = strtok(NULL, delimiters))
			time_elements[i++] = std::atoi(pch);
		//Функция std::atoi() 'ASCII-string to int' преобразует строку в целое число.
		delete[] time_buffer;

		//4. Сохраняем элементы времени в структуру 'tm':
		this->time.tm_hour = time_elements[0];
		this->time.tm_min = time_elements[1];
		this->time.tm_mday = time_elements[2];
		this->time.tm_mon = time_elements[3];
		this->time.tm_year = time_elements[4] - 1900;
		//this->time = time;
	}
	void set_timestamp(time_t timestamp)
	{
		time = *localtime(&timestamp);
	}

	//				Constructors:
	Crime(int violation_id, const std::string& place, const std::string& time)
	{
		this->time = {};
		set_violation_id(violation_id);
		set_place(place);
		set_time(time);
#ifdef DEBUG
		cout << "Constructor:\t" << this << endl;
#endif // DEBUG
	}
	~Crime()
	{
#ifdef DEBUG
		cout << "Destructor:\t" << this << endl;
#endif // DEBUG
	}
};

std::ostream& operator<<(std::ostream& os, const Crime& obj)
{
	return os << obj.get_time() << ":\t " << obj.get_place() << " - " << obj.get_violation();
}
std::ofstream& operator<<(std::ofstream& ofs, const Crime& obj)
{
	ofs << obj.get_violation_id() << " " << obj.get_timestamp() << "  " << obj.get_place();
	return ofs;
}
std::istream& operator>>(std::istream& is, Crime& obj)
{
	int id;
	time_t timestamp;
	std::string place;
	is >> id >> timestamp;
	std::getline(is, place, ',');
	is.ignore();
	obj.set_violation_id(id);
	obj.set_timestamp(timestamp);
	obj.set_place(place);
	return is;
}
void print(const std::map<std::string, std::list<Crime>>& base);
void save(const std::map<std::string, std::list<Crime>>& base, const std::string& file);
std::map<std::string, std::list<Crime>> load(const std::string& file);

void main()
{
	setlocale(LC_ALL, "");
	/*Crime crime(1, "Ул. Ленина", "18:10 1.09.2024");
	cout << crime << endl;*/

	std::map<std::string, std::list<Crime>> base
	{
		{"a777bb", {Crime(1, "Ул. Ленина", "18:10 1.09.2024"), Crime(2, "пл. Свободы", "12:25 20.08.2024")}},
		{"a000bb", {Crime(6, "Ул. Космонавтов", "17:50 1.08.2024"), Crime(8, "ул. Космонавтов", "17:45 01.08.2024")}},
		{"a001aa", {Crime(10, "Ул. Пролетарская", "21:50 1.08.2024"), Crime(9, "Ул. Пролетарская", "21:51 1.08.2024"), Crime(11, "Ул. Пролетарская", "21:51 1.08.2024"), Crime(12, "Ул. Пролетарская", "22:05 1.08.2024")}},

	};

	base = load("base.txt");
	//print(base);
	//save(base, "base.txt");
	std::map<std::string, std::list<Crime>> crime_map = load("base.txt");
	//print(crime_map);
	std::string command = "notepad base.txt";
	system(command.c_str());
}

void save(const std::map<std::string, std::list<Crime>>& base, const std::string& file)
{
	std::ofstream fout(file);
	for (std::map<std::string, std::list<Crime>>::const_iterator it = base.begin(); it != base.end(); ++it)
	{
		fout << it->first << ":\t";
		for (std::list<Crime>::const_iterator const_it = it->second.begin(); const_it != it->second.end(); ++const_it)
		{
			fout << *const_it << ",";
		}
		//fout.seekp(-1, std::ios::cur); //Метод seekp(offset, direction) задает позицию курсора записи (p - put)
		// -1 - смещение  на 1 символ обратно, std::ios::cur - показывает что смещение производится от текущей позиции курсора
		//fout << ";\n";
		fout << endl;
	}
	fout.close();

	std::string command = "notepad ";
	command += file;
	system(command.c_str());
}

std::map<std::string, std::list<Crime>> load(const std::string& file)
{
	std::map<std::string, std::list<Crime>> base;
	std::ifstream fin(file);

	if (fin.is_open())
	{
		std::string licence_plate;
		while (std::getline(fin, licence_plate, ':'))
		{
			std::list<Crime> crimes;
			std::string crimes_str;
			std::getline(fin, crimes_str);

			char* sz_buffer = new char[crimes_str.size() + 1];
			strcpy(sz_buffer, crimes_str.c_str());
			char delimiters[] = ",";
			Crime crime(0, "place", "00:00 01.01.2000");
			for (char* pch = strtok(sz_buffer, delimiters); pch; pch = strtok(NULL, delimiters))
			{
				std::string s_crime(pch);
				std::stringstream ss_crime(s_crime, std::ios_base::in | std::ios_base::out);
				
				ss_crime >> crime;
				crimes.push_back(crime);
			}
			delete[] sz_buffer;

			base[licence_plate] = crimes;
		}
	}
	else
	{
		std::cerr << "Error: file not found" << endl;
	}

	return base;
}

void print(const std::map<std::string, std::list<Crime>>& base)
{
	for (std::map<std::string, std::list<Crime>>::const_iterator map_it = base.begin(); map_it != base.end(); ++map_it)
	{
		cout << map_it->first << ":\n";
		for (std::list<Crime>::const_iterator it = map_it->second.begin(); it != map_it->second.end(); ++it)
		{
			cout << "\t" << *it << endl;
		}
		cout << delimiter << endl;
	}
}