#include <iostream>
#include<array>
#include<vector>
#include<list>

using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n----------------------------------\n"

//#define STL_ARRAY
//#define STL_VECTOR
#define STL_LIST

template<typename T>void vector_info(const std::vector<T>& vec);

void main()
{
	setlocale(LC_ALL, "");
	//cout << "Hello STL" << endl;

#ifdef STL_ARRAY
	//array - это контейнер, который хранит данные в виде статического массива.
	//При создании 'array', кроме типа хранимых значений, так же обязательно нужно указать
	//количество хранимых значений.

	const int N = 5;
	std::array<int, N> arr = { 3, 5, 8, 13, 21 };
	for (int i = 0; i < arr.size(); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;

#endif // STL_ARRAY

#ifdef STL_VECTOR
	//vector - это контейнер, который хранит данные в виде динамического массива.
	//При создании Вектора обязательно задают только тип хранимых элементов.
	std::vector<int> vec = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34 };
	for (int i = 0; i < vec.size(); i++)
	{
		cout << vec[i] << tab;
	}
	cout << endl;
	vector_info(vec);
	vec.push_back(55);
	for (int i = 0; i < vec.size(); i++)
	{
		cout << vec.at(i) << tab;
	}
	cout << endl;
	vector_info(vec);
	vec.reserve(24);	//резервирует память ДО ЗАДАННОЙ ВМЕСТИТЕЛЬНОСТИ.
	                    //если текущая вместительность больше заданной, то ничего не происходит.
	                    //Резевирует столько вместительности, сколько мы хотим, если хотим больше чем есть на данный момент.
	vector_info(vec);

	vec.shrink_to_fit();//урезает вместительность до фактического размера вектора (size)
	                    //это можно сделать в целях экономии памяти, если мы уверены что в вектор
	                    //больше ничего не будет добавляться
	vector_info(vec);
	vec.resize(8);		//задает фактический размер Вектора.
	                    //!!! При уменьшении теряются значения в конце Вектора !!!
	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
	vector_info(vec);
	//vec.resize(14);
	for (int i : vec)cout << i << tab; cout << endl;
	vector_info(vec);

	vec.insert(vec.begin() + 4, { 1024, 2048, 3072, 4096 });
	for (int i : vec)cout << i << tab; cout << endl;

	int index;
	int count;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите количество добавляемых элементов: "; cin >> count;
	cout << "Введите значение добавляемого элемента: "; cin >> value;

	if (index >= 0 && index <= vec.size())vec.insert(vec.begin() + index, count, value);
	else cout << "Индекс вне диапазона!" << endl;
	for (int i : vec)cout << i << tab; cout << endl;
	vector_info(vec);

	cout << "Введите индекс удаляемого элемента: "; cin >> index;
	cout << "Введите количество удаляемых элементов: "; cin >> count;
	if (index >= 0 && index <= vec.size())vec.erase(vec.begin() + index, vec.begin() + index + count);
	else cout << "Индекс вне диапазона!" << endl;
	for (int i : vec)cout << i << tab; cout << endl;

#endif // STL_VECTOR

#ifdef STL_LIST
	// list - это контейнер, который хранит данные в виде двусвязного списка.
	std::list<int> list = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34 };
	for (int i : list)cout << i << tab; cout << endl;
	cout << list.front() << endl;
	cout << list.back() << endl;

	int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;

	if (index >= 0 && index <= list.size())
	{
		std::list<int>::iterator it = list.begin();
		std::advance(it, index);
		list.insert(it, value);
	}
	else
	{
		cout << "Индекс вне диапазона!" << endl;
	}
	for (int i : list)cout << i << tab; cout << endl;

	cout << "Введите индекс удаляемого элемента: "; cin >> index;
	if (index >= 0 && index <= list.size())
	{
		std::list<int>::iterator it = list.begin();
		std::advance(it, index); 
		list.erase(it);
	}
	else
	{
		cout << "Индекс вне диапазона!" << endl;
	}
	for (int i : list)cout << i << tab; cout << endl;
#endif // STL_LIST
}

template<typename T>void vector_info(const std::vector<T>& vec)
{
	cout << "Size:    " << vec.size() << endl;
	cout << "Capacity:" << vec.capacity() << endl;
	cout << "MaxSize: " << vec.max_size() << endl;
}
