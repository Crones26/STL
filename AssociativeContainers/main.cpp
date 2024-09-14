#include<iostream>
#include<map>
#include<vector>
#include<string>

using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n-------------------------------------\n"

void main()
{
    setlocale(LC_ALL, "");

    // ���������� std::map ��� �������� ������ ���������� � ������ ��������������
    std::map<std::string, std::vector<std::string>> trafficDatabase;
    // ��������� ��������� (���� ����� ���������� �����, �������� ����� ����)
    auto addViolation = [](std::map<std::string, std::vector<std::string>>& db, const std::string& plate, const std::string& violation)
        {
            // ���� ����� ���������� ��� ���� � ����, ��������� �������������� � ������������� ������
            if (db.find(plate) != db.end())
            {
                db[plate].push_back(violation);
            }
            else
            {
                // ���� ������ ���, ������ ����� ���� � ���� ������� � ��������� ��������������
                db[plate] = std::vector<std::string>{ violation };
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
    std::cout << delimiter << "����� ���� ����������� � �� ��������������:" << std::endl;
    for (const auto& entry : trafficDatabase)
    {
        std::cout << "���������� � �������: " << entry.first << std::endl;
        for (const auto& violation : entry.second)
        {
            std::cout << tab << "���������: " << violation << std::endl;
        }
    }

    // ����� � ����� ���������� �� ���������� �����������
    std::cout << delimiter << "���������� ������:" << std::endl;

    std::string platesToSearch[] = { "�123��77", "�456��50", "�678��23", "�777��77", "�222��77", "�222��79" };

    for (const auto& plate : platesToSearch)
    {
        auto it = trafficDatabase.find(plate);
        if (it != trafficDatabase.end())
        {
            std::cout << "���������� � ������� " << plate << " ����� ��������� ��������������:" << std::endl;
            for (const auto& violation : it->second)
            {
                std::cout << "- " << violation << std::endl;
            }
        }
        else
        {
            std::cout << "���������� � ������� " << plate << " �� ������." << std::endl;
        }
    }

}