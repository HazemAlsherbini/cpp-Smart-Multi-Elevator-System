#pragma once
#include <iostream>
#include <map>
#include <cmath>
#include <queue>
#include "clsElevator.h"
#include "clsRequest.h"

const short ELEVATORS_NUMBER = 3;

class clsDispatcher
{

private:
	std::map <std::string, clsElevator> _Elevators;
	std::queue <clsRequest> _PendingRequests;
	short _LastFloor = 8;
	short _FirstFloor = 0;
	clsElevator _Dumby = clsElevator("", 0);

	clsElevator::enState _GetTheDesiredElevatorDirection(clsRequest& Request)
	{
		switch (Request.GoingState())
		{
		case clsRequest::enGoingState::GoingUP:
			return clsElevator::enState::MovingUP;

		case clsRequest::enGoingState::GoingDOWN:
			return clsElevator::enState::MovingDOWN;

		default:
			return clsElevator::enState::Idle;
			break;
		}
	}

	clsElevator& _GetTheClosestElevatorInTheSameDirection(clsRequest& Request, clsElevator::enState DesiredDirection)
	{
		short ClosestDistance = 20;
		std::string TheSuitableElevatorName = "";
		short FullElevators = 0;

		for (auto& pair : _Elevators)
		{
			if (pair.second.IsElevatorHasEnoughRequests())
			{
				FullElevators++;
				continue;
			}

			short Distance = std::abs(pair.second.ElevatorFloor() - Request.CurrentFloor());

			if (Distance < ClosestDistance
				&& pair.second.ElevatorCurrentState == DesiredDirection)
			{
				ClosestDistance = Distance;
				TheSuitableElevatorName = pair.first;
			}
		}

		if (TheSuitableElevatorName == "" && FullElevators < ELEVATORS_NUMBER)
		{
			for (auto& pair : _Elevators)
			{
				if (pair.second.IsElevatorHasEnoughRequests())
				{
					continue;
				}

				short Distance = std::abs(pair.second.ElevatorFloor() - Request.CurrentFloor());

				if (Distance < ClosestDistance
					&& pair.second.ElevatorCurrentState == clsElevator::enState::Idle)
				{
					ClosestDistance = Distance;
					TheSuitableElevatorName = pair.first;
				}
			}
		}

		if (TheSuitableElevatorName == "" && FullElevators < ELEVATORS_NUMBER)
		{
			for (auto& pair : _Elevators)
			{
				if (pair.second.IsElevatorHasEnoughRequests())
				{
					continue;
				}

				short Distance = std::abs(pair.second.ElevatorFloor() - Request.CurrentFloor());

				if (Distance < ClosestDistance)
				{
					ClosestDistance = Distance;
					TheSuitableElevatorName = pair.first;
				}
			}
		}

		if (TheSuitableElevatorName == "")
		{
			return _Dumby;
		}
		else
		{
			Request.TheRequesIsAttached = true;
			return _Elevators[TheSuitableElevatorName];
		}
	}

public:
	clsDispatcher()
	{
		_Elevators["A"] = clsElevator("A", 0);
		_Elevators["B"] = clsElevator("B", 0);
		_Elevators["C"] = clsElevator("C", 0);
	}

	void AttachRequestToAnElevator(clsRequest& Request)
	{
		if (Request.GoingState() == clsRequest::enGoingState::CancelRequest)
			return;

		if (!_PendingRequests.empty() && !Request.TheRequestIsPending)
		{
			Request.TheRequestIsPending = true;
			_PendingRequests.push(Request);
			return;
		}

		clsElevator& TheSuitableElevator = _GetTheClosestElevatorInTheSameDirection(Request
			, _GetTheDesiredElevatorDirection(Request));

		if (Request.TheRequesIsAttached)
		{
			TheSuitableElevator.AddRequest(Request);
		}
		else if(!Request.TheRequestIsPending)
		{
			Request.TheRequestIsPending = true;
			_PendingRequests.push(Request);
		}
	}

	void CheckPendingRequests()
	{
		while (!_PendingRequests.empty())
		{
			clsRequest Request = _PendingRequests.front();
			AttachRequestToAnElevator(Request);
			
			if (Request.TheRequesIsAttached)
			{
				Request.TheRequestIsPending = false;
				_PendingRequests.pop();
			}
			else
			{
				break;
			}
		}
	}

	bool AreThereAnyPendingRequests()
	{
		return !_PendingRequests.empty();
	}

	std::map<std::string, clsElevator>& Elevators()
	{
		return _Elevators;
	}

	short LastFloor()
	{
		return _LastFloor;
	}

	short FirstFloor()
	{
		return _FirstFloor;
	}

	
};

