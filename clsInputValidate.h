#pragma once
#include <iostream>
#include "clsDate.h"

class clsInputValidate
{
public:

	static  char ReadingYESorNO(string ErrorMessage = "Invalid Input, Enter Again: \n")
	{
		char Choice;
		cin >> Choice;
		while (cin.fail() || ( tolower(Choice) != 'y' && tolower(Choice) != 'n' ) )
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << ErrorMessage;
			cin >> Choice;
		}
		return Choice;
	}

	static bool IsNumberBetween(int Number , int from , int to)
	{
		return (Number >= from) && (Number <= to);
	}
	static bool IsNumberBetween(double Number , double from , double to)
	{
		return (Number >= from) && (Number <= to);
	}

	static bool IsDateBetween(const clsDate& Date, const clsDate& From, const clsDate& To)
	{
		if (clsDate::IsDate1AfterDate2(Date, From)
			|| clsDate::IsDate1EqualToDate2(Date, From))
		{
			if (clsDate::IsDate1BeforeDate2(Date, To)
				|| clsDate::IsDate1EqualToDate2(Date, To))
				return true;
		}
		else if (clsDate::IsDate1BeforeDate2(Date, From)
			|| clsDate::IsDate1EqualToDate2(Date, From))
		{
			if (clsDate::IsDate1AfterDate2(Date, To)
				|| clsDate::IsDate1EqualToDate2(Date, To))
				return true;
		}
		return false;
	}

	static int ReadIntNumber(string ErrorMessage = "Invalid Number, Enter Again: \n")
	{
		int Number;
		cin >> Number;

		while (cin.fail()) // Check if (std::cin) has entered an error state
		{
			cin.clear(); // Resets the error flag back to normal -It doesn't erase the bad input; it just wakes cin back up -
			// Skips and throws away all characters left in the input buffer
			// until it hits a newline character ('\n' - created when user hits Enter)
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << ErrorMessage;
			cin >> Number;
		}
		return Number;
	}
	static int ReadIntNumberBetween(int from , int to ,string ErrorMessage)
	{
		int Number = ReadIntNumber("Invalid Number, Enter Again: \n");
		while (!IsNumberBetween(Number,from,to))
		{
			cout << ErrorMessage;
			Number = ReadIntNumber("Invalid Number, Enter Again: \n");
		}
		return Number;
	}

	static short ReadShortNumber(string ErrorMessage = "Invalid Number, Enter Again: \n")
	{
		short Number;
		cin >> Number;

		while (cin.fail()) // Check if (std::cin) has entered an error state
		{
			cin.clear(); // Resets the error flag back to normal -It doesn't erase the bad input; it just wakes cin back up -
			// Skips and throws away all characters left in the input buffer
			// until it hits a newline character ('\n' - created when user hits Enter)
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << ErrorMessage;
			cin >> Number;
		}
		return Number;
	}
	static short ReadShortNumberBetween(short from, short to, string ErrorMessage)
	{
		short Number = ReadShortNumber("Invalid Number, Enter Again: \n");
		while (!IsNumberBetween(Number, from, to))
		{
			cout << ErrorMessage;
			Number = ReadShortNumber("Invalid Number, Enter Again: \n");
		}
		return Number;
	}

	static double ReadDoubleNumber(string ErrorMessage = "Invalid Number, Enter Again: \n")
	{
		double Number;
		cin >> Number;

		while (cin.fail()) // Check if (std::cin) has entered an error state
		{
			cin.clear(); // Resets the error flag back to normal -It doesn't erase the bad input; it just wakes cin back up -
			// Skips and throws away all characters left in the input buffer
			// until it hits a newline character ('\n' - created when user hits Enter)
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << ErrorMessage;
			cin >> Number;
		}
		return Number;
	}
	static double ReadDoubleNumberBetween(double from, double to, string ErrorMessage)
	{
		double Number = ReadDoubleNumber("Invalid Number, Enter Again: \n");
		while (!IsNumberBetween(Number, from, to))
		{
			cout << ErrorMessage;
			Number = ReadDoubleNumber("Invalid Number, Enter Again: \n");
		}
		return Number;
	}

	static float ReadfloatNumber(string ErrorMessage = "Invalid Number, Enter Again: \n")
	{
		float Number;
		cin >> Number;

		while (cin.fail()) // Check if (std::cin) has entered an error state
		{
			cin.clear(); // Resets the error flag back to normal -It doesn't erase the bad input; it just wakes cin back up -
			// Skips and throws away all characters left in the input buffer
			// until it hits a newline character ('\n' - created when user hits Enter)
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << ErrorMessage;
			cin >> Number;
		}
		return Number;
	}
	static float ReadfloatNumberBetween(float from, float to, string ErrorMessage)
	{
		float Number = ReadfloatNumber("Invalid Number, Enter Again: \n");
		while (!IsNumberBetween(Number, from, to))
		{
			cout << ErrorMessage;
			Number = ReadfloatNumber("Invalid Number, Enter Again: \n");
		}
		return Number;
	}

	static string ReadString()
	{
		string S = "";

		// std::ws to extract all whitespace character
		getline(cin >> ws, S);
		return S;

	}

	static bool IsValidDate(const clsDate& Date)
	{
		return clsDate::IsDateValid(Date);
	}
};

