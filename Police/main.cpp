#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <iomanip>

using std::cin;
using std::cout;
using std::endl;

#define delimiter "\n------------------------------------------------------------------------\n"

// Карта нарушений
const std::map<int, std::string> VIOLATIONS =
{
    {1, "Ремень безопасности"},
    {2, "Парковка в неположенном месте"},
    {3, "Пересечение сплошной"},
    {4, "Превышение скорости"},
    {5, "Отсутствие водительского удостоверения"},
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
    int id;
    std::string place;
    std::string time;
    std::string custom_violation;

public:
    Crime(int violation_id, const std::string& place, const std::string& time, const std::string& custom_violation = "")
        : id(violation_id), place(place), time(time), custom_violation(custom_violation) {}

    int get_violation_id() const
    {
        return id;
    }

    const std::string& get_violation() const
    {
        return (id == 0) ? custom_violation : VIOLATIONS.at(id);
    }

    const std::string& get_place() const
    {
        return place;
    }

    const std::string& get_time() const
    {
        return time;
    }
};

// Перегрузка оператора вывода для объектов Crime
std::ostream& operator<<(std::ostream& os, const Crime& obj)
{
    return os << obj.get_time() << " " << obj.get_place() << " " << obj.get_violation();
}

// Функция для загрузки базы данных из файла
void loadDatabase(std::map<std::string, std::vector<Crime>>& db, const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cout << "Не удалось открыть файл для чтения. Создан новый файл: " << std::endl;
        return;
    }

    std::string plate, place, time, custom_violation;
    int violation_id;
    while (file >> plate >> violation_id)
    {
        file.ignore();
        std::getline(file, place);
        std::getline(file, time);
        std::getline(file, custom_violation);
        db[plate].push_back(Crime(violation_id, place, time, custom_violation));
    }

    file.close();
}

// Функция для сохранения базы данных в файл с добавлением новых данных
void saveDatabase(const std::map<std::string, std::vector<Crime>>& db, const std::string& filename)
{
    std::ofstream file(filename);         // Открываем файл в режиме записи (перезапись)
    if (!file.is_open())
    {
        std::cout << "Не удалось открыть файл для записи." << std::endl;
        return;
    }

    for (const auto& entry : db)
    {
        file << delimiter;
        file << entry.first << std::endl;  // Сохраняем номер автомобиля
        for (const auto& crime : entry.second)
        {
            file << crime.get_place() << std::endl;         // Сохраняем место нарушения
            file << crime.get_time() << std::endl;          // Сохраняем время нарушения
            file << crime.get_violation() << std::endl;     // Сохраняем текстовое описание правонарушения (если custom)
        }
    }

    file.close();
}

// Функция для удаления нарушения по номеру автомобиля
void removeViolation(std::map<std::string, std::vector<Crime>>& db, const std::string& plate, const std::string& filename)
{
    auto it = db.find(plate);
    if (it != db.end())
    {
        std::cout << "Список правонарушений для автомобиля с номером " << plate << ":" << std::endl;
        int index = 1;
        for (const auto& crime : it->second)
        {
            std::cout << index++ << ". " << crime << std::endl;
        }

        std::cout << "Введите номер правонарушения, которое хотите удалить: ";
        int crime_index;
        std::cin >> crime_index;

        if (crime_index > 0 && crime_index <= it->second.size())
        {
            it->second.erase(it->second.begin() + (crime_index - 1));  // Удалить нарушение
            if (it->second.empty())
            {
                db.erase(it);            // Если нарушений больше нет, удалить запись об автомобиле
            }
            saveDatabase(db, filename);  // Перезаписываем обновленную базу данных
            std::cout << "Правонарушение удалено и база данных обновлена." << std::endl;
        }
        else
        {
            std::cout << "Неверный индекс. Попробуйте снова." << std::endl;
        }
    }
    else
    {
        std::cout << "Автомобиль с номером " << plate << " не найден." << std::endl;
    }
}

// Функция для отображения доступных нарушений
void displayViolations()
{
    std::cout << "Доступные правонарушения:\n";
    for (const auto& violation : VIOLATIONS)
    {
        std::cout << violation.first << ". " << violation.second << std::endl;
    }
}

// Функция для инициализации базы данных (с добавлением примеров)
void initializeDatabase(std::map<std::string, std::vector<Crime>>& db, const std::string& filename)
{
    if (!db.empty()) return;  // Проверяем, что база данных не пустая

    // Добавляем правонарушения
    db["F789KL"].push_back(Crime(11, "Ул. Кольцевая", "20:50 18.11.2024", ""));
    db["D123GH"].push_back(Crime(8, "Ул. Советская", "16:20 05.09.2024", ""));
    db["A123BC"].push_back(Crime(4, "Ул. Ленина", "12:00 11.09.2024", ""));
    db["B456CD"].push_back(Crime(2, "Ул. Пушкина", "14:30 01.08.2024", ""));
    db["C789EF"].push_back(Crime(4, "Ул. Мира", "10:00 03.01.2024", ""));
    db["F789KL"].push_back(Crime(7, "Ул. Транспортная", "21:15 20.11.2024", ""));
    db["D123GH"].push_back(Crime(12, "Ул. Лесная", "18:45 07.09.2024", ""));
    db["C789EF"].push_back(Crime(9, "Ул. Мира", "09:45 03.09.2024", ""));
    db["D123GH"].push_back(Crime(1, "Ул. Лесная", "19:10 07.09.2024", ""));
    db["E456IJ"].push_back(Crime(3, "Ул. Центральная", "11:10 10.10.2024", ""));
    db["F789KL"].push_back(Crime(6, "Ул. Транспортная", "21:30 20.11.2024", ""));

    // Сохраняем в файл
    saveDatabase(db, filename);
}

// Функция для открытия файла
void openFile(const std::string& filename)
{
#ifdef _WIN32
    system(("start " + filename).c_str());
#elif __APPLE__
    system(("open " + filename).c_str());
#elif __linux__
    system(("xdg-open " + filename).c_str());
#else
    std::cout << "Открытие файла не поддерживается на этой ОС." << std::endl;
#endif
}

int main()
{
    setlocale(LC_ALL, "");

    std::map<std::string, std::vector<Crime>> trafficDatabase;
    std::string filename = "traffic_database.txt";

    loadDatabase(trafficDatabase, filename);        // Загружаем существующую базу данных
    initializeDatabase(trafficDatabase, filename);  // Инициализируем примеры и сохраняем в файл

    int choice = 0;

    while (true)
    {
        std::cout << delimiter;
        std::cout << "Выберите действие:\n";
        std::cout << "1. Добавить правонарушение\n";
        std::cout << "2. Проверить правонарушения по номеру автомобиля\n";
        std::cout << "3. Открыть и просмотреть все сохранённые данные\n";
        std::cout << "4. Удалить правонарушение\n";
        std::cout << "5. Открыть файл с нарушениями\n";
        std::cout << "0. Сохранить данные и выйти\n";
        std::cout << "Ваш выбор: ";
        std::cin >> choice;

        if (choice == 1)
        {
            std::string plate, place, time, custom_violation;
            int violation_id;
            std::cout << "Введите номер автомобиля: ";
            std::cin >> plate;

            displayViolations();
            std::cout << "Введите ID правонарушения (1-16) или 0, чтобы ввести своё описание: ";
            std::cin >> violation_id;

            if (violation_id == 0)
            {
                std::cout << "Введите описание правонарушения: ";
                std::cin.ignore();
                std::getline(std::cin, custom_violation);
            }

            std::cout << "Введите место нарушения: ";
            std::cin.ignore();  // Сбрасываем символ новой строки после предыдущего ввода
            std::getline(std::cin, place);
            std::cout << "Введите время нарушения: ";
            std::getline(std::cin, time);

            trafficDatabase[plate].push_back(Crime(violation_id, place, time, custom_violation));
            saveDatabase(trafficDatabase, filename);
            std::cout << "Данные добавлены и сохранены!" << std::endl;
        }
        else if (choice == 2)
        {
            std::string searchPlate;
            std::cout << "Введите номер автомобиля для поиска: ";
            std::cin >> searchPlate;

            auto it = trafficDatabase.find(searchPlate);
            if (it != trafficDatabase.end())
            {
                std::cout << "Автомобиль с номером " << searchPlate << " имеет следующие правонарушения:" << std::endl;
                for (const auto& crime : it->second)
                {
                    std::cout << std::setw(5) << crime << std::endl;
                }
            }
            else
            {
                std::cout << "Автомобиль с номером " << searchPlate << " не найден." << std::endl;
            }
        }
        else if (choice == 3)
        {
            std::ifstream file(filename);
            if (!file.is_open())
            {
                std::cout << "Не удалось открыть файл для чтения." << std::endl;
                continue;
            }

            std::string line;
            while (std::getline(file, line))
            {
                std::cout << line << std::endl;
            }

            file.close();
        }
        else if (choice == 4)
        {
            std::string plate;
            std::cout << "Введите номер автомобиля, для которого нужно удалить правонарушение: ";
            std::cin >> plate;

            removeViolation(trafficDatabase, plate, filename);
        }
        else if (choice == 5)
        {
            openFile(filename);
        }
        else if (choice == 0)
        {
            saveDatabase(trafficDatabase, filename);
            std::cout << "Данные сохранены. Выход из программы." << std::endl;
            break;
        }
        else
        {
            std::cout << "Неверный выбор. Попробуйте снова." << std::endl;
        }
    }
}