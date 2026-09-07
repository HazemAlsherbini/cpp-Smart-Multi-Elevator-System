#pragma once

#include <iostream>
#include <vector>

using namespace std;

class clsString
{
private:
	string _Value;

public:
	clsString()
	{
		_Value = "";
	}
	clsString(string Value)
	{
		_Value = Value;
	}

	void setValue(string Value)
	{
		_Value = Value;
	}
	string getValue()
	{
		return _Value;
	}

	__declspec(property(get = getValue , put = setValue)) string Value;

	static void PrintFirstLetterOfEachWord(const string & Message)
	{
		bool IsFirstLetter = true;

		for (short i = 0; i < Message.length(); i++)
		{
			if (IsFirstLetter && Message[i] != ' ')
				cout << Message[i] << '\n';
			IsFirstLetter = (Message[i] == ' ' ? true : false);
		}
	}
	void PrintFirstLetterOfEachWord()
	{
		PrintFirstLetterOfEachWord(_Value);
	}

	static string UpperFirstLetterOfEachWord(string Message)
	{
		bool IsFirstLetter = true;

		for (short i = 0; i < Message.length(); i++)
		{
			if (IsFirstLetter && Message[i] != ' ')
				Message[i] = toupper(Message[i]);
			IsFirstLetter = (Message[i] == ' ' ? true : false);
		}
		return Message;
	}
    void UpperFirstLetterOfEachWord()
	{
		_Value = UpperFirstLetterOfEachWord(_Value);
	}

	static string LowerFirstLetterOfEachWord(string Message)
	{
		bool IsFirstLetter = true;

		for (short i = 0; i < Message.length(); i++)
		{
			if (IsFirstLetter && Message[i] != ' ')
				Message[i] = tolower(Message[i]);
			IsFirstLetter = (Message[i] == ' ' ? true : false);
		}
		return Message;
	}
	void LowerFirstLetterOfEachWord()
	{
		_Value = LowerFirstLetterOfEachWord(_Value);
	}

	static string UpperAllLetter(string Message)
	{
		for (short i = 0; i < Message.length(); i++)
			Message[i] = toupper(Message[i]);
		return Message;
	}
	static string LowerAllLetter(string Message)
	{
		for (short i = 0; i < Message.length(); i++)
		{
			Message[i] = tolower(Message[i]);
		}
		return Message;
	}
	void UpperAllLetter()
	{
		_Value = UpperAllLetter(_Value);
	}
	void LowerAllLetter()
	{
		_Value = LowerAllLetter(_Value);
	}

	static char InvertCharCase(char C)
	{
		return (islower(C) ? toupper(C) : tolower(C));
	}
	static string InverAllLettersCase(string Message)
	{
		for (short i = 0; i < Message.length(); i++)
			Message[i] = InvertCharCase(Message[i]);
		return Message;

	}
	void InverAllLettersCase()
	{
		_Value = InverAllLettersCase(_Value);

	}

	enum enWhatToCount { SmallLetters, CapitalLetters, All };
	static short CountLetters(string Message, enWhatToCount WhatToCount = enWhatToCount::All)
	{
		if (WhatToCount == enWhatToCount::All)
			return Message.length();

		short counter = 0;
		for (short i = 0; i < Message.length(); i++)
		{
			if (isupper(Message[i]) && WhatToCount == enWhatToCount::CapitalLetters)
				counter++;
			if (islower(Message[i]) && WhatToCount == enWhatToCount::SmallLetters)
				counter++;
		}
		return counter;
	}
	short CountLetters(enWhatToCount WhatToCount = enWhatToCount::All)
	{
		return CountLetters(_Value , WhatToCount);
	}

	static short CountLetters(string Message, char C)
	{
		short counter = 0;
		for (short i = 0; i < Message.length(); i++)
		{
			if (Message[i] == C)
				counter++;
		}
		return counter;
	}
	short CountLetters(char C)
	{
		return CountLetters(_Value, C);
	}
	static short CountSpecificLetters(string Message, char C)
	{
		short counter = 0;
		for (short i = 0; i < Message.length(); i++)
		{
			if (Message[i] == tolower(C) || Message[i] == toupper(C))
				counter++;
		}
		return counter;
	}
	short CountSpecificLetters(char C)
	{
		return CountSpecificLetters(_Value, C);
	}

	static bool IsVowel(char C)
	{
		return (tolower(C) == 'a') || (tolower(C) == 'e') || (tolower(C) == 'o') || (tolower(C) == 'u') || (tolower(C) == 'i');
	}
	static short CountVowels(string Message)
	{
		short counter = 0;
		for (short i = 0; i < Message.length(); i++)
		{
			if (IsVowel(Message[i]))
				counter++;
		}
		return counter;
	}
	short CountVowels()
	{
		return CountVowels(_Value);
	}
	static void PrintVowelLetters(string Message)
	{
		cout << "\nVowels In String Are :";
		for (short i = 0; i < Message.length(); i++)
		{
			if (IsVowel(Message[i]))
				cout << Message[i] << '\t';
		}
		cout << '\n';
	}
	void PrintVowelLetters()
	{
		PrintVowelLetters(_Value);
	}

	static void PrintEachWordInString(string Message)
	{
		short pos = 0;
		string word;
		string delim = " ";
		cout << "Each Word In This String:\n";

		while ((pos = Message.find(delim)) != std::string::npos)
		{
			word = Message.substr(0, pos);
			if (word != "")
				cout << word << '\n';
			Message.erase(0, pos + 1); // It begins from first litter and count (pos+1) letters then erase them
		}

		if (!Message.empty()) //(Message != "")
			cout << Message << '\n';

	}
	void PrintEachWordInString()
	{
		PrintEachWordInString(_Value);
	}

	static short NumberOfWordsInString(string Message)
	{
		short pos = 0;
		string delim = " ";
		short counter = 0;

		while ((pos = Message.find(delim)) != std::string::npos)
		{
			if (Message.substr(0, pos) != "")
				counter++;
			Message.erase(0, pos + 1);
		}

		if (Message != "")
			counter++;
		return counter;
	}
	short NumberOfWordsInString()
	{
		return NumberOfWordsInString(_Value);
	}

	static vector<string> Split(string Message, string Delim)
	{
		vector<string> vWords;

		string Word;
		short Position;

		while ((Position = Message.find(Delim)) != std::string::npos)
		{
			Word = Message.substr(0, Position);
			//if (Word != "")
			vWords.push_back(Word);

			Message.erase(0, Position + Delim.length());

		}

		if (Message != "")
			vWords.push_back(Message);

		return vWords;
	}
	static void PrintVectorStringElements(vector<string> Words)
	{
		cout << '\n';
		for (string& Word : Words)
			cout << Word << '\n';
	}
	static int VectorStringElementsNumber(vector<string> Words)
	{
		return Words.size();
	}
	vector<string> Split(string Delim)
	{
		return Split(_Value, Delim);
	}
	
	static string TrimLeft(string Message)
	{
		for (int i = 0; i < Message.length(); i++)
		{
			if (Message[i] != ' ')
				return Message.substr(i, Message.length() - 1);
		}
		return "";
	}
	static string TrimRight(string Message)
	{
		for (int i = Message.length() - 1; i >= 0; i--)
		{
			if (Message[i] != ' ')
				return Message.substr(0, i + 1);
		}

		return "";
	}
	static string Trim(string Message)
	{
		return TrimRight(TrimLeft(Message));
	}
	void TrimLeft()
	{
		_Value = TrimLeft(_Value);
	}
	void TrimRight()
	{
		_Value = TrimRight(_Value);
	}
	void Trim()
	{
		_Value = Trim(_Value);
	}

	static string JoinString(vector<string>& vWords, string Delim)
	{
		//vector<string>::iterator iter;
		//for (iter = vWords.begin(); iter != vWords.end(); iter++)
		//{
		//	if (iter != vWords.end()-1)
		//		Message += *iter + Delim;
		//	else
		//		Message += *iter;
		//}
		//return Message;

		string Message = "";
		if (vWords.empty())
			return Message;

		for (string& s : vWords)
			Message += s + Delim;
		return Message.substr(0, Message.length() - Delim.length());
	}
	static string JoinString(string aWords[], int Length, string Delim)
	{
		string Message = "";
		if (Length == 0)
			return Message;
		for (int i = 0; i < Length; i++)
			Message += aWords[i] + Delim;
		return Message.substr(0, Message.length() - Delim.length());
	}

	static string ReverseStringWords(string Message)
	{
		vector<string> vWords = Split(Message, " ");
		string ReversedMessage = "";



		//AbuHadhud Solution
		vector<string>::iterator iter = vWords.end();
		while (iter != vWords.begin())
		{
			iter--;
			ReversedMessage += *iter + " ";
		}



		//Iter My Modification
		//vector<string>::reverse_iterator iter; // auto iter;
		//for (iter = vWords.rbegin(); iter != vWords.rend(); iter++)
		//{
		//	ReversedMessage += *iter + " ";
		//}



		//My_Solution
		//while (!vWords.empty())
		//{
		//	ReversedMessage += vWords.back() + " ";
		//	vWords.pop_back();
		//}



		if (ReversedMessage.empty())
			return"";

		return ReversedMessage.substr(0, ReversedMessage.length() - 1);

	}
	void ReverseStringWords()
	{
		_Value = ReverseStringWords(_Value);
	}

	static string ReplaceWord(string Message, string ReplaceFrom, string ReplaceTo, bool MatchCase = true)
	{
		vector<string> vWords = Split(Message, " ");

		//First Method
		/*

		string ReplacedString = "";
		for (string& Word : vWords)
		{
			if (MatchCase)
			{
				if (Word == ReplaceFrom)
					ReplacedString += ReplaceTo + " ";
				else
					ReplacedString += Word + " ";
			}
			else
			{
				if (LowerAllLetter(Word) == LowerAllLetter(ReplaceFrom))
					ReplacedString += ReplaceTo + " ";
				else
					ReplacedString += Word + " ";
			}
		}
		return ReplacedString;
		*/

		//Second Method
		for (string& Word : vWords)
		{
			if (MatchCase)
			{
				if (Word == ReplaceFrom)
					Word = ReplaceTo;
			}
			else
			{
				if (LowerAllLetter(Word) == LowerAllLetter(ReplaceFrom))
					Word = ReplaceTo;
			}
		}
		return JoinString(vWords, " ");
	}
	void ReplaceWord(string ReplaceFrom, string ReplaceTo, bool MatchCase = true)
	{
		_Value = ReplaceWord(_Value, ReplaceFrom, ReplaceTo , MatchCase);
	}

	static string ReplaceWordUsingBuiltInFunction(string Message, string ReplaceFrom, string ReplaceTo)
	{
		int Position = Message.find(ReplaceFrom);

		while (Position != std::string::npos)
		{
			Message.replace(Position, ReplaceFrom.length(), ReplaceTo); //(Position , how many last , to)
			Position = Message.find(ReplaceFrom); // To Look For If There Is Another ReplaceFrom
		}
		return Message;
	}
	void ReplaceWordUsingBuiltInFunction(string ReplaceFrom, string ReplaceTo)
	{
		_Value = ReplaceWordUsingBuiltInFunction(_Value, ReplaceFrom, ReplaceTo);
	}

	static string RemovePunctuation(string Message)
	{
		string S = "";
		for (short i = 0; i < Message.length(); i++)
		{
			if (!ispunct(Message[i]))
				S += Message[i];
		}
		return S;
	}
	void RemovePunctuation()
	{
		_Value = RemovePunctuation(_Value);
	}


};

