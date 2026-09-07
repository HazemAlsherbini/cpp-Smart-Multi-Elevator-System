#pragma once
#include <vector>
#include <cmath>
#include "clsRequest.h"

const short MAXIMUM_CAPACITY = 5;
class clsElevator
{
public:
	enum enState { Idle = 0, MovingUP = 1, MovingDOWN = 2 };

private:
	std::string _ElevatorName = "";
	short _ElevatorCurrentFloor = 0;
	enState _ElevatorCurrentState = Idle;
	enState _ElevatorPreviousState = Idle;
	std::vector<clsRequest> _Requests;
	std::string _ElevatorStateSymbol[3] = { "-","^","v" };
	bool _ReadyToMoveNextStep = false;
	short _Passengers = 0;

public:
	clsElevator()
	{
	}

	clsElevator(std::string ElevatorName , short ElevatorCurrentFloor)
	{
		_ElevatorName = ElevatorName;
		_ElevatorCurrentFloor = ElevatorCurrentFloor;
		_ElevatorCurrentState = enState::Idle;
	}

	std::vector<clsRequest>& ElevatorRequests()
	{
		return _Requests;
	}

	void setReadyToMove_value(bool PickUP)
	{
		_ReadyToMoveNextStep = PickUP;
	}
	bool ReadyToMove_value()
	{
		return _ReadyToMoveNextStep;
	}
	__declspec(property(get = ReadyToMove_value, put = setReadyToMove_value)) bool ReadyToMove;

	std::string ElevatorName()
	{
		return _ElevatorName;
	}

	std::string ElevatorStateSymbol()
	{
		return _ElevatorStateSymbol[_ElevatorCurrentState];
	}

	short ElevatorFloor() 
	{
		return _ElevatorCurrentFloor;
	}

	short NumberOfRequests()
	{
		return _Requests.size();
	}

	void SetCurrentState(enState State)
	{
		_ElevatorCurrentState = State;
	}
	enState GetElevatorCurrentState()  
	{
		return _ElevatorCurrentState;
	}
	__declspec(property(get = GetElevatorCurrentState, put = SetCurrentState)) enState ElevatorCurrentState;

	void SetPreviousState(enState State)
	{
		_ElevatorPreviousState = State;
	}
	enState GetElevatorPreviousState()  
	{
		return _ElevatorPreviousState;
	}
	__declspec(property(get = GetElevatorPreviousState, put = SetPreviousState)) enState ElevatorPreviousState;

	short Passengers()
	{
		return _Passengers;
	}

	void PickUP_Passengers()
	{
		_Passengers++;
	}

	void Drop_Passengers()
	{
		_Passengers--;
	}

	void MoveUp()
	{
		_ElevatorCurrentFloor++;
	}

	void MoveDown()
	{
		_ElevatorCurrentFloor--;

	}

	void AddRequest(clsRequest& Request)
	{
		_Requests.push_back(Request);
	}

	bool HasRequest()
	{
		return !_Requests.empty();
	}

	clsRequest TheClosestRequest()
	{
		short Distance = 20;
		clsRequest TheClosestRequest;
		short Difference = -1;

		for (clsRequest& Request : _Requests)
		{
			if (Request.ReachedPickUpFloor)
			{
				Difference = abs(_ElevatorCurrentFloor - Request.DestinationFloor());
				if (Difference < Distance)
				{
					Distance = Difference;
					TheClosestRequest = Request;
				}
			}
			else
			{
				Difference = abs(_ElevatorCurrentFloor - Request.CurrentFloor());
				if (Difference < Distance)
				{
					Distance = Difference;
					TheClosestRequest = Request;
				}
			}
			
		}

		return TheClosestRequest;
	}

	bool IsElevatorAboveTheFloor(short RequestFloor)
	{
		return _ElevatorCurrentFloor > RequestFloor;
	}

	bool IsElevatorBelowTheFloor(short RequestFloor)
	{
		return _ElevatorCurrentFloor < RequestFloor;
	}

	bool IsElevatorInTheSameFloor(short RequestFloor)
	{
		return _ElevatorCurrentFloor == RequestFloor;
	}

	bool IsElevatorHasEnoughRequests()
	{
		return _Requests.size() >= MAXIMUM_CAPACITY;
	}

	bool IsIdle()
	{
		return _ElevatorCurrentState == enState::Idle;
	}

	bool IsMovingUP()
	{
		return _ElevatorCurrentState == enState::MovingUP;
	}

	bool IsMovingDOWN()
	{
		return _ElevatorCurrentState == enState::MovingDOWN;
	}
	
	bool AreThereRequestsAbove()
	{
		for (clsRequest& Request : _Requests)
		{
			if (  ( (Request.CurrentFloor()     > _ElevatorCurrentFloor) && (!Request.ReachedPickUpFloor))
			   || ( (Request.DestinationFloor() > _ElevatorCurrentFloor) && (Request.ReachedPickUpFloor) ))
			{
				return true;
			}
		}
		return false;
	}

	bool AreThereRequestsBelow()
	{
		for (clsRequest& Request : _Requests)
		{
			if (   ( (Request.CurrentFloor()     < _ElevatorCurrentFloor) && (!Request.ReachedPickUpFloor))
				|| ( (Request.DestinationFloor() < _ElevatorCurrentFloor) && (Request.ReachedPickUpFloor)))
			{
				return true;
			}
		}
		return false;
	}
};

