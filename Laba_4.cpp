#include <iostream>
#include <map>
#include <set>
#include <string>
#include <fstream>
#include "Header.h"


class TestResult {
public:
    std::string studentName;
    std::string language;
    int score;

    TestResult(const std::string& name = "", const std::string& lang = "", int scr = 0)
        : studentName(name), language(lang), score(scr) {}

    void display() const {
        std::cout << "Name: " << studentName
            << ", Language: " << language
            << ", Score: " << score << std::endl;
    }

    bool operator<(const TestResult& other) const {
        return score < other.score;
    }

    friend std::ostream& operator<<(std::ostream& os, const TestResult& result) {
        os << result.studentName << "," << result.language << "," << result.score;
        return os;
    }


    friend std::istream& operator>>(std::istream& is, TestResult& result) {
        std::getline(is, result.studentName, ',');
        std::getline(is, result.language, ',');
        is >> result.score;
        is.ignore();
        return is;
    }
};


void addToMap(std::map<std::string, TestResult>& records, const std::string& key, const TestResult& result) {
    records[key] = result;
    std::cout << "Added record with key: " << key << std::endl;
}


void displayMap(const std::map<std::string, TestResult>& records) {
    if (records.empty()) {
        std::cout << "Map is empty.\n";
        return;
    }
    for (const auto& element : records) {
        std::cout << element.first << ": " << element.second << std::endl;
    }
}


int HeadFunction_4() {
    std::map<std::string, TestResult> testResultsMap;

    int choice;
    do {
        std::cout << "\nMenu:\n";
        std::cout << "1. Add to Map\n";
        std::cout << "2. Display Map\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;


        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            std::cout << "Invalid input. Please try again.\n";
            continue;
        }


        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
        case 1: {
            std::string key, name, language;
            int score;

      
            std::cout << "Enter Key: ";
            std::getline(std::cin, key); 


            std::cout << "Enter Name: ";
            std::getline(std::cin, name); 


            std::cout << "Enter Language: ";
            std::getline(std::cin, language); 

 
            std::cout << "Enter Score: ";
            std::cin >> score;


            if (std::cin.fail()) {
                std::cin.clear();  
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                std::cout << "Invalid score input. Please try again.\n";
                continue;
            }

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            addToMap(testResultsMap, key, TestResult(name, language, score));
            break;
        }
        case 2:
            displayMap(testResultsMap);
            break;
        case 3:
            std::cout << "Exiting...\n";
            break;
        default:
            std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 3);

    return 0;
}
