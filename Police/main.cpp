#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<conio.h>
#include<map>
#include<ctime>
#include<string>
#include<list>

using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n------------------------------------------------------------------------\n"

const std::map<int, std::string> VIOLATIONS =
{
	{1, "������ ������������"},
	{2, "�������� � ������������ �����"},
	{3, "����������� ��������"},
	{4, "���������� ��������"},
	{5, "���������� ������������� �������������"},
	{6, "���������� ����� ���������� �����������"},
	{7, "���������� ���������"},
	{8, "������ �� ������� ����"},
	{9, "����� �� ��������� ������"},
	{10, "����� �� �����������"},
	{11, "���� � ��������� ���������"},
	{12, "����������� �������"},
	{13, "�������� ��������� � ����������� ����������"},
	{14, "��������� ������������� �����"},
	{15, "���������� ������������ �������� �� ���"},
	{16, "��������� ������� ��� ������"},
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
		//1. ������� ����. ������ ��� ����, ����� ���������� ���������� ������ 
		char* time_buffer = new char[time.size() + 1] {};
		//2. �������� ���������� ������ � �����:
		strcpy(time_buffer, time.c_str());
		//������� strcpy(dst, src); �������� ���������� ������-��������� � ������ ����������

		//3. ������� ������ ��� �������� ��������� �������
		int time_elements[5]{};
		int i = 0;
		char delimiters[] = ":./ ";
		for (char* pch = strtok(time_buffer, delimiters); pch; pch = strtok(NULL, delimiters))
			time_elements[i++] = std::atoi(pch);
		//������� std::atoi() 'ASCII-string to int' ����������� ������ � ����� �����.
		delete[] time_buffer;

		//4. ��������� �������� ������� � ��������� 'tm':
		this->time.tm_hour = time_elements[0];
		this->time.tm_min = time_elements[1];
		this->time.tm_mday = time_elements[2];
		this->time.tm_mon = time_elements[3];
		this->time.tm_year = time_elements[4] - 1900;
		//this->time = time;
	}

	//				Constructors:
	Crime
	(
		int violation_id,
		const std::string& place,
		const std::string& time
	)
	{
		this->time = {};
		this->set_violation_id(violation_id);
		this->set_place(place);
		this->set_time(time);
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
	return os << obj.get_time() << ":\t" << obj.get_place() << " - " << obj.get_violation();
}

void print(const std::map<std::string, std::list<Crime>>& base);
void save(const std::map<std::string, std::list<Crime>>& base, const std::string& filename);

void main()
{	/*Crime crime(1, "��. ������", "18:10 1.09.2024");
	cout << crime << endl;*/
	setlocale(LC_ALL, "");
	std::map<std::string, std::list<Crime>> base =
	{
		{"a777bb", {Crime(1, "��. ������", "18:10 1.09.2024"), Crime(2, "��. �������", "12:25 20.08.2024")}},
		{"a000bb", {Crime(6, "��. �����������", "17:50 1.08.2024"), Crime(8, "��. �����������", "17:45 01.08.2024")}},
		{"a001aa", {Crime(10, "��. ������������", "21:50 1.08.2024"), Crime(9, "��. ������������", "21:51 1.08.2024"), Crime(11, "��. ������������", "21:51 1.08.2024"), Crime(12, "��. ������������", "22:05 1.08.2024")}},
	};

	print(base);
	save(base, "base.txt");
}

void print(const std::map<std::string, std::list<Crime>>& base)
{
	cout << delimiter << endl;
	for (std::map<std::string, std::list<Crime>>::const_iterator map_it = base.begin();
		map_it != base.end();
		++map_it)
	{
		cout << map_it->first << ":\n";
		for (std::list<Crime>::const_iterator it = map_it->second.begin(); it != map_it->second.end(); ++it)
		{
			cout << "\t" << *it << endl;
		}
		cout << delimiter << endl;
	}
}

void save(const std::map<std::string, std::list<Crime>>& base, const std::string& filename)
{
	std::ofstream fout(filename);
	fout << delimiter << endl;
	for (std::map<std::string, std::list<Crime>>::const_iterator map_it = base.begin();
		map_it != base.end();
		++map_it)
	{
		fout << map_it->first << ":\n";
		for (std::list<Crime>::const_iterator it = map_it->second.begin(); it != map_it->second.end(); ++it)
		{
			fout << "\t" << *it << endl;
		}
		fout << delimiter << endl;
	}
	fout.close();
	std::string command = "notepad " + filename;
	system(command.c_str());
}