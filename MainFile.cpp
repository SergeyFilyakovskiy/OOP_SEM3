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
		std::cout << "~~~~~~~~~~����~~~~~~~~~~" << std::endl;
		std::cout << "1. ������������ ������ 1\n2. ������������ ������ 2\n3. ������������ ������ 3\n4. ������������ ������ 4\n5. ������������ ������ 5\n6. ������������ ������ 6\n7. �����\n"<<std::endl;
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