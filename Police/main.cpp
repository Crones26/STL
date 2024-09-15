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

// ����� ���������
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

// ���������� ��������� ������ ��� �������� Crime
std::ostream& operator<<(std::ostream& os, const Crime& obj)
{
    return os << obj.get_time() << " " << obj.get_place() << " " << obj.get_violation();
}

// ������� ��� �������� ���� ������ �� �����
void loadDatabase(std::map<std::string, std::vector<Crime>>& db, const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cout << "�� ������� ������� ���� ��� ������. ������ ����� ����: " << std::endl;
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

// ������� ��� ���������� ���� ������ � ���� � ����������� ����� ������
void saveDatabase(const std::map<std::string, std::vector<Crime>>& db, const std::string& filename)
{
    std::ofstream file(filename);         // ��������� ���� � ������ ������ (����������)
    if (!file.is_open())
    {
        std::cout << "�� ������� ������� ���� ��� ������." << std::endl;
        return;
    }

    for (const auto& entry : db)
    {
        file << delimiter;
        file << entry.first << std::endl;  // ��������� ����� ����������
        for (const auto& crime : entry.second)
        {
            file << crime.get_place() << std::endl;         // ��������� ����� ���������
            file << crime.get_time() << std::endl;          // ��������� ����� ���������
            file << crime.get_violation() << std::endl;     // ��������� ��������� �������� �������������� (���� custom)
        }
    }

    file.close();
}

// ������� ��� �������� ��������� �� ������ ����������
void removeViolation(std::map<std::string, std::vector<Crime>>& db, const std::string& plate, const std::string& filename)
{
    auto it = db.find(plate);
    if (it != db.end())
    {
        std::cout << "������ �������������� ��� ���������� � ������� " << plate << ":" << std::endl;
        int index = 1;
        for (const auto& crime : it->second)
        {
            // ������� �������������� � ���� ������
            std::cout << index++ << ". " << crime << std::endl;
        }

        std::cout << "������� ����� ��������������, ������� ������ �������: ";
        int crime_index;
        std::cin >> crime_index;

        if (crime_index > 0 && crime_index <= it->second.size())
        {
            it->second.erase(it->second.begin() + (crime_index - 1));  // ������� ���������
            if (it->second.empty())
            {
                db.erase(it);            // ���� ��������� ������ ���, ������� ������ �� ����������
            }
            saveDatabase(db, filename);  // �������������� ����������� ���� ������
            std::cout << "�������������� ������� � ���� ������ ���������." << std::endl;
        }
        else
        {
            std::cout << "�������� ������. ���������� �����." << std::endl;
        }
    }
    else
    {
        std::cout << "���������� � ������� " << plate << " �� ������." << std::endl;
    }
}

// ������� ��� ����������� ��������� ���������
void displayViolations()
{
    std::cout << "��������� ��������������:\n";
    for (const auto& violation : VIOLATIONS)
    {
        std::cout << violation.first << ". " << violation.second << std::endl;
    }
}

// ������� ��� ������������� ���� ������ (� ����������� ��������)
void initializeDatabase(std::map<std::string, std::vector<Crime>>& db, const std::string& filename)
{
    if (!db.empty()) return;  // ���������, ��� ���� ������ �� ������

    // ��������� ��������������
    db["F789KL"].push_back(Crime(11, "��. ���������", "20:50 18.11.2024", ""));
    db["D123GH"].push_back(Crime(8, "��. ���������", "16:20 05.09.2024", ""));
    db["A123BC"].push_back(Crime(4, "��. ������", "12:00 11.09.2024", ""));
    db["B456CD"].push_back(Crime(2, "��. �������", "14:30 01.08.2024", ""));
    db["C789EF"].push_back(Crime(4, "��. ����", "10:00 03.01.2024", ""));
    db["F789KL"].push_back(Crime(7, "��. ������������", "21:15 20.11.2024", ""));
    db["D123GH"].push_back(Crime(12, "��. ������", "18:45 07.09.2024", ""));
    db["C789EF"].push_back(Crime(9, "��. ����", "09:45 03.09.2024", ""));
    db["D123GH"].push_back(Crime(1, "��. ������", "19:10 07.09.2024", ""));
    db["E456IJ"].push_back(Crime(3, "��. �����������", "11:10 10.10.2024", ""));
    db["F789KL"].push_back(Crime(6, "��. ������������", "21:30 20.11.2024", ""));

    // ��������� � ����
    saveDatabase(db, filename);
}

// ������� ��� �������� �����
void openFile(const std::string& filename)
{
#ifdef _WIN32
    system(("start " + filename).c_str());
#elif __APPLE__
    system(("open " + filename).c_str());
#elif __linux__
    system(("xdg-open " + filename).c_str());
#else
    std::cout << "�������� ����� �� �������������� �� ���� ��." << std::endl;
#endif
}

int main()
{
    setlocale(LC_ALL, "");

    std::map<std::string, std::vector<Crime>> trafficDatabase;
    std::string filename = "traffic_database.txt";

    loadDatabase(trafficDatabase, filename);        // ��������� ������������ ���� ������
    initializeDatabase(trafficDatabase, filename);  // �������������� ������� � ��������� � ����

    int choice = 0;

    while (true)
    {
        std::cout << delimiter;
        std::cout << "�������� ��������:\n";
        std::cout << "1. �������� ��������������\n";
        std::cout << "2. ��������� �������������� �� ������ ����������\n";
        std::cout << "3. ������� � ����������� ��� ���������� ������\n";
        std::cout << "4. ������� ��������������\n";
        std::cout << "5. ������� ���� � �����������\n";
        std::cout << "0. ��������� ������ � �����\n";
        std::cout << "��� �����: ";
        std::cin >> choice;

        if (choice == 1)
        {
            std::string plate, place, time, custom_violation;
            int violation_id;
            std::cout << "������� ����� ����������: ";
            std::cin >> plate;

            displayViolations();
            std::cout << "������� ID �������������� (1-16) ��� 0, ����� ������ ��� ��������: ";
            std::cin >> violation_id;

            if (violation_id == 0)
            {
                std::cout << "������� �������� ��������������: ";
                std::cin.ignore();
                std::getline(std::cin, custom_violation);
            }

            std::cout << "������� ����� ���������: ";
            std::cin.ignore();  // ���������� ������ ����� ������ ����� ����������� �����
            std::getline(std::cin, place);
            std::cout << "������� ����� ���������: ";
            std::getline(std::cin, time);

            trafficDatabase[plate].push_back(Crime(violation_id, place, time, custom_violation));
            saveDatabase(trafficDatabase, filename);
            std::cout << "������ ��������� � ���������!" << std::endl;
        }
        else if (choice == 2)
        {
            std::string searchPlate;
            std::cout << "������� ����� ���������� ��� ������: ";
            std::cin >> searchPlate;

            auto it = trafficDatabase.find(searchPlate);
            if (it != trafficDatabase.end())
            {
                std::cout << "���������� � ������� " << searchPlate << " ����� ��������� ��������������:" << std::endl;
                for (const auto& crime : it->second)
                {
                    std::cout << std::setw(5) << crime << std::endl;
                }
            }
            else
            {
                std::cout << "���������� � ������� " << searchPlate << " �� ������." << std::endl;
            }
        }
        else if (choice == 3)
        {
            std::ifstream file(filename);
            if (!file.is_open())
            {
                std::cout << "�� ������� ������� ���� ��� ������." << std::endl;
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
            std::cout << "������� ����� ����������, ��� �������� ����� ������� ��������������: ";
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
            std::cout << "������ ���������. ����� �� ���������." << std::endl;
            break;
        }
        else
        {
            std::cout << "�������� �����. ���������� �����." << std::endl;
        }
    }
}