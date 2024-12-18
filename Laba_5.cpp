//���������� ����������� ������ � ������������ queue, stack, priority_queue, ������� ����� �������
//������� ������� �� ���������� �������, ��������� � ������� ����(�����
//������ ��������� ���������� �� ���������� �������(����������,
//��������, ��������������, �����, ������ ������)).��� ����������
//����������� ����������, ��������, ��������������, ����� �����������
//���������� �� ����� � � ����, ����� � ���������� ���������.����������
//������� ������� ���������������� ���� ��� ������������ ����
//������������� �������.
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
            std::cout << "������� �����!\n";
        }
    }

    void removeFromStack() {
        if (!testStack.empty()) {
            testStack.pop();
        }
        else {
            std::cout << "���� ����!\n";
        }
    }

    void removeFromPriorityQueue() {
        if (!testPriorityQueue.empty()) {
            testPriorityQueue.pop();
        }
        else {
            std::cout << "Priority_queue �����!\n";
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
            std::cout << "�� ������� ������� ���� ��� ������!\n";
            return;
        }

        std::queue<TestResult> copy = testQueue;
        while (!copy.empty()) {
            const TestResult& result = copy.front();
            file << result.name << "," << result.language << "," << result.score << "\n";
            copy.pop();
        }

        file.close();
        std::cout << "������ ��������� � ���� " << filename << "\n";
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
            std::cout << "���������� ��� �������� " << name << " �� �������.\n";
        }
    }
};

int HeadFunction_5() 
{
    TestManager manager;
    int choice;

    do {
        std::cout << "\n����:\n";
        std::cout << "1. �������� ���������\n";
        std::cout << "2. ������� �� �������\n";
        std::cout << "3. ������� �� �����\n";
        std::cout << "4. ������� �� priority_queue\n";
        std::cout << "5. ������� �������\n";
        std::cout << "6. ������� ����\n";
        std::cout << "7. ������� priority_queue\n";
        std::cout << "8. ��������� � ����\n";
        std::cout << "9. ����� �� �����\n";
        std::cout << "0. �����\n";
        std::cout << "��� �����: ";
        std::cin >> choice;

        switch (choice) 
        {
        case 1: 
        {
            TestResult result;
            std::cout << "������� ���: ";
            std::cin >> result.name;
            std::cout << "������� ����: ";
            std::cin >> result.language;
            std::cout << "������� ����: ";
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
            std::cout << "������� ��� �����: ";
            std::cin >> filename;
            manager.saveToFile(filename);
            break;
        }
        case 9: {
            std::string name;
            std::cout << "������� ��� ��� ������: ";
            std::cin >> name;
            manager.searchByName(name);
            break;
        }
        case 0:
            std::cout << "�����...\n";
            break;
        default:
            std::cout << "�������� �����!\n";
        }
    } while (choice != 0);

    return 0;
}
