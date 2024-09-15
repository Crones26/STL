#include <iostream>
#include <fstream>
#include <map>
#include <list>
#include <vector>
#include <string>
#include <ctime>

using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n------------------------------------------------------------------------\n"

// Map of violations
const std::map<int, std::string> VIOLATIONS = {
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

// Class representing a crime
class Crime {
    int id;
    std::string place;
    std::string time;
    std::string custom_violation;
public:
    int get_violation_id() const {
        return id;
    }
    const std::string& get_violation() const {
        return (id == 0) ? custom_violation : VIOLATIONS.at(id);
    }
    const std::string& get_place() const {
        return place;
    }
    const std::string& get_time() const {
        return time;
    }
    void set_violation_id(int id) {
        this->id = id;
    }
    void set_custom_violation(const std::string& violation) {
        this->custom_violation = violation;
    }
    void set_place(const std::string& place) {
        this->place = place;
    }
    void set_time(const std::string& time) {
        this->time = time;
    }

    // Constructors
    Crime(int violation_id, const std::string& place, const std::string& time, const std::string& custom_violation = "")
        : id(violation_id), place(place), time(time), custom_violation(custom_violation) {}

    ~Crime() {}
};

// Overload operator<< to print Crime objects
std::ostream& operator<<(std::ostream& os, const Crime& obj) {
    return os << obj.get_time() << ":\t " << obj.get_place() << " - " << obj.get_violation();
}

// Function for loading database from file
void loadDatabase(std::map<std::string, std::list<Crime>>& db, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Не удалось открыть файл для чтения." << std::endl;
        return;
    }

    std::string plate, place, time, custom_violation;
    int violation_id;
    while (file >> plate >> violation_id) {
        file.ignore();
        std::getline(file, place);
        std::getline(file, time);
        std::getline(file, custom_violation);
        db[plate].push_back(Crime(violation_id, place, time, custom_violation));
    }

    file.close();
}

// Function for saving database to file
void saveDatabase(const std::map<std::string, std::list<Crime>>& db, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Не удалось открыть файл для записи." << std::endl;
        return;
    }
    for (const auto& entry : db) {
        for (const auto& crime : entry.second) {
            file << entry.first << std::endl;
            file << crime.get_violation_id() << std::endl;
            file << crime.get_place() << std::endl;
            file << crime.get_time() << std::endl;
            file << (crime.get_violation_id() == 0 ? crime.get_violation() : "") << std::endl;  // Сохранение пользовательского нарушения, если есть
        }
    }
    file.close();
}

// Function to print all violations
void printDatabase(const std::map<std::string, std::list<Crime>>& db) {
    if (db.empty()) {
        std::cout << "База данных пуста." << std::endl;
        return;
    }
    std::cout << delimiter << "Все данные в базе нарушений:" << std::endl;
    for (const auto& entry : db) {
        std::cout << "Автомобиль с номером: " << entry.first << std::endl;
        for (const auto& crime : entry.second) {
            std::cout << tab << crime << std::endl;
        }
    }
}

// Function to delete a violation by plate number
void removeViolation(std::map<std::string, std::list<Crime>>& db, const std::string& plate, const std::string& filename) {
    auto it = db.find(plate);
    if (it != db.end()) {
        std::cout << "Список правонарушений для автомобиля с номером " << plate << ":" << std::endl;
        int index = 1;
        for (const auto& crime : it->second) {
            std::cout << index++ << ". " << crime << std::endl;
        }

        std::cout << "Введите номер правонарушения, которое хотите удалить: ";
        int crime_index;
        std::cin >> crime_index;

        if (crime_index > 0 && crime_index <= it->second.size()) {
            auto crime_it = it->second.begin();
            std::advance(crime_it, crime_index - 1);
            it->second.erase(crime_it);  // Remove violation
            if (it->second.empty()) {
                db.erase(it);  // If no violations left, remove car entry
            }
            saveDatabase(db, filename);  // Save updated database
            std::cout << "Правонарушение удалено и база данных обновлена." << std::endl;
        }
        else {
            std::cout << "Неверный индекс. Попробуйте снова." << std::endl;
        }
    }
    else {
        std::cout << "Автомобиль с номером " << plate << " не найден." << std::endl;
    }
}

// Function to open file in system
void openFile(const std::string& filename) {
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

// Function to display available violations
void displayViolations() {
    std::cout << "Доступные правонарушения:\n";
    for (const auto& violation : VIOLATIONS) {
        std::cout << violation.first << ". " << violation.second << std::endl;
    }
}

// Main function
int main() {
    setlocale(LC_ALL, "");

    std::map<std::string, std::list<Crime>> trafficDatabase;
    std::string filename = "traffic_database.txt";
    loadDatabase(trafficDatabase, filename);

    int choice = 0;

    while (true) {
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

        if (choice == 1) {
            std::string plate, place, time, custom_violation;
            int violation_id;
            std::cout << "Введите номер автомобиля: ";
            std::cin >> plate;

            // Display available violations and ask for input
            displayViolations();
            std::cout << "Введите ID правонарушения (1-16) или 0, чтобы ввести своё описание: ";
            std::cin >> violation_id;

            if (violation_id == 0) {
                std::cout << "Введите описание правонарушения: ";
                std::cin.ignore();
                std::getline(std::cin, custom_violation);
            }

            std::cout << "Введите место нарушения: ";
            std::cin.ignore();
            std::getline(std::cin, place);
            std::cout << "Введите время нарушения: ";
            std::getline(std::cin, time);

            trafficDatabase[plate].push_back(Crime(violation_id, place, time, custom_violation));
            saveDatabase(trafficDatabase, filename);
            std::cout << "Данные добавлены и сохранены!" << std::endl;
        }
        else if (choice == 2) {
            std::string searchPlate;
            std::cout << "Введите номер автомобиля для поиска: ";
            std::cin >> searchPlate;

            auto it = trafficDatabase.find(searchPlate);
            if (it != trafficDatabase.end()) {
                std::cout << "Автомобиль с номером " << searchPlate << " имеет следующие правонарушения:" << std::endl;
                for (const auto& crime : it->second) {
                    std::cout << "- " << crime << std::endl;
                }
            }
            else {
                std::cout << "Автомобиль с номером " << searchPlate << " не найден." << std::endl;
            }
        }
        else if (choice == 3) {
            printDatabase(trafficDatabase);
        }
        else if (choice == 4) {
            std::string plate;
            std::cout << "Введите номер автомобиля, для которого нужно удалить правонарушение: ";
            std::cin >> plate;

            removeViolation(trafficDatabase, plate, filename);
        }
        else if (choice == 5) {
            openFile(filename);
        }
        else if (choice == 6) {
            saveDatabase(trafficDatabase, filename);
            std::cout << "Данные сохранены. Выход из программы." << std::endl;
            break;
        }
        else {
            std::cout << "Неверный выбор. Попробуйте снова." << std::endl;
        }
    }

    return 0;
}