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

// ������� ��� �������� ������ �� �����
void loadDatabase(std::map<string, vector<string>>& db, const string& filename) {
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "�� ������� ������� ���� ��� ������." << endl;
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
// ������� ��� ���������� ������ � ����
void saveDatabase(const std::map<string, vector<string>>& db, const string& filename) {
    ofstream file(filename);
    if (!file.is_open())
    {
        cout << "�� ������� ������� ���� ��� ������." << endl;
        return;
    }
    for (const auto& entry : db)
    {
        file << entry.first << endl;
        for (const auto& violation : entry.second)
        {
            file << violation << endl;
        }
        file << "---" << endl; // ����������� ��� ������� ����������
    }
    file.close();
}
// ������� ��� ������ ���� ������
void printDatabase(const std::map<string, vector<string>>& db)
{
    if (db.empty())
    {
        cout << "���� ������ �����." << endl;
        return;
    }
    cout << delimiter << "��� ������ � ���� ���������:" << endl;
    for (const auto& entry : db)
    {
        cout << "���������� � �������: " << entry.first << endl;
        for (const auto& violation : entry.second)
        {
            cout << tab << "���������: " << violation << endl;
        }
    }
}
// ������� ��� �������� �����
void openFile(const string& filename) {
    // ��������� ���� � �������������� ��������� ������� � ����������� �� ��
#ifdef _WIN32
    system(("start " + filename).c_str());
#elif __APPLE__
    system(("open " + filename).c_str());
#elif __linux__
    system(("xdg-open " + filename).c_str());
#else
    cout << "�������� ����� �� �������������� �� ���� ��." << endl;
#endif
}
// ������� ��� �������� �������������� �� ������ ����������
void removeViolation(std::map<string, vector<string>>& db, const string& plate, const string& filename) {
    auto it = db.find(plate);
    if (it != db.end())
    {
        cout << "������ �������������� ��� ���������� � ������� " << plate << ":" << endl;
        for (size_t i = 0; i < it->second.size(); ++i)
        {
            cout << i + 1 << ". " << it->second[i] << endl;
        }

        cout << "������� ����� ��������������, ������� ������ �������: ";
        size_t index;
        cin >> index;

        if (index > 0 && index <= it->second.size())
        {
            it->second.erase(it->second.begin() + index - 1); // �������� ���������� ���������
            if (it->second.empty())
            {
                db.erase(it); // ���� ������ ��� ���������, ������� ������ �� ����������
            }
            saveDatabase(db, filename); // ��������� ���������
            cout << "�������������� ������� � ���� ������ ���������." << endl;
        }
        else
        {
            cout << "�������� ������. ���������� �����." << endl;
        }
    }
    else
    {
        cout << "���������� � ������� " << plate << " �� ������." << endl;
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
        saveDatabase(db, filename); // �������������� ����� ����������
        };

    int choice = 0;

    while (true)
    {
        cout << delimiter;
        cout << "�������� ��������:\n";
        cout << "1. �������� ��������������\n";
        cout << "2. ��������� �������������� �� ������ ����������\n";
        cout << "3. ������� � ����������� ��� ���������� ������\n";
        cout << "4. ������� ��������������\n";
        cout << "5. ������� ���� � �����������\n";
        cout << "6. ��������� ������ � �����\n";
        cout << "��� �����: ";
        cin >> choice;

        if (choice == 1)
        {
            string plate, violation;
            cout << "������� ����� ����������: ";
            cin >> plate;

            cout << "������� ��������������: ";
            cin.ignore();
            getline(cin, violation);

            addViolation(trafficDatabase, plate, violation, filename);
            cout << "������ ��������� � ���������!" << endl;
        }
        else if (choice == 2)
        {
            string searchPlate;
            cout << "������� ����� ���������� ��� ������: ";
            cin >> searchPlate;

            auto it = trafficDatabase.find(searchPlate);
            if (it != trafficDatabase.end())
            {
                cout << "���������� � ������� " << searchPlate << " ����� ��������� ��������������:" << endl;
                for (const auto& violation : it->second) 
                {
                    cout << "- " << violation << endl;
                }
            }
            else
            {
                cout << "���������� � ������� " << searchPlate << " �� ������." << endl;
            }
        }
        else if (choice == 3)
        {
            printDatabase(trafficDatabase);
        }
        else if (choice == 4)
        {
            string plate;
            cout << "������� ����� ����������, ��� �������� ����� ������� ��������������: ";
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
            cout << "������ ���������. ����� �� ���������." << endl;
            break;
        }
        else
        {
            cout << "�������� �����. ���������� �����." << endl;
        }
    }
}
