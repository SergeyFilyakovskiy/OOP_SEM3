#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include "Header.h"

struct TestResult {
    std::string studentName;
    std::string language;
    int score;
    std::string testDate;

   
    TestResult(const std::string& name, const std::string& lang, int s, const std::string& date)
        : studentName(name), language(lang), score(s), testDate(date) {}

    void display() const 
    {
        std::cout << "Name: " << studentName
            << ", Language: " << language
            << ", Score: " << score
            << ", Date: " << testDate << std::endl;
    }

   
    bool operator<(const TestResult& other) const 
    {
        return score < other.score;
    }
};

void addTestResultToQueue(std::queue<TestResult>& q, const TestResult& result) 
{
    q.push(result);
}

void removeTestResultFromQueue(std::queue<TestResult>& q) 
{
    if (!q.empty()) 
    {
        q.pop();
    }
    else 
    {
        std::cout << "Queue is empty!" << std::endl;
    }
}

void displayQueue(const std::queue<TestResult>& q) 
{
    std::queue<TestResult> temp = q;
    while (!temp.empty()) {
        temp.front().display();
        temp.pop();
    }
}

void addTestResultToStack(std::stack<TestResult>& s, const TestResult& result) 
{
    s.push(result);
}

void removeTestResultFromStack(std::stack<TestResult>& s)
{
    if (!s.empty()) 
    {
        s.pop();
    }
    else 
    {
        std::cout << "Stack is empty!" << std::endl;
    }
}

void displayStack(const std::stack<TestResult>& s)
{
    std::stack<TestResult> temp = s;
    while (!temp.empty()) 
    {
        temp.top().display();
        temp.pop();
    }
}

void addTestResultToPriorityQueue(std::priority_queue<TestResult>& pq, const TestResult& result) 
{
    pq.push(result);
}

void displayPriorityQueue(std::priority_queue<TestResult> pq) 
{
    while (!pq.empty()) 
    {
        pq.top().display();
        pq.pop();
    }
}


int HeadFunction_6() 
{
    std::queue<TestResult> testQueue;
    std::stack<TestResult> testStack;
    std::priority_queue<TestResult> testPQ;

    int choice;
    do 
    {
        std::cout << "\n--- Menu ---\n";
        std::cout << "1. Add to Queue\n";
        std::cout << "2. Remove from Queue\n";
        std::cout << "3. Display Queue\n";
        std::cout << "4. Add to Stack\n";
        std::cout << "5. Remove from Stack\n";
        std::cout << "6. Display Stack\n";
        std::cout << "7. Add to Priority Queue\n";
        std::cout << "8. Display Priority Queue\n";
        std::cout << "9. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1: 
        {
            std::string name, language, date;
            int score;
            std::cout << "Enter Name, Language, Score, Date: ";
            std::cin >> name >> language >> score >> date;
            addTestResultToQueue(testQueue, TestResult(name, language, score, date));
            break;
        }
        case 2:
        {
            removeTestResultFromQueue(testQueue);
            break;
        }
        case 3:
        {
            displayQueue(testQueue);
            break;
        }
        case 4:
        {
            std::string name, language, date;
            int score;
            std::cout << "Enter Name, Language, Score, Date: ";
            std::cin >> name >> language >> score >> date;
            addTestResultToStack(testStack, TestResult(name, language, score, date));
            break;
        }
        case 5:
        {
            removeTestResultFromStack(testStack);
            break;
        }
        case 6:
        {
            displayStack(testStack);
            break;
        }
        case 7: 
        {
            std::string name, language, date;
            int score;
            std::cout << "Enter Name, Language, Score, Date: ";
            std::cin >> name >> language >> score >> date;
            addTestResultToPriorityQueue(testPQ, TestResult(name, language, score, date));
            break;
        }
        case 8:
            displayPriorityQueue(testPQ);
            break;
        case 9:
            std::cout << "Exiting...\n";
            break;
        default:
            std::cout << "Invalid choice!\n";
        }
    } while (choice != 9);
     
    return 0;
}

