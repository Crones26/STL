#include<iostream>
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

template<typename T> void vector_info(const std::vector<T>& vec);
template<typename T> void list_info(const std::list<T>& lst);

void insert_at_index(std::vector<int>& vec, int index, int value);  // Вставка в вектор
void remove_at_index(std::vector<int>& vec, int index);             // Удаление из вектора
void insert_at_index(std::list<int>& lst, int index, int value);    // Вставка в список
void remove_at_index(std::list<int>& lst, int index);               // Удаление из списка

int get_valid_index(int max_size, const std::string& action, bool allow_equal = false); // Получение корректного индекса

void main()
{
    setlocale(LC_ALL, "");

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
    cout << "Исходный вектор: " << endl;
    for (int i = 0; i < vec.size(); i++)
    {
        cout << vec[i] << tab;
    }
    cout << endl;
    vector_info(vec);

    // Вставка в вектор
    int index = get_valid_index(vec.size(), "вставка", true);  // Проверка корректности индекса для вставки
    int value;
    cout << "Введите значение для вставки в вектор: ";
    cin >> value;
    insert_at_index(vec, index, value);
    cout << "Вектор после вставки: " << endl;
    for (int i : vec) cout << i << tab;
    cout << endl;
    vector_info(vec);

    // Удаление из вектора
    index = get_valid_index(vec.size(), "удаление");  // Проверка корректности индекса для удаления
    remove_at_index(vec, index);
    cout << "Вектор после удаления: " << endl;
    for (int i : vec) cout << i << tab;
    cout << endl;
    vector_info(vec);
#endif // STL_VECTOR

#ifdef STL_LIST
    // list - это контейнер, который хранит данные в виде двусвязного списка.
    std::list<int> lst = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34 };
    cout << "Исходный список: " << endl;
    for (int i : lst) cout << i << tab;
    cout << endl;
    list_info(lst);

    // Вставка в список
    int index = get_valid_index(lst.size(), "вставка", true);  // Проверка корректности индекса для вставки
    int value;
    cout << "Введите значение для вставки в список: ";
    cin >> value;
    insert_at_index(lst, index, value);
    cout << "Список после вставки: " << endl;
    for (int i : lst) cout << i << tab;
    cout << endl;
    list_info(lst);

    // Удаление из списка
    index = get_valid_index(lst.size(), "удаление");  // Проверка корректности индекса для удаления
    remove_at_index(lst, index);
    cout << "Список после удаления: " << endl;
    for (int i : lst) cout << i << tab;
    cout << endl;
    list_info(lst);
#endif // STL_LIST
}

// Получения корректного индекса от пользователя
int get_valid_index(int max_size, const std::string& action, bool allow_equal)
{
    int index;
    do
    {
        cout << "Введите индекс для " << action;
        if (allow_equal)
            cout << " (0-" << max_size << "): ";
        else
            cout << " (0-" << max_size - 1 << "): ";
        cin >> index;
        if (index < 0 || (allow_equal ? index > max_size : index >= max_size))
        {
            cout << "ОШИБКА: Некорректный индекс! Попробуйте снова." << endl;
        }
    } while (index < 0 || (allow_equal ? index > max_size : index >= max_size));
    return index;
}

// Вывод информации о векторе
template<typename T> void vector_info(const std::vector<T>& vec)
{
    cout << "Size:    " << vec.size() << endl;
    cout << "Capacity:" << vec.capacity() << endl;
    cout << "MaxSize: " << vec.max_size() << endl;
}
// Вывод информации о списке
template<typename T> void list_info(const std::list<T>& lst)
{
    cout << "Size:    " << lst.size() << endl;
    cout << "MaxSize: " << lst.max_size() << endl;
}
// Вставка элемента в вектор по указанному индексу
void insert_at_index(std::vector<int>& vec, int index, int value)
{
    vec.insert(vec.begin() + index, value);
}
// Удаление элемента из вектора по указанному индексу
void remove_at_index(std::vector<int>& vec, int index)
{
    vec.erase(vec.begin() + index);
}
// Вставка элемента в список по указанному индексу
void insert_at_index(std::list<int>& lst, int index, int value)
{
    auto it = lst.begin();
    //std::list<int>::iterator it = lst.begin();
    std::advance(it, index);
    lst.insert(it, value);
}
// Удаление элемента из списка по указанному индексу
void remove_at_index(std::list<int>& lst, int index)
{
    auto it = lst.begin();
    //std::list<int>::iterator it = lst.begin();
    std::advance(it, index);
    lst.erase(it);
}
