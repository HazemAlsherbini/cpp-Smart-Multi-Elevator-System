#pragma once
#include <iostream>
#include "clsDate.h"
#include "clsGlobal.h"

class clsScreen
{
private:

	static void _PrintElevatorsState()
	{
		std::cout << "\n\t\t\t\t\t ";
		for (auto& pair : TheDispatcher.Elevators())
		{
			std::cout << '\t' << pair.second.ElevatorStateSymbol();
		}
	}

	static void _PrintElevatorsName()
	{
		std::cout << "\n\t\t\t\t\t ";
		for (auto& pair : TheDispatcher.Elevators())
		{
			std::cout << '\t' << pair.second.ElevatorName();
		}
	}

	static void _ShowElevatorsFlow()
	{
		for (short i = TheDispatcher.LastFloor(); i >= TheDispatcher.FirstFloor(); i--)
		{
			std::cout << "\n\t\t\t\t\t" << i;
			for (auto& pair : TheDispatcher.Elevators())
			{
				std::cout << '\t';
				if (pair.second.ElevatorFloor() == i)
				{
					std::cout << "["<< pair.second.Passengers() << "]";
				}
			}
			std::cout << "\n";
		}

		_PrintElevatorsName();

		_PrintElevatorsState();
	}

protected:
	static void _DrawScreenHeader(std::string Title)
	{
		std::cout << "\n\t\t\t\t\t ______________________________\n";
		std::cout << "\n\t\t\t\t\t    " << Title;
		std::cout << "\n\t\t\t\t\t          By: Hazem Al-Sherbini";
		std::cout << "\n\t\t\t\t\t ______________________________\n";
		std::cout << "\n\t\t\t\t\t    " << clsDate::GetSystemDateAndTimeString() << endl;
		_ShowElevatorsFlow();
	}
};

