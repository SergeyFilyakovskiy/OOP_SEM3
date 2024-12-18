#include "Header.h"
#include <iostream>
#include <Windows.h>
#include <sstream>
 
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int choise=0;
	do
	{
		std::cout << "~~~~~~~~~~Меню~~~~~~~~~~" << std::endl;
		std::cout << "1. Лабараторная работа 1\n2. Лабараторная работа 2\n3. Лабараторная работа 3\n4. Лабараторная работа 4\n5. Лабараторная работа 5\n6. Лабараторная работа 6\n7. Выход\n"<<std::endl;
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
		choise = checkInput<int>();
		switch (choise)
		{
		case 1:
		{
			HeadFunction_1();
			break;
		}
		case 2:
		{
			HeadFunction_2();
			break;
		}
		case 3:
		{
			HeadFunction_3();
			break;
		}
		case 4:
		{
			HeadFunction_4();
			break;
		}
		case 5:
		{
			HeadFunction_5();
			break;
		}
		case 6:
		{
			HeadFunction_6();
			break;
		}
		
		default:
			break;
		}
	} while (choise<7);

	return 0;
}