#include<iostream>
#include<map>
#include<vector>
#include<iostream>
#include<map>
#include<vector>
#include<string>
#include<fstream>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::ofstream;
using std::ifstream;

#define tab "\t"
#define delimiter "\n-------------------------------------\n"

// ������� ��� ���������� ������ �������������� � ����
void saveViolationToFile(const string& plate, const string& violation) {
    ofstream outfile("violations.txt", std::ios::app);
    if (outfile.is_open()) {
        outfile << "addViolation(trafficDatabase, \"" << plate << "\", \"" << violation << "\");\n";
        outfile.close();
    }
    else {
        cout << "������ �������� ����� ��� ������." << endl;
    }
}
// ������� ��� �������� ��������� �� �����
void loadViolationsFromFile(std::map<string, vector<string>>& trafficDatabase) {
    ifstream infile("violations.txt");
    if (infile.is_open()) {
        string plate, violation, line;
        while (getline(infile, line)) {
            size_t pos1 = line.find("\"");
            size_t pos2 = line.find("\"", pos1 + 1);
            plate = line.substr(pos1 + 1, pos2 - pos1 - 1);
            pos1 = line.find("\"", pos2 + 1);
            pos2 = line.find("\"", pos1 + 1);
            violation = line.substr(pos1 + 1, pos2 - pos1 - 1);
            trafficDatabase[plate].push_back(violation);
        }
        infile.close();
    }
    else {
        // ������ ���� � ���������� �������, ���� ��� ���
        ofstream outfile("violations.txt");
        if (outfile.is_open()) 
        {
            outfile << "addViolation(trafficDatabase, \"�123��77\", \"���������� ��������\");\n";
            outfile << "addViolation(trafficDatabase, \"�123��77\", \"������������ ��������\");\n";
            outfile << "addViolation(trafficDatabase, \"�987��99\", \"������ �� ������� ����\");\n";
            outfile << "addViolation(trafficDatabase, \"�456��50\", \"���������� ����� ������������\");\n";
            outfile << "addViolation(trafficDatabase, \"�111��23\", \"�������� �� �������� �� ����\");\n";
            outfile << "addViolation(trafficDatabase, \"�111��23\", \"���������� ��������\");\n";
            outfile << "addViolation(trafficDatabase, \"�222��77\", \"��������� ������ ��������\");\n";
            outfile << "addViolation(trafficDatabase, \"�333��33\", \"������ �� ������� ����\");\n";
            outfile << "addViolation(trafficDatabase, \"�333��33\", \"������������ ��������\");\n";
            outfile << "addViolation(trafficDatabase, \"�333��33\", \"���������� ���������\");\n";
            outfile << "addViolation(trafficDatabase, \"�444��77\", \"���������� ��������\");\n";
            outfile << "addViolation(trafficDatabase, \"�444��77\", \"�������� �� �������� �� ����\");\n";
            outfile << "addViolation(trafficDatabase, \"�555��99\", \"��������� ������ ������\");\n";
            outfile << "addViolation(trafficDatabase, \"�666��77\", \"���������� ����� ������������\");\n";
            outfile << "addViolation(trafficDatabase, \"�666��77\", \"���������� ��������\");\n";
            outfile << "addViolation(trafficDatabase, \"�777��77\", \"������ �� ����������� ������ ���������\");\n";
            outfile << "addViolation(trafficDatabase, \"�777��77\", \"���������� ��������\");\n";
            outfile.close();
        }
    }
}
void main()
{
    setlocale(LC_ALL, "Russian");

    // ���������� std::map ��� �������� ������ ���������� � ������ ��������������
    std::map<string, vector<string>> trafficDatabase;

    // ������� ��� ���������� ���������
    auto addViolation = [](std::map<string, vector<string>>& db, const string& plate, const string& violation) {
        db[plate].push_back(violation);
        };

    // ��������� ������ �� ����� ��� ������� ���������
    loadViolationsFromFile(trafficDatabase);

    // ����������� ���� ��� ����� ������ � ����������
    while (true)
    {
        string plate, violation;
        char choice;

        // ���� ������ ����������
        cout << "������� ����� ���������� (��� 'exit' ��� ������): ";
        cin >> plate;

        if (plate == "exit")
        {
            break;  // ���� ������������ ������ "exit", ��������� ��������� ����
        }

        // ��������, ���������� �� ����� � ����
        if (trafficDatabase.find(plate) != trafficDatabase.end()) {
            // ���� ����� ������, ������� ��� ������������ ��������������
            cout << "���������� � ������� " << plate << " ����� ��������� ��������������:" << endl;
            for (const auto& violation : trafficDatabase[plate]) {
                cout << "- " << violation << endl;
            }
        }
        else {
            // ���� ����� �� ������, ������ ����� ������
            cout << "���������� � ������� " << plate << " �� ������. ����� ������� ����� ������." << endl;
        }

        // ���� ������ ��������������
        cout << "������� �������������� ��� ���������� " << plate << ": ";
        cin.ignore();  // ���������� ������ ����� ������ ����� ����� ������
        getline(cin, violation);

        // ��������� ������ � ����
        addViolation(trafficDatabase, plate, violation);
        saveViolationToFile(plate, violation);  // ��������� � ����

        // ���������� ������������, ����� �� �� �������� ��� ���� ��������������
        cout << "������ �������� ��� ���� ��������������? (y/n): ";
        cin >> choice;

        if (choice == 'n' || choice == 'N')
        {
            break;  // ����� �� �����, ���� ������������ ������ 'n'
        }
    }

    // ����� ���� ����������� � �� ���������
    cout << delimiter << "����� ���� ����������� � �� ��������������:" << endl;
    for (const auto& entry : trafficDatabase)
    {
        cout << "���������� � �������: " << entry.first << endl;
        for (const auto& violation : entry.second)
        {
            cout << tab << "���������: " << violation << endl;
        }
    }

}