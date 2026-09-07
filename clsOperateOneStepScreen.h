#pragma once
#include "clsScreen.h"
#include "clsElevatorSystem.h"

class clsOperateOneStepScreen : protected clsScreen
{
	
public:
	static void OneStepScreen(bool DoAllSteps = false)
	{
		if (!DoAllSteps)
		{
			system("cls");

			_DrawScreenHeader("Smart Multi-Elevator System");
			std::cout << "\n\n";
			std::cout << "\n\t\t\t\t\t ______________________________\n";
			std::cout << "\n\t\t\t\t\t      Doing One Step.";
			std::cout << "\n\t\t\t\t\t ______________________________\n";
		}
		TheDispatcher.CheckPendingRequests();
		if (clsElevatorSystem::IsThereAnyRequest())
		{
			clsElevatorSystem::AttachNextStepStatusToElevator();
			clsElevatorSystem::DoNextStep();

			if (!DoAllSteps)
			{
				std::cout << "\n\t\t\t\t\t return to see the changes.....";
			}
		}
		else
		{
			if (!DoAllSteps)
			{
				std::cout << "\n\t\t\t\t\t There are not any requests yet!";
			}
		}
		
		if (!DoAllSteps)
		{
			std::cout << "\n\t\t\t\t\t Enter to return to the Main screen.....";
			system("pause > 0");
		}
		
	}
};

