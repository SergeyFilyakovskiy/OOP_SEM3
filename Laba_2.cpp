//На основе разработанной иерархии классов, реализованной в
//лабораторной работе «Использование потоков ввода / вывода данных»,
//реализовать программу работы с данными, используя потоки файлового
//ввода - вывода.Реализовать функций добавления данных в файл, удаления
//данных из файла, редактирования данных в файле, просмотра данных из
//файла, поиска данных по необходимым параметрам в файле.Использовать
//функции open(), is_open(), bad(), good(), close(), eof(), fail(), перегрузить
//операторы вывода в поток << и считывания из потока >> , seekg(), seekp(),
//tellg().
#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>
#include <string>
#include <exception>
#include "Header.h"
#include <fstream>

class CustomException : public std::runtime_error
{
public:
    CustomException(const std::string& message) : std::runtime_error(message) {}
};

class InvalidBroadcastException : public std::runtime_error
{
public:
    InvalidBroadcastException(const std::string& message) : std::runtime_error(message) {}
};

class InvalidPersonException : public std::runtime_error
{
public:
    InvalidPersonException(const std::string& message) : std::runtime_error(message) {}
};

class OperationException : public std::runtime_error
{
public:
    OperationException(const std::string& message) : std::runtime_error(message) {}
};

//void customTerminate()
//{
//    std::cerr << "Custom terminate called" << std::endl;
//    std::abort();
//}

class Person
{
protected:
    std::string name;
    int age;

public:
    Person(std::string name, int age) : name(name), age(age)
    {
        if (age < 0)
        {
            throw std::invalid_argument("Age cannot be negative");
        }
    }
    std::string getName() const { return name; }
    int getAge() const { return age; }
    virtual ~Person() {}

    friend std::ostream& operator<<(std::ostream& os, const Person& person) 
    {
        os << person.name << " " << person.age;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Person& person) 
    {
        is >> person.name >> person.age;
        return is;
    }

};
class Employee : public Person
{
public:
    Employee(std::string name, int age) : Person(name, age) {}
    std::string getName() const { return name; }
    int getAge() const { return age; }
    virtual ~Employee() {}
};

class Producer : public Employee
{
public:
    Producer(std::string name, int age) : Employee(name, age) {}
    std::string getName() const { return name; }
    int getAge() const { return age; }
    ~Producer() {}
};

class Presenter : public Employee
{
public:
    Presenter(std::string name, int age) : Employee(name, age) {}
    std::string getName() const { return name; }
    int getAge() const { return age; }
    ~Presenter() {}
};

class Broadcast
{
    std::shared_ptr<Presenter> presenter;
    std::shared_ptr<Producer> producer;
    std::string title;

public:
    Broadcast(std::string title, std::shared_ptr<Presenter> presenter, std::shared_ptr<Producer> producer)
        : title(title), presenter(presenter), producer(producer) {
        if (title.empty())
        {
            throw InvalidBroadcastException("Title cannot be empty");
        }
        if (!presenter || !producer)
        {
            throw InvalidBroadcastException("Broadcast must have a presenter and a producer");
        }
    }
    std::string getTitle() const { return title; }
    std::shared_ptr<Presenter> getPresenter() const { return presenter; }
    std::shared_ptr<Producer> getProducer() const { return producer; }

    friend std::ostream& operator<<(std::ostream& os, const Broadcast& broadcast)
    {
        os << broadcast.title << "\n";
        os << *(broadcast.presenter) << "\n";
        os << *(broadcast.producer) << "\n";
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Broadcast& broadcast) 
    {
        std::string title;
        std::shared_ptr<Presenter> presenter = std::make_shared<Presenter>("", 0);
        std::shared_ptr<Producer> producer = std::make_shared<Producer>("", 0);

        is >> title;
        is >> *presenter;
        is >> *producer;

        broadcast = Broadcast(title, presenter, producer);
        return is;
    }
    ~Broadcast() {}
};

class TVChannel
{
    std::vector<std::shared_ptr<Broadcast>> broadcasts;

public:
    TVChannel() {}
    void addBroadcast(std::shared_ptr<Broadcast> broadcast)
    {
        if (!broadcast)
        {
            throw OperationException("Cannot add a null broadcast");
        }
        broadcasts.push_back(broadcast);
    }
    void display() const {
        if (broadcasts.empty()) {
            std::cout << "The TV channel has no broadcasts." << std::endl;
            return;
        }
        for (const auto& broadcast : broadcasts) {
            std::cout << "Broadcast Title: " << broadcast->getTitle() << std::endl;
            std::cout << "Presenter: " << broadcast->getPresenter()->getName()
                << ", Age: " << broadcast->getPresenter()->getAge() << std::endl;
            std::cout << "Producer: " << broadcast->getProducer()->getName()
                << ", Age: " << broadcast->getProducer()->getAge() << std::endl;
            std::cout << "-----------------------------------" << std::endl;
        }
    }
    friend std::ostream& operator<<(std::ostream& os, const TVChannel& channel) {
        for (const auto& broadcast : channel.broadcasts) {
            os << *broadcast << "\n";
        }
        return os;
    }

    friend std::istream& operator>>(std::istream& is, TVChannel& channel) {
        std::shared_ptr<Broadcast> broadcast;
        while (is) {
            broadcast = std::make_shared<Broadcast>("", nullptr, nullptr);
            is >> *broadcast;
            if (is) {
                channel.addBroadcast(broadcast);
            }
        }
        return is;
    }
    ~TVChannel() {}
};

void addToFile(const std::string& filename, const TVChannel& channel) 
{
    std::ofstream file(filename, std::ios::app);
    if (!file.is_open()) 
    {
        throw std::ios_base::failure("Failed to open file for adding data");
    }
    file.seekp(0, std::ios::end);
    file << channel;
    file.close();
}

void viewFromFile(const std::string& filename) 
{ 
    std::string buffer;
    std::ifstream file(filename);
    if (!file.is_open()) 
    {
        throw std::ios_base::failure("Failed to open file for viewing data");
    }
    while (!file.eof())
    {
       
        getline(file, buffer);
        std::cout << buffer << std::endl;
    }

    file.close();
}

void deleteFromFile(const std::string& filename) 
{
    std::ofstream file(filename, std::ios::trunc);
    if (!file.is_open()) 
    {
        throw std::ios_base::failure("Failed to open file for deleting data");
    }
    file.close();
}

void editInFile(const std::string& filename, const TVChannel& newChannel) 
{
    std::ofstream file(filename, std::ios::trunc);
    if (!file.is_open())
    {
        throw std::ios_base::failure("Failed to open file for editing data");
    }
    file << newChannel;
    file.close();
}

void searchByTitle(const std::string& filename, const std::string& title) 
{
    std::ifstream file(filename);
    if (!file.is_open()) 
    {
        throw std::ios_base::failure("Failed to open file for searching data");
    }

    TVChannel channel;
    file >> channel;

    bool found = false;
   /* for (const auto& broadcast : channel.broadcasts) 
    {
        if (broadcast->getTitle() == title) 
        {
            std::cout << *broadcast << std::endl;
            found = true;
        }
    }*/

    if (!found) 
    {
        std::cout << "Broadcast with title \"" << title << "\" not found." << std::endl;
    }

    file.close();
}


int HeadFunction_2()
{
    std::string file = "Laba_2_results.txt";
    std::vector<TVChannel> channels;
    int choise = 0;
    do
    {
        std::cout << "1. Создать телеканал\n2. Показать список работников и каналов\n3. Запись в файл\n4. Вывод содержимого файла\n5. Редактирование\n6. Удалить всё содержимое\n7. Выход\n" << std::endl;
        choise = checkInput<int>();

        switch (choise)
        {
        case 1:
        {
            int producer_age, presenter_age;
            std::string producer_name, presenter_name, channel_name;
            std::cout << "Введите имя и возраст продюсера:" << std::endl;
            std::cin >> producer_name;
            producer_age = checkInput<int>();
            std::cout << "Введите имя и возраст ведущего:" << std::endl;
            std::cin >> presenter_name;
            presenter_age = checkInput<int>();
            std::cout << "Введите название программы" << std::endl;
            std::cin >> channel_name;
            try
            {
                auto presenter = std::make_shared<Presenter>(presenter_name, presenter_age);
                auto producer = std::make_shared<Producer>(producer_name, producer_age);

                auto broadcast = std::make_shared<Broadcast>(channel_name, presenter, producer);

                TVChannel channel;

                channel.addBroadcast(broadcast);

                std::cout << "Broadcast successfully added to the channel." << std::endl;
                channels.push_back(channel);

            }
            catch (const std::exception& e)
            {
                std::cerr << "Exception: " << e.what() << std::endl;
            }
            break;
        }
        case 2:
        {
            for (int i = 0; i < channels.size(); i++)
            {
                channels[i].display();
            }
            break;
        }
        case 3:
        {
            for (int i = 0; i < channels.size(); i++)
            {
                addToFile(file, channels[i]);
            }
            break;
        }
        case 4:
        { 
            try
            {
                viewFromFile(file);
            }
            catch (const std::exception& e) 
            {
                std::cerr << "Error: " << e.what() << std::endl;
            }
            break;
        }
        case 5:
        {

            break;
        }
        case 6:
        {
            try 
            {
                deleteFromFile(file);
            }
            catch (const std::exception& e)
            {
                std::cerr << "Error: " << e.what() << std::endl;
            }
            break;
        }
        default:
            break;
        }
    } while (choise < 7);
    return 0;
}