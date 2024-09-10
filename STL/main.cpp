#include<iostream>
#include<array>
#include<vector>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n----------------------------------\n"

//#define STL_ARRAY
#define STL_VECTOR

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
	vec.resize(14);
	for (int i : vec)cout << i << tab; cout << endl;
	vector_info(vec);
#endif // STL_VECTOR

}

template<typename T>void vector_info(const std::vector<T>& vec)
{
	cout << "Size:    " << vec.size() << endl;
	cout << "Capacity:" << vec.capacity() << endl;
	cout << "MaxSize: " << vec.max_size() << endl;
}