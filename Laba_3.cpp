//В каждом индивидуальном задании необходимо создать контейнеры
//list, vector, array, которые будут хранить объекты классов по предметной
//области, указанной в таблице(класс должен содержать функционал по
//	предметной области(добавление, удаление, редактирование, поиск, фильтр
//		данных)).Для контейнера раеализовать
//	добавление,
//	удаление,
//	редактирование, вывод содержимого контейнера на экран и в файл, поиск и
//	сортировку элементов.Необходимо создать удобное пользовательское меню
//	для тестирования всех реализованных функций.
//	учет результатов тестирования по иностранным языкам
#include <iostream>
#include <list>
#include <vector>
#include <array>
#include <fstream>
#include <algorithm>
#include <string>

class TestResult 
{
public:
    std::string studentName;
    std::string language;
    int score;
    std::string testDate;

    TestResult(const std::string& name, const std::string& lang, int scr, const std::string& date)
        : studentName(name), language(lang), score(scr), testDate(date) {}

    void display() const 
    {
        std::cout << "Name: " << studentName
            << ", Language: " << language
            << ", Score: " << score
            << ", Date: " << testDate << std::endl;
    }
};

void addRecord(std::list<TestResult>& records, const TestResult& result) 
{
    records.push_back(result);
}

void deleteRecord(std::list<TestResult>& records, const std::string& name) 
{
    records.remove_if([&name](const TestResult& r) 
        {
        return r.studentName == name;
        });
}

void editRecord(std::list<TestResult>& records, const std::string& name, const TestResult& newResult)
{
    for (auto& record : records) 
    {
        if (record.studentName == name) 
        {
            record = newResult;
            break;
        }
    }
}

void displayRecords(const std::list<TestResult>& records) 
{
    for (const auto& record : records) 
    {
        record.display();
    }
}

void sortRecords(std::list<TestResult>& records) 
{
    records.sort([](const TestResult& a, const TestResult& b) 
        {
        return a.score > b.score; 
        });
}

void saveToFile(const std::list<TestResult>& records, const std::string& filename)
{
    std::ofstream file(filename);
    if (file.is_open()) 
    {
        for (const auto& record : records) 
        {
            file << record.studentName << ","
                << record.language << ","
                << record.score << ","
                << record.testDate << "\n";
        }
        file.close();
    }
    else 
    {
        std::cerr << "Error opening file!" << std::endl;
    }
}

void loadFromFile(std::list<TestResult>& records, const std::string& filename) 
{
    std::ifstream file(filename);
    if (file.is_open())
    {
        std::string name, language, date;
        int score;
        char delimiter;
        while (file >> name >> delimiter >> language >> delimiter >> score >> delimiter >> date) 
        {
            records.emplace_back(name, language, score, date);
        }
        file.close();
    }
    else 
    {
        std::cerr << "Error opening file!" << std::endl;
    }
}

int HeadFunction_3() 
{
    std::list<TestResult> testResults;
    int choice;
    do 
    {
        std::cout << "\nMenu:\n";
        std::cout << "1. Add Record\n";
        std::cout << "2. Delete Record\n";
        std::cout << "3. Edit Record\n";
        std::cout << "4. Display Records\n";
        std::cout << "5. Sort Records by Score\n";
        std::cout << "6. Save to File\n";
        std::cout << "7. Load from File\n";
        std::cout << "8. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) 
        {
        case 1: 
        {
            std::string name, language, date;
            int score;
            std::cout << "Enter Name: ";
            std::cin >> name;
            std::cout << "Enter Language: ";
            std::cin >> language;
            std::cout << "Enter Score: ";
            std::cin >> score;
            std::cout << "Enter Test Date: ";
            std::cin >> date;
            addRecord(testResults, TestResult(name, language, score, date));
            break;
        }
        case 2: 
        {
            std::string name;
            std::cout << "Enter Name to Delete: ";
            std::cin >> name;
            deleteRecord(testResults, name);
            break;
        }
        case 3: 
        {
            std::string name, newName, language, date;
            int score;
            std::cout << "Enter Name to Edit: ";
            std::cin >> name;
            std::cout << "Enter New Name: ";
            std::cin >> newName;
            std::cout << "Enter New Language: ";
            std::cin >> language;
            std::cout << "Enter New Score: ";
            std::cin >> score;
            std::cout << "Enter New Test Date: ";
            std::cin >> date;
            editRecord(testResults, name, TestResult(newName, language, score, date));
            break;
        }
        case 4:
            displayRecords(testResults);
            break;
        case 5:
            sortRecords(testResults);
            break;
        case 6: 
        {
            std::string filename;
            std::cout << "Enter filename to save: ";
            std::cin >> filename;
            saveToFile(testResults, filename);
            break;
        }
        case 7: 
        {
            std::string filename;
            std::cout << "Enter filename to load: ";
            std::cin >> filename;
            loadFromFile(testResults, filename);
            break;
        }
        case 8:
            std::cout << "Exiting...\n";
            break;
        default:
            std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 8);

    return 0;
}
