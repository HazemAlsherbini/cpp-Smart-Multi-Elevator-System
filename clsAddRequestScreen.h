#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsRequest.h"

class clsAddRequestScreen : protected clsScreen
{
private:
	static short _ReadFloorNumber()
	{
		short Choice;
		Choice = clsInputValidate::ReadShortNumberBetween(0, 8, "\t\t\t\tINVALID!, Please Enter Between [0-8]: ");
		return Choice;
	}

	static bool _SendTheRequest(short CurrentFloor, short DestinationFloor)
	{
		clsRequest Request(CurrentFloor, DestinationFloor);
		TheDispatcher.AttachRequestToAnElevator(Request);

		if (Request.TheRequesIsAttached)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

public:
	static void AddNewRequestScreen()
	{
		
		system("cls");
		_DrawScreenHeader("Smart Multi-Elevator System");
		std::cout << "\n\n";
		std::cout << "\n\t\t\t\t\t ______________________________\n";
		std::cout << "\n\t\t\t\t\t      Add New Request.";
		std::cout << "\n\t\t\t\t\t ______________________________\n";
		std::cout << "\n\t\t\t\t\t Please, Enter the current floor number: ";
		short CurrentFloor = _ReadFloorNumber();
		std::cout << "\n\t\t\t\t\t Please, Enter the destination floor number:";
		short DestinationFloor = _ReadFloorNumber();
		std::cout << "\n\t\t\t\t\t ______________________________\n";
		if (_SendTheRequest(CurrentFloor, DestinationFloor))
		{
			std::cout << "\n\t\t\t\t\t The request has been sent successfully :)";
		}
		else
		{
			std::cout << "\n\t\t\t\t\t All elevators are busy now, please wait :)";
		}
		std::cout << "\n\t\t\t\t\t Enter to return to the Main screen.....";
		system("pause > 0");
	}
};

