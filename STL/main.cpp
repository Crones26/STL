#include<iostream>
#include<array>
#include<vector>
#include<deque>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n----------------------------------\n"

//#define STL_ARRAY
//#define STL_VECTOR
//#define STL_STACK_1
//#define STL_QUEUE_1
#define STL_STACK_2
#define STL_QUEUE_2

template<typename T>void vector_info(const std::vector<T>& vec);
template<typename T>void stack_info(std::vector<T>& stack);
template<typename T>void queue_info(std::deque<T>& queue);

void main()
{
	setlocale(LC_ALL, "");

#ifdef STL_ARRAY
	const int N = 5;
	std::array<int, N> arr = { 3, 5, 8, 13, 21 };
	for (int i = 0; i < arr.size(); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;

#endif // STL_ARRAY

#ifdef STL_VECTOR
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
	vec.reserve(24);    //резервирует память ДО ЗАДАННОЙ ВМЕСТИТЕЛЬНОСТИ.
	                    //если текущая вместительность больше заданной, то ничего не происходит.
	                    //Резевирует столько вместительности, сколько мы хотим, если хотим больше чем есть на данный момент.
	vector_info(vec);
	vec.shrink_to_fit();//урезает вместительность до фактического размера вектора (size)
	                    //это можно сделать в целях экономии памяти, если мы уверены что в вектор
	                    //больше ничего не будет добавляться
	vector_info(vec);
	vec.resize(8);      //задает фактический размер Вектора.
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

#ifdef STL_STACK_1
	// Реализация стека с использованием vector
	cout << delimiter;
	std::vector<int> stack = { 1, 2, 3, 4, 5 };
	// Вывод содержимого стека
	cout << "Стек (сверху вниз): ";
	for (int i = stack.size() - 1; i >= 0; --i)
	{
		cout << stack[i] << tab;
	}
	cout << endl;
	cout << "Размер стека: " << stack.size() << endl;
	// Добавление элементов в стек
	stack.push_back(6);
	stack.push_back(7);
	cout << "Стек (сверху вниз): ";
	for (int i = stack.size() - 1; i >= 0; --i)
	{
		cout << stack[i] << tab;
	}
	cout << endl;
	cout << "Размер стека: " << stack.size() << endl;
	// Удаление элемента из стека
	stack.pop_back();
	cout << "Стек (сверху вниз): ";
	for (int i = stack.size() - 1; i >= 0; --i)
	{
		cout << stack[i] << tab;
	}
	cout << endl;
	cout << "Размер стека: " << stack.size() << endl;
#endif // STL_STACK_1

#ifdef STL_QUEUE_1
	// Реализация очереди с использованием deque
	cout << delimiter;
	std::deque<int> queue = { 10, 20, 30 };
	// Вывод содержимого очереди
	cout << "Очередь (с начала до конца): ";
	for (int i = 0; i < queue.size(); i++)
	{
		cout << queue[i] << tab;
	}
	cout << endl;
	cout << "Размер очереди: " << queue.size() << endl;
	// Добавление элементов в очередь
	queue.push_back(40);
	queue.push_back(50);
	cout << "Очередь (с начала до конца): ";
	for (int i = 0; i < queue.size(); i++)
	{
		cout << queue[i] << tab;
	}
	cout << endl;
	cout << "Размер очереди: " << queue.size() << endl;
	// Удаление элемента из очереди
	queue.pop_front();
	cout << "Очередь (с начала до конца): ";
	for (int i = 0; i < queue.size(); i++)
	{
		cout << queue[i] << tab;
	}
	cout << endl;
	cout << "Размер очереди: " << queue.size() << endl;

#endif // STL_QUEUE_1

#ifdef STL_STACK_2
	// Реализация стека с использованием vector
	cout << delimiter;
	std::vector<int> stack = { 1, 2, 3, 4, 5 };
	stack_info(stack);
	// Добавляем элементы в стек
	stack.push_back(6);
	stack.push_back(7);
	stack_info(stack);
	// Удаляем элемент из стека (LIFO)
	stack.pop_back();
	stack_info(stack);
#endif // STL_STACK_2

#ifdef STL_QUEUE_2
	// Реализация очереди с использованием deque
	cout << delimiter;
	std::deque<int> queue = { 10, 20, 30 };
	queue_info(queue);
	// Добавляем элементы в очередь
	queue.push_back(40);
	queue.push_back(50);
	queue_info(queue);
	// Удаляем элемент из очереди (FIFO)
	queue.pop_front();
	queue_info(queue);
#endif // STL_QUEUE_2

}

template<typename T>void vector_info(const std::vector<T>& vec)
{
	cout << "Size:    " << vec.size() << endl;
	cout << "Capacity:" << vec.capacity() << endl;
	cout << "MaxSize: " << vec.max_size() << endl;
}

template<typename T>void stack_info(std::vector<T>& stack)
{
	cout << "Стек (сверху вниз): ";
	for (int i = stack.size() - 1; i >= 0; --i)
	{
		cout << stack[i] << tab;
	}
	cout << endl;
	cout << "Размер стека: " << stack.size() << endl;
}

template<typename T>void queue_info(std::deque<T>& queue)
{
	cout << "Очередь (с начала до конца): ";
	for (const T& elem : queue)
	{
		cout << elem << tab;
	}
	cout << endl;
	cout << "Размер очереди: " << queue.size() << endl;
}