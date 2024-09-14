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

// ������� ��� �������� ������ �� �����
void loadDatabase(std::map<std::string, std::vector<std::string>>& db, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cout << "�� ������� ������� ���� ��� ������." << std::endl;
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

// ������� ��� ���������� ������ � ����
void saveDatabase(const std::map<std::string, std::vector<std::string>>& db, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open())
    {
        std::cout << "�� ������� ������� ���� ��� ������." << std::endl;
        return;
    }
    for (const auto& entry : db)
    {
        file << entry.first << std::endl;
        for (const auto& violation : entry.second)
        {
            file << violation << std::endl;
        }
        file << "---" << std::endl; // ����������� ��� ������� ����������
    }
    file.close();
}

// ������� ��� ������ ���� ������
void printDatabase(const std::map<std::string, std::vector<std::string>>& db)
{
    if (db.empty())
    {
        std::cout << "���� ������ �����." << std::endl;
        return;
    }
    std::cout << delimiter << "��� ������ � ���� ���������:" << std::endl;
    for (const auto& entry : db)
    {
        std::cout << "���������� � �������: " << entry.first << std::endl;
        for (const auto& violation : entry.second)
        {
            std::cout << tab << "���������: " << violation << std::endl;
        }
    }
}

// ������� ��� �������� �����
void openFile(const std::string& filename) {
    // ��������� ���� � �������������� ��������� ������� � ����������� �� ��
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

// ������� ��� �������� �������������� �� ������ ����������
void removeViolation(std::map<std::string, std::vector<std::string>>& db, const std::string& plate, const std::string& filename) {
    auto it = db.find(plate);
    if (it != db.end())
    {
        std::cout << "������ �������������� ��� ���������� � ������� " << plate << ":" << std::endl;
        for (size_t i = 0; i < it->second.size(); ++i)
        {
            std::cout << i + 1 << ". " << it->second[i] << std::endl;
        }

        std::cout << "������� ����� ��������������, ������� ������ �������: ";
        size_t index;
        std::cin >> index;

        if (index > 0 && index <= it->second.size())
        {
            it->second.erase(it->second.begin() + index - 1); // �������� ���������� ���������
            if (it->second.empty())
            {
                db.erase(it); // ���� ������ ��� ���������, ������� ������ �� ����������
            }
            saveDatabase(db, filename); // ��������� ���������
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

int main() {
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
            saveDatabase(db, filename); // �������������� ����� ����������
        };

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
        std::cout << "6. ��������� ������ � �����\n";
        std::cout << "��� �����: ";
        std::cin >> choice;

        if (choice == 1)
        {
            std::string plate, violation;
            std::cout << "������� ����� ����������: ";
            std::cin >> plate;

            std::cout << "������� ��������������: ";
            std::cin.ignore();
            std::getline(std::cin, violation);

            addViolation(trafficDatabase, plate, violation, filename);
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
                for (const auto& violation : it->second)
                {
                    std::cout << "- " << violation << std::endl;
                }
            }
            else
            {
                std::cout << "���������� � ������� " << searchPlate << " �� ������." << std::endl;
            }
        }
        else if (choice == 3)
        {
            printDatabase(trafficDatabase);
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
        else if (choice == 6)
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
