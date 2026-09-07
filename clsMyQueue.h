#pragma once
#include <iostream>
#include "clsDblLinkedList.h"

template <typename T>
class clsMyQueue
{
protected:
	clsDblLinkedList<T> _List;

public:
	void push(T Value)
	{
		_List.InsertAtEnd(Value);
	}

	void pop()
	{
		_List.DeleteFirstNode();
	}

	bool IsEmpty()
	{
		return _List.IsEmpty();
	}

	int Size()
	{
		return _List.Size();
	}

	T front()
	{
		return _List.GetItem(0);
	}

	T back()
	{
		return _List.GetItem(Size() - 1);
	}

	//void Print()
	//{
	//	_List.PrintLinkedList();
	//}

	T GetItem(int index)
	{
		return _List.GetItem(index);
	}

	void Reverse()
	{
		_List.Reverse();
	}

	void UpdateItem(int index, T value)
	{
		_List.UpdateItem(index, value);
	}

	void InsertAfter(int index, T value)
	{
		_List.InsertAfter(index, value);
	}

	void InsertAtFront(T value)
	{
		_List.InsertAtBeginning(value);
	}

	void InsertAtBack(T value)
	{
		_List.InsertAtEnd(value);
	}

	void Clear()
	{
		_List.Clear();
	}

};

