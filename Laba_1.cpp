//27. Разработать набор классов(минимум 5 классов, связи между
//	классами : агрегация, композиция, наследование) по предметной области
//	«Телевизионный канал».Функционал программы должен позволить
//	собрать данные команду для проведения телепередач.
#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>
#include <string>
#include <exception>
#include "Header.h"

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

void customTerminate()
{
    std::cerr << "Custom terminate called" << std::endl;
    std::abort();
}

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
    ~TVChannel() {}
};


int HeadFunction_1()
{
    std::vector<TVChannel> channels;
    int choise = 0;
    do
    {
        std::cout << "1. Создать телеканал\n2. Показать список работников и каналов\n3. Выход" << std::endl;
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
            for (int i = 0; i<channels.size(); i++)
            {
                channels[i].display();
            }
            break;
        }
            default:
                 break;
        }
    } while (choise<4);
	return 0;
}