#pragma once
#include "clsScreen.h"
#include "clsOperateOneStepScreen.h"

class clsOperateUntilTheEnd : protected clsScreen
{
public:
	static void OperateUntilTheEndScreen()
	{
		while (1)
		{
			system("cls");
			_DrawScreenHeader("Smart Multi-Elevator System");
			std::cout << "\n\n";
			std::cout << "\n\t\t\t\t\t ______________________________\n";
			std::cout << "\n\t\t\t\t\t      Doing All Steps.";
			std::cout << "\n\t\t\t\t\t ______________________________\n";
			if (clsElevatorSystem::IsThereAnyRequest())
			{
				clsOperateOneStepScreen::OneStepScreen(true);
			}
			else
			{
				std::cout << "\n\t\t\t\t\t All Requests Are Done!";
				std::cout << "\n\t\t\t\t\t Enter to return to the Main screen.....";
				system("pause > 0");
				return;
			}

			std::cout << "\n\t\t\t\t\t Enter to See the next flow.....";
			system("pause > 0");
		}
	}
};

