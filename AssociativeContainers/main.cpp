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

    // Используем std::map для хранения номера автомобиля и списка правонарушений
    std::map<string, vector<string>> trafficDatabase;
    // Добавляем квитанции (если номер автомобиля новый, создаётся новый узел)
    auto addViolation = [](std::map<string, vector<string>>& db, const string& plate, const string& violation) {
        // Если номер автомобиля уже есть в базе, добавляем правонарушение к существующему списку
        if (db.find(plate) != db.end())
        {
            db[plate].push_back(violation);
        }
        else
        {
            // Если номера нет, создаём новый узел с этим номером и добавляем правонарушение
            db[plate] = vector<string>{ violation };
        }
};
    addViolation(trafficDatabase, "А123ВС77", "Превышение скорости");
    addViolation(trafficDatabase, "А123ВС77", "Неправильная парковка");
    addViolation(trafficDatabase, "Х987УЗ99", "Проезд на красный свет");
    addViolation(trafficDatabase, "М456ЛМ50", "Отсутствие ремня безопасности");
    addViolation(trafficDatabase, "Р111КХ23", "Разговор по телефону за рулём");
    addViolation(trafficDatabase, "Р111КХ23", "Превышение скорости");
    addViolation(trafficDatabase, "Д222ЕФ77", "Нарушение правил парковки");
    addViolation(trafficDatabase, "Г333ИЙ33", "Проезд на красный свет");
    addViolation(trafficDatabase, "Г333ИЙ33", "Неправильная парковка");
    addViolation(trafficDatabase, "Г333ИЙ33", "Отсутствие страховки");
    addViolation(trafficDatabase, "Й444КЛ77", "Превышение скорости");
    addViolation(trafficDatabase, "Й444КЛ77", "Разговор по телефону за рулём");
    addViolation(trafficDatabase, "М555НО99", "Нарушение правил обгона");
    addViolation(trafficDatabase, "К666РС77", "Отсутствие ремня безопасности");
    addViolation(trafficDatabase, "К666РС77", "Превышение скорости");
    addViolation(trafficDatabase, "Т777УВ77", "Проезд на запрещающий сигнал светофора");
    addViolation(trafficDatabase, "Т777УВ77", "Превышение скорости");
    // Вывод всех автомобилей и их нарушений
    cout << delimiter << "Вывод всех автомобилей и их правонарушений:" << endl;
    for (const auto& entry : trafficDatabase)
    {
        cout << "Автомобиль с номером: " << entry.first << endl;
        for (const auto& violation : entry.second)
        {
            cout << tab << "Нарушение: " << violation << endl;
        }
    }
    // Поиск и вывод информации по конкретным автомобилям
    cout << delimiter << "Результаты поиска:" << endl;

    string platesToSearch[] = { "А123ВС77", "М456ЛМ50", "Р678КХ23", "Т777УВ77", "Д222ЕФ77", "Д222ЕФ79" };

    for (const auto& plate : platesToSearch)
    {
        auto it = trafficDatabase.find(plate);
        if (it != trafficDatabase.end())
        {
            cout << "Автомобиль с номером " << plate << " имеет следующие правонарушения:" << endl;
            for (const auto& violation : it->second)
            {
                cout << "- " << violation << endl;
            }
        }
        else
        {
            cout << "Автомобиль с номером " << plate << " не найден." << endl;
        }
    }

    return 0;
}