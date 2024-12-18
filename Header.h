#pragma once
#include <sstream>
#include <iostream>
template<typename T>
T checkInput()
{
	T val;
	while (true)
	{
		std::string input;
		std::cin >> input;

		std::stringstream ss(input);
		if (ss >> val && ss.eof())
			break;
		else
			std::cout << "Некорректный ввод! Попробуйте еще раз." << std::endl;
	}

	return val;
}
int HeadFunction_1();
int HeadFunction_2();
int HeadFunction_3();
int HeadFunction_4();
int HeadFunction_5();
int HeadFunction_6();