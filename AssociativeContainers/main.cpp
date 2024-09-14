#include<iostream>
#include<map>
#include<vector>
#include<string>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;

#define tab "\t"
#define delimiter "\n-------------------------------------\n"

int main()
{
    setlocale(LC_ALL, "");

    // ���������� std::map ��� �������� ������ ���������� � ������ ��������������
    std::map<string, vector<string>> trafficDatabase;
    // ��������� ��������� (���� ����� ���������� �����, �������� ����� ����)
    auto addViolation = [](std::map<string, vector<string>>& db, const string& plate, const string& violation) {
        // ���� ����� ���������� ��� ���� � ����, ��������� �������������� � ������������� ������
        if (db.find(plate) != db.end())
        {
            db[plate].push_back(violation);
        }
        else
        {
            // ���� ������ ���, ������ ����� ���� � ���� ������� � ��������� ��������������
            db[plate] = vector<string>{ violation };
        }
};
    addViolation(trafficDatabase, "�123��77", "���������� ��������");
    addViolation(trafficDatabase, "�123��77", "������������ ��������");
    addViolation(trafficDatabase, "�987��99", "������ �� ������� ����");
    addViolation(trafficDatabase, "�456��50", "���������� ����� ������������");
    addViolation(trafficDatabase, "�111��23", "�������� �� �������� �� ����");
    addViolation(trafficDatabase, "�111��23", "���������� ��������");
    addViolation(trafficDatabase, "�222��77", "��������� ������ ��������");
    addViolation(trafficDatabase, "�333��33", "������ �� ������� ����");
    addViolation(trafficDatabase, "�333��33", "������������ ��������");
    addViolation(trafficDatabase, "�333��33", "���������� ���������");
    addViolation(trafficDatabase, "�444��77", "���������� ��������");
    addViolation(trafficDatabase, "�444��77", "�������� �� �������� �� ����");
    addViolation(trafficDatabase, "�555��99", "��������� ������ ������");
    addViolation(trafficDatabase, "�666��77", "���������� ����� ������������");
    addViolation(trafficDatabase, "�666��77", "���������� ��������");
    addViolation(trafficDatabase, "�777��77", "������ �� ����������� ������ ���������");
    addViolation(trafficDatabase, "�777��77", "���������� ��������");
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
    // ����� � ����� ���������� �� ���������� �����������
    cout << delimiter << "���������� ������:" << endl;

    string platesToSearch[] = { "�123��77", "�456��50", "�678��23", "�777��77", "�222��77", "�222��79" };

    for (const auto& plate : platesToSearch)
    {
        auto it = trafficDatabase.find(plate);
        if (it != trafficDatabase.end())
        {
            cout << "���������� � ������� " << plate << " ����� ��������� ��������������:" << endl;
            for (const auto& violation : it->second)
            {
                cout << "- " << violation << endl;
            }
        }
        else
        {
            cout << "���������� � ������� " << plate << " �� ������." << endl;
        }
    }

    return 0;
}