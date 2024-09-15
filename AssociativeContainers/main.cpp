#include<iostream>
#include<map>
#include<vector>
#include<string>
#include<fstream>

using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n-------------------------------------\n"

// Функция для загрузки данных из файла
void loadDatabase(std::map<std::string, std::vector<std::string>>& db, const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cout << "Не удалось открыть файл для чтения." << std::endl;
        return;
    }

    std::string plate, violation;
    while (std::getline(file, plate))
    {
        std::vector<std::string> violations;
        while (std::getline(file, violation) && violation != "---")
        {
            violations.push_back(violation);
        }
        db[plate] = violations;
    }

    file.close();
}

// Функция для сохранения данных в файл
void saveDatabase(const std::map<std::string, std::vector<std::string>>& db, const std::string& filename)
{
    std::ofstream file(filename);
    if (!file.is_open())
    {
        std::cout << "Не удалось открыть файл для записи." << std::endl;
        return;
    }
    for (const auto& entry : db)
    {
        file << entry.first << std::endl;
        for (const auto& violation : entry.second)
        {
            file << violation << std::endl;
        }
        file << "---" << std::endl; // Разделитель для каждого автомобиля
    }
    file.close();
}

// Функция для вывода всех данных
void printDatabase(const std::map<std::string, std::vector<std::string>>& db)
{
    if (db.empty())
    {
        std::cout << "База данных пуста." << std::endl;
        return;
    }
    std::cout << delimiter << "Все данные в базе нарушений:" << std::endl;
    for (const auto& entry : db)
    {
        std::cout << "Автомобиль с номером: " << entry.first << std::endl;
        for (const auto& violation : entry.second)
        {
            std::cout << tab << "Нарушение: " << violation << std::endl;
        }
    }
}

// Функция для открытия файла
void openFile(const std::string& filename) {
    // Открываем файл с использованием системной команды в зависимости от ОС
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

// Функция для удаления правонарушения по номеру автомобиля
void removeViolation(std::map<std::string, std::vector<std::string>>& db, const std::string& plate, const std::string& filename)
{
    auto it = db.find(plate);
    if (it != db.end())
    {
        std::cout << "Список правонарушений для автомобиля с номером " << plate << ":" << std::endl;
        for (size_t i = 0; i < it->second.size(); ++i)
        {
            std::cout << i + 1 << ". " << it->second[i] << std::endl;
        }

        std::cout << "Введите номер правонарушения, которое хотите удалить: ";
        size_t index;
        std::cin >> index;

        if (index > 0 && index <= it->second.size())
        {
            it->second.erase(it->second.begin() + index - 1); // Удаление выбранного нарушения
            if (it->second.empty())
            {
                db.erase(it); // Если больше нет нарушений, удаляем запись об автомобиле
            }
            saveDatabase(db, filename); // Сохраняем изменения
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

int main() 
{
    setlocale(LC_ALL, "");

    std::map<std::string, std::vector<std::string>> trafficDatabase;
    std::string filename = "traffic_database.txt";
    loadDatabase(trafficDatabase, filename);

    auto addViolation = [](std::map<std::string, std::vector<std::string>>& db, const std::string& plate, const std::string& violation, const std::string& filename)
        {
            if (db.find(plate) != db.end())
            {
                db[plate].push_back(violation);
            }
            else
            {
                db[plate] = std::vector<std::string>{ violation };
            }
            saveDatabase(db, filename); // Автосохранение после добавления
        };

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
        std::cout << "6. Сохранить данные и выйти\n";
        std::cout << "Ваш выбор: ";
        std::cin >> choice;

        if (choice == 1)
        {
            std::string plate, violation;
            std::cout << "Введите номер автомобиля: ";
            std::cin >> plate;

            std::cout << "Введите правонарушение: ";
            std::cin.ignore();
            std::getline(std::cin, violation);

            addViolation(trafficDatabase, plate, violation, filename);
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
                for (const auto& violation : it->second)
                {
                    std::cout << "- " << violation << std::endl;
                }
            }
            else
            {
                std::cout << "Автомобиль с номером " << searchPlate << " не найден." << std::endl;
            }
        }
        else if (choice == 3)
        {
            printDatabase(trafficDatabase);
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
        else if (choice == 6)
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
