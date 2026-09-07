#pragma once
#include "clsScreen.h"
#include "clsAddRequestScreen.h"
#include "clsOperateOneStepScreen.h"
#include "clsOperateUntilTheEnd.h"
#include "clsInputValidate.h"

class clsMainScreen : protected clsScreen
{
private:
	enum _enMainScreenOptions {enAddNewRequest = 1 , enOneStep = 2 , enOperateUntilTheEnd = 3};

	static void _OperateUntilTheEnd()
	{
		clsOperateUntilTheEnd::OperateUntilTheEndScreen();
	}

	static void _OperateOneStep()
	{
		clsOperateOneStepScreen::OneStepScreen();
	}

	static void _AddNewRequest()
	{
		clsAddRequestScreen::AddNewRequestScreen();
	}

	static short _ReadChoice()
	{
		cout << "\n\t\t\t\t\tEnter Your Choice[1 - 3]: ";
		short Choice;
		Choice = clsInputValidate::ReadShortNumberBetween(1, 3, "\t\t\t\tINVALID!, Please Enter Between [1-3]: ");
		return Choice;
	}

	static void _PerformChoice(_enMainScreenOptions UserChoice)
	{
		void (*FunctionsPtr[]) () = { _AddNewRequest ,_OperateOneStep , _OperateUntilTheEnd };
		FunctionsPtr[UserChoice - 1](); 
	}

public:
	static void ShowMainScreen()
	{
		while (true)
		{
			system("cls");
			_DrawScreenHeader("Smart Multi-Elevator System");
			std::cout << "\n\n";
			std::cout << "\n\t\t\t\t\t ______________________________\n";
			std::cout << "\n\t\t\t\t\t     What Do You Want To Do?";
			std::cout << "\n\t\t\t\t\t ______________________________\n";
			std::cout << "\n\t\t\t\t\t [1] Add New Request.\n";
			std::cout << "\n\t\t\t\t\t [2] Operate One Step.\n";
			std::cout << "\n\t\t\t\t\t [3] Operate Until The End.\n";
			std::cout << "\n\t\t\t\t\t ______________________________\n";
			short Choice = _ReadChoice();
			_PerformChoice( (_enMainScreenOptions) Choice);
		}
	}
};

