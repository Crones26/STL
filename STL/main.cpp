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
	vec.reserve(24);    //����������� ������ �� �������� ���������������.
	                    //���� ������� ��������������� ������ ��������, �� ������ �� ����������.
	                    //���������� ������� ���������������, ������� �� �����, ���� ����� ������ ��� ���� �� ������ ������.
	vector_info(vec);
	vec.shrink_to_fit();//������� ��������������� �� ������������ ������� ������� (size)
	                    //��� ����� ������� � ����� �������� ������, ���� �� ������� ��� � ������
	                    //������ ������ �� ����� �����������
	vector_info(vec);
	vec.resize(8);      //������ ����������� ������ �������.
	                    //!!! ��� ���������� �������� �������� � ����� ������� !!!
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
	// ���������� ����� � �������������� vector
	cout << delimiter;
	std::vector<int> stack = { 1, 2, 3, 4, 5 };
	// ����� ����������� �����
	cout << "���� (������ ����): ";
	for (int i = stack.size() - 1; i >= 0; --i)
	{
		cout << stack[i] << tab;
	}
	cout << endl;
	cout << "������ �����: " << stack.size() << endl;
	// ���������� ��������� � ����
	stack.push_back(6);
	stack.push_back(7);
	cout << "���� (������ ����): ";
	for (int i = stack.size() - 1; i >= 0; --i)
	{
		cout << stack[i] << tab;
	}
	cout << endl;
	cout << "������ �����: " << stack.size() << endl;
	// �������� �������� �� �����
	stack.pop_back();
	cout << "���� (������ ����): ";
	for (int i = stack.size() - 1; i >= 0; --i)
	{
		cout << stack[i] << tab;
	}
	cout << endl;
	cout << "������ �����: " << stack.size() << endl;
#endif // STL_STACK_1

#ifdef STL_QUEUE_1
	// ���������� ������� � �������������� deque
	cout << delimiter;
	std::deque<int> queue = { 10, 20, 30 };
	// ����� ����������� �������
	cout << "������� (� ������ �� �����): ";
	for (int i = 0; i < queue.size(); i++)
	{
		cout << queue[i] << tab;
	}
	cout << endl;
	cout << "������ �������: " << queue.size() << endl;
	// ���������� ��������� � �������
	queue.push_back(40);
	queue.push_back(50);
	cout << "������� (� ������ �� �����): ";
	for (int i = 0; i < queue.size(); i++)
	{
		cout << queue[i] << tab;
	}
	cout << endl;
	cout << "������ �������: " << queue.size() << endl;
	// �������� �������� �� �������
	queue.pop_front();
	cout << "������� (� ������ �� �����): ";
	for (int i = 0; i < queue.size(); i++)
	{
		cout << queue[i] << tab;
	}
	cout << endl;
	cout << "������ �������: " << queue.size() << endl;

#endif // STL_QUEUE_1

#ifdef STL_STACK_2
	// ���������� ����� � �������������� vector
	cout << delimiter;
	std::vector<int> stack = { 1, 2, 3, 4, 5 };
	stack_info(stack);
	// ��������� �������� � ����
	stack.push_back(6);
	stack.push_back(7);
	stack_info(stack);
	// ������� ������� �� ����� (LIFO)
	stack.pop_back();
	stack_info(stack);
#endif // STL_STACK_2

#ifdef STL_QUEUE_2
	// ���������� ������� � �������������� deque
	cout << delimiter;
	std::deque<int> queue = { 10, 20, 30 };
	queue_info(queue);
	// ��������� �������� � �������
	queue.push_back(40);
	queue.push_back(50);
	queue_info(queue);
	// ������� ������� �� ������� (FIFO)
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
	cout << "���� (������ ����): ";
	for (int i = stack.size() - 1; i >= 0; --i)
	{
		cout << stack[i] << tab;
	}
	cout << endl;
	cout << "������ �����: " << stack.size() << endl;
}

template<typename T>void queue_info(std::deque<T>& queue)
{
	cout << "������� (� ������ �� �����): ";
	for (const T& elem : queue)
	{
		cout << elem << tab;
	}
	cout << endl;
	cout << "������ �������: " << queue.size() << endl;
}