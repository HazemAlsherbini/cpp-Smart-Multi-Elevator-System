#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "clsDate.h"
using namespace std;

class clsUtil
{
public:
	enum enCharType { SmallLetter, CapitalLetter, SpecialCharacter, Digit , MixCharcters };

	static void Srand()
	{
		// Seed the random number generator with the current time.
	    // This ensures that we get a different sequence of random numbers on each run.
		srand((unsigned)time(NULL));
	}
	static int RandomNumbersInRange(int from, int to)
	{
		// rand % N = 0 to N-1
		int random = rand() % (to - from + 1) + from;
		return random;
	}
	static char GetRandomCharacter(enCharType CharType)
	{
		if (CharType == enCharType::MixCharcters)
			CharType = (enCharType)RandomNumbersInRange(0, 3);
		switch (CharType)
		{
		case enCharType::CapitalLetter:
			return char(RandomNumbersInRange(65, 90));
			break;
		case enCharType::SmallLetter:
			return char(RandomNumbersInRange(97, 122));
			break;
		case enCharType::SpecialCharacter:
			return char(RandomNumbersInRange(33, 47));
			break;
		case enCharType::Digit:
			return char(RandomNumbersInRange(48, 57));
			break;
		}

		return '\0';
	}
	static string GenerateRandomLetters(enCharType CharType , short NumberOfLetters)
	{
		string Word = "";

		for (int i = 0; i < NumberOfLetters; i++)
		{
			Word.append(1,GetRandomCharacter(CharType));
		}
		return Word;
	}
	static string GenerateKey(enCharType CharType)
	{
		string Random4Letters;
		string TheWholeKey = "";

		for (int i = 0; i < 4; i++)
		{
			Random4Letters = GenerateRandomLetters(CharType,4);
			TheWholeKey.append(Random4Letters);
			Random4Letters.clear();
			if (i < 3)
			{
				TheWholeKey.append("-");
			}
		}
		return TheWholeKey;
	}
	static void GenerateNumberOfKeys(enCharType CharType, int NumberOfKeys)
	{
		cout << "\n----------------------------------------\n";
		for (int Counter = 1; Counter <= NumberOfKeys; Counter++)
		{
			cout << "Key [" << Counter << "] : " << GenerateKey(CharType) << endl;
		}
	}

	static void Swap(int& A, int& B)
	{
		int Temp = A;
		A = B;
		B = Temp;
	}
	static void Swap(double& A, double& B)
	{
		double Temp = A;
		A = B;
		B = Temp;
	}
	static void Swap(char& A, char& B)
	{
		char Temp = A;
		A = B;
		B = Temp;
	}
	static void Swap(string& A, string& B)
	{
		string Temp = A;
		A = B;
		B = Temp;
	}
	static void Swap(bool& A, bool& B)
	{
		bool Temp = A;
		A = B;
		B = Temp;
	}
	static void Swap(clsDate& A, clsDate& B)
	{
		clsDate::SwapDates(A, B);
	}

	static void ShuffleArray(int Array[], int Length)
	{
		for (int i = 0; i < Length; i++)
		{
			int index1 = RandomNumbersInRange(0, Length - 1);
			int index2 = RandomNumbersInRange(0, Length - 1);
			Swap(Array[index1], Array[index2]);
		}
	}
	static void ShuffleArray(string Array[], int Length)
	{
		for (int i = 0; i < Length; i++)
		{
			int index1 = RandomNumbersInRange(0, Length - 1);
			int index2 = RandomNumbersInRange(0, Length - 1);
			Swap(Array[index1], Array[index2]);
		}
	}

	static void FillArrayWithRandomNumbers(int Array[], int Length, int from, int to)
	{
		for (int i = 0; i < Length; i++)
		{
			Array[i] = RandomNumbersInRange(from, to);
		}
	}
	static void FillArrayWithRandomWords(string Array[], int Length, enCharType CharType, short WordLength)
	{
		for (int i = 0; i < Length; i++)
		{
			Array[i] = GenerateRandomLetters(CharType,WordLength);
		}
	}
	static void FillArrayWithKeys(string Array[], int NumberOfKeys , enCharType CharType)
	{
		for (int i = 0; i < NumberOfKeys; i++)
		{
			Array[i] = GenerateKey(CharType);
		}
	}

	static string EncryptText(string Text, short EncryptionKey)
	{
		for (int i = 0; i < Text.length(); i++)
		{
			Text[i] = char((int)Text[i] + EncryptionKey);
		}
		return Text;
	}
	static string DecryptText(string Text, short EncryptionKey)
	{
		for (int i = 0; i < Text.length(); i++)
		{
			Text[i] = char((int)Text[i] - EncryptionKey);
		}
		return Text;
	}

	static string Tabs(short NumberOfTabs)
	{
		string Tabs = "";
		for (short i = 1; i <= NumberOfTabs; i++)
		{
			Tabs += '\t';
		}
		return Tabs;
	}
};

