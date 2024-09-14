#include<iostream>
#include<map>
#include<vector>
#include<string>
#include<fstream>
#include<cstdlib>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::ifstream;
using std::ofstream;

#define tab "\t"
#define delimiter "\n-------------------------------------\n"

// Функция для загрузки данных из файла
void loadDatabase(std::map<string, vector<string>>& db, const string& filename) {
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Не удалось открыть файл для чтения." << endl;
        return;
    }

    string plate, violation;
    while (getline(file, plate))
    {
        vector<string> violations;
        while (getline(file, violation) && violation != "---")
        {
            violations.push_back(violation);
        }
        db[plate] = violations;
    }

    file.close();
}
// Функция для сохранения данных в файл
void saveDatabase(const std::map<string, vector<string>>& db, const string& filename) {
    ofstream file(filename);
    if (!file.is_open())
    {
        cout << "Не удалось открыть файл для записи." << endl;
        return;
    }
    for (const auto& entry : db)
    {
        file << entry.first << endl;
        for (const auto& violation : entry.second)
        {
            file << violation << endl;
        }
        file << "---" << endl; // Разделитель для каждого автомобиля
    }
    file.close();
}
// Функция для вывода всех данных
void printDatabase(const std::map<string, vector<string>>& db)
{
    if (db.empty())
    {
        cout << "База данных пуста." << endl;
        return;
    }
    cout << delimiter << "Все данные в базе нарушений:" << endl;
    for (const auto& entry : db)
    {
        cout << "Автомобиль с номером: " << entry.first << endl;
        for (const auto& violation : entry.second)
        {
            cout << tab << "Нарушение: " << violation << endl;
        }
    }
}
// Функция для открытия файла
void openFile(const string& filename) {
    // Открываем файл с использованием системной команды в зависимости от ОС
#ifdef _WIN32
    system(("start " + filename).c_str());
#elif __APPLE__
    system(("open " + filename).c_str());
#elif __linux__
    system(("xdg-open " + filename).c_str());
#else
    cout << "Открытие файла не поддерживается на этой ОС." << endl;
#endif
}
// Функция для удаления правонарушения по номеру автомобиля
void removeViolation(std::map<string, vector<string>>& db, const string& plate, const string& filename) {
    auto it = db.find(plate);
    if (it != db.end())
    {
        cout << "Список правонарушений для автомобиля с номером " << plate << ":" << endl;
        for (size_t i = 0; i < it->second.size(); ++i)
        {
            cout << i + 1 << ". " << it->second[i] << endl;
        }

        cout << "Введите номер правонарушения, которое хотите удалить: ";
        size_t index;
        cin >> index;

        if (index > 0 && index <= it->second.size())
        {
            it->second.erase(it->second.begin() + index - 1); // Удаление выбранного нарушения
            if (it->second.empty())
            {
                db.erase(it); // Если больше нет нарушений, удаляем запись об автомобиле
            }
            saveDatabase(db, filename); // Сохраняем изменения
            cout << "Правонарушение удалено и база данных обновлена." << endl;
        }
        else
        {
            cout << "Неверный индекс. Попробуйте снова." << endl;
        }
    }
    else
    {
        cout << "Автомобиль с номером " << plate << " не найден." << endl;
    }
}

int main() {
    setlocale(LC_ALL, "");

    std::map<string, vector<string>> trafficDatabase;
    string filename = "traffic_database.txt";
    loadDatabase(trafficDatabase, filename);

    auto addViolation = [](std::map<string, vector<string>>& db, const string& plate, const string& violation, const string& filename)
        {
        if (db.find(plate) != db.end())
        {
            db[plate].push_back(violation);
        }
        else
        {
            db[plate] = vector<string>{ violation };
        }
        saveDatabase(db, filename); // Автосохранение после добавления
        };

    int choice = 0;

    while (true)
    {
        cout << delimiter;
        cout << "Выберите действие:\n";
        cout << "1. Добавить правонарушение\n";
        cout << "2. Проверить правонарушения по номеру автомобиля\n";
        cout << "3. Открыть и просмотреть все сохранённые данные\n";
        cout << "4. Удалить правонарушение\n";
        cout << "5. Открыть файл с нарушениями\n";
        cout << "6. Сохранить данные и выйти\n";
        cout << "Ваш выбор: ";
        cin >> choice;

        if (choice == 1)
        {
            string plate, violation;
            cout << "Введите номер автомобиля: ";
            cin >> plate;

            cout << "Введите правонарушение: ";
            cin.ignore();
            getline(cin, violation);

            addViolation(trafficDatabase, plate, violation, filename);
            cout << "Данные добавлены и сохранены!" << endl;
        }
        else if (choice == 2)
        {
            string searchPlate;
            cout << "Введите номер автомобиля для поиска: ";
            cin >> searchPlate;

            auto it = trafficDatabase.find(searchPlate);
            if (it != trafficDatabase.end())
            {
                cout << "Автомобиль с номером " << searchPlate << " имеет следующие правонарушения:" << endl;
                for (const auto& violation : it->second) 
                {
                    cout << "- " << violation << endl;
                }
            }
            else
            {
                cout << "Автомобиль с номером " << searchPlate << " не найден." << endl;
            }
        }
        else if (choice == 3)
        {
            printDatabase(trafficDatabase);
        }
        else if (choice == 4)
        {
            string plate;
            cout << "Введите номер автомобиля, для которого нужно удалить правонарушение: ";
            cin >> plate;

            removeViolation(trafficDatabase, plate, filename);
        }
        else if (choice == 5)
        {
            openFile(filename);
        }
        else if (choice == 6)
        {
            saveDatabase(trafficDatabase, filename);
            cout << "Данные сохранены. Выход из программы." << endl;
            break;
        }
        else
        {
            cout << "Неверный выбор. Попробуйте снова." << endl;
        }
    }
}
