//необходимо реализовать работу с контейнерами queue, stack, priority_queue, которые будут хранить
//объекты классов по предметной области, указанной в таблице ниже(класс
//должен содержать функционал по предметной области(добавление,
//удаление, редактирование, поиск, фильтр данных)).Для контейнера
//реализовать добавление, удаление, редактирование, вывод содержимого
//контейнера на экран и в файл, поиск и сортировку элементов.Необходимо
//создать удобное пользовательское меню для тестирования всех
//реализованных функций.
#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include "Header.h"

struct TestResult 
{
public:
    std::string name;
    std::string language;
    int score;

    bool operator<(const TestResult& other) const {
        return score < other.score; 
    }
};

class TestManager 
{
private:
    std::queue<TestResult> testQueue;
    std::stack<TestResult> testStack;
    std::priority_queue<TestResult> testPriorityQueue;

public:

    void addResult(const TestResult& result) {
        testQueue.push(result);
        testStack.push(result);
        testPriorityQueue.push(result);
    }


    void removeFromQueue() {
        if (!testQueue.empty()) {
            testQueue.pop();
        }
        else {
            std::cout << "Очередь пуста!\n";
        }
    }

    void removeFromStack() {
        if (!testStack.empty()) {
            testStack.pop();
        }
        else {
            std::cout << "Стек пуст!\n";
        }
    }

    void removeFromPriorityQueue() {
        if (!testPriorityQueue.empty()) {
            testPriorityQueue.pop();
        }
        else {
            std::cout << "Priority_queue пуста!\n";
        }
    }

    void displayQueue() const {
        std::queue<TestResult> copy = testQueue;
        while (!copy.empty()) {
            const TestResult& result = copy.front();
            std::cout << result.name << " (" << result.language << ") - " << result.score << "\n";
            copy.pop();
        }
    }

    void displayStack() const {
        std::stack<TestResult> copy = testStack;
        while (!copy.empty()) {
            const TestResult& result = copy.top();
            std::cout << result.name << " (" << result.language << ") - " << result.score << "\n";
            copy.pop();
        }
    }

    void displayPriorityQueue() const {
        std::priority_queue<TestResult> copy = testPriorityQueue;
        while (!copy.empty()) {
            const TestResult& result = copy.top();
            std::cout << result.name << " (" << result.language << ") - " << result.score << "\n";
            copy.pop();
        }
    }

    void saveToFile(const std::string& filename) const {
        std::ofstream file(filename);
        if (!file) {
            std::cout << "Не удалось открыть файл для записи!\n";
            return;
        }

        std::queue<TestResult> copy = testQueue;
        while (!copy.empty()) {
            const TestResult& result = copy.front();
            file << result.name << "," << result.language << "," << result.score << "\n";
            copy.pop();
        }

        file.close();
        std::cout << "Данные сохранены в файл " << filename << "\n";
    }

    void searchByName(const std::string& name) const {
        std::queue<TestResult> copy = testQueue;
        bool found = false;
        while (!copy.empty()) {
            const TestResult& result = copy.front();
            if (result.name == name) {
                std::cout << result.name << " (" << result.language << ") - " << result.score << "\n";
                found = true;
            }
            copy.pop();
        }
        if (!found) {
            std::cout << "Результаты для студента " << name << " не найдены.\n";
        }
    }
};

int HeadFunction_5() 
{
    TestManager manager;
    int choice;

    do {
        std::cout << "\nМеню:\n";
        std::cout << "1. Добавить результат\n";
        std::cout << "2. Удалить из очереди\n";
        std::cout << "3. Удалить из стека\n";
        std::cout << "4. Удалить из priority_queue\n";
        std::cout << "5. Вывести очередь\n";
        std::cout << "6. Вывести стек\n";
        std::cout << "7. Вывести priority_queue\n";
        std::cout << "8. Сохранить в файл\n";
        std::cout << "9. Поиск по имени\n";
        std::cout << "0. Выход\n";
        std::cout << "Ваш выбор: ";
        std::cin >> choice;

        switch (choice) 
        {
        case 1: 
        {
            TestResult result;
            std::cout << "Введите имя: ";
            std::cin >> result.name;
            std::cout << "Введите язык: ";
            std::cin >> result.language;
            std::cout << "Введите балл: ";
            std::cin >> result.score;
            manager.addResult(result);
            break;
        }
        case 2:
            manager.removeFromQueue();
            break;
        case 3:
            manager.removeFromStack();
            break;
        case 4:
            manager.removeFromPriorityQueue();
            break;
        case 5:
            manager.displayQueue();
            break;
        case 6:
            manager.displayStack();
            break;
        case 7:
            manager.displayPriorityQueue();
            break;
        case 8: {
            std::string filename;
            std::cout << "Введите имя файла: ";
            std::cin >> filename;
            manager.saveToFile(filename);
            break;
        }
        case 9: {
            std::string name;
            std::cout << "Введите имя для поиска: ";
            std::cin >> name;
            manager.searchByName(name);
            break;
        }
        case 0:
            std::cout << "Выход...\n";
            break;
        default:
            std::cout << "Неверный выбор!\n";
        }
    } while (choice != 0);

    return 0;
}
