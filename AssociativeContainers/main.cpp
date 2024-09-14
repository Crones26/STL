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

// Функция для сохранения нового правонарушения в файл
void saveViolationToFile(const string& plate, const string& violation) {
    ofstream outfile("violations.txt", std::ios::app);
    if (outfile.is_open()) {
        outfile << "addViolation(trafficDatabase, \"" << plate << "\", \"" << violation << "\");\n";
        outfile.close();
    }
    else {
        cout << "Ошибка открытия файла для записи." << endl;
    }
}
// Функция для загрузки нарушений из файла
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
        // Создаём файл с начальными данными, если его нет
        ofstream outfile("violations.txt");
        if (outfile.is_open()) 
        {
            outfile << "addViolation(trafficDatabase, \"А123ВС77\", \"Превышение скорости\");\n";
            outfile << "addViolation(trafficDatabase, \"А123ВС77\", \"Неправильная парковка\");\n";
            outfile << "addViolation(trafficDatabase, \"Х987УЗ99\", \"Проезд на красный свет\");\n";
            outfile << "addViolation(trafficDatabase, \"М456ЛМ50\", \"Отсутствие ремня безопасности\");\n";
            outfile << "addViolation(trafficDatabase, \"Р111КХ23\", \"Разговор по телефону за рулём\");\n";
            outfile << "addViolation(trafficDatabase, \"Р111КХ23\", \"Превышение скорости\");\n";
            outfile << "addViolation(trafficDatabase, \"Д222ЕФ77\", \"Нарушение правил парковки\");\n";
            outfile << "addViolation(trafficDatabase, \"Г333ИЙ33\", \"Проезд на красный свет\");\n";
            outfile << "addViolation(trafficDatabase, \"Г333ИЙ33\", \"Неправильная парковка\");\n";
            outfile << "addViolation(trafficDatabase, \"Г333ИЙ33\", \"Отсутствие страховки\");\n";
            outfile << "addViolation(trafficDatabase, \"Й444КЛ77\", \"Превышение скорости\");\n";
            outfile << "addViolation(trafficDatabase, \"Й444КЛ77\", \"Разговор по телефону за рулём\");\n";
            outfile << "addViolation(trafficDatabase, \"М555НО99\", \"Нарушение правил обгона\");\n";
            outfile << "addViolation(trafficDatabase, \"К666РС77\", \"Отсутствие ремня безопасности\");\n";
            outfile << "addViolation(trafficDatabase, \"К666РС77\", \"Превышение скорости\");\n";
            outfile << "addViolation(trafficDatabase, \"Т777УВ77\", \"Проезд на запрещающий сигнал светофора\");\n";
            outfile << "addViolation(trafficDatabase, \"Т777УВ77\", \"Превышение скорости\");\n";
            outfile.close();
        }
    }
}
void main()
{
    setlocale(LC_ALL, "Russian");

    // Используем std::map для хранения номера автомобиля и списка правонарушений
    std::map<string, vector<string>> trafficDatabase;

    // Функция для добавления нарушений
    auto addViolation = [](std::map<string, vector<string>>& db, const string& plate, const string& violation) {
        db[plate].push_back(violation);
        };

    // Загружаем данные из файла при запуске программы
    loadViolationsFromFile(trafficDatabase);

    // Бесконечный цикл для ввода данных с клавиатуры
    while (true)
    {
        string plate, violation;
        char choice;

        // Ввод номера автомобиля
        cout << "Введите номер автомобиля (или 'exit' для выхода): ";
        cin >> plate;

        if (plate == "exit")
        {
            break;  // Если пользователь вводит "exit", программа завершает ввод
        }

        // Проверка, существует ли номер в базе
        if (trafficDatabase.find(plate) != trafficDatabase.end()) {
            // Если номер найден, выводим все существующие правонарушения
            cout << "Автомобиль с номером " << plate << " имеет следующие правонарушения:" << endl;
            for (const auto& violation : trafficDatabase[plate]) {
                cout << "- " << violation << endl;
            }
        }
        else {
            // Если номер не найден, создаём новую запись
            cout << "Автомобиль с номером " << plate << " не найден. Будет создана новая запись." << endl;
        }

        // Ввод нового правонарушения
        cout << "Введите правонарушение для автомобиля " << plate << ": ";
        cin.ignore();  // Игнорируем символ новой строки после ввода номера
        getline(cin, violation);

        // Добавляем данные в базу
        addViolation(trafficDatabase, plate, violation);
        saveViolationToFile(plate, violation);  // Сохраняем в файл

        // Спрашиваем пользователя, хочет ли он добавить ещё одно правонарушение
        cout << "Хотите добавить еще одно правонарушение? (y/n): ";
        cin >> choice;

        if (choice == 'n' || choice == 'N')
        {
            break;  // Выход из цикла, если пользователь выбрал 'n'
        }
    }

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

}