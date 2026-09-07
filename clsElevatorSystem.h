#pragma once
#include "clsElevator.h"
#include "clsGlobal.h"


class clsElevatorSystem
{
public:
	static bool IsThereAnyRequest()
	{
		if (TheDispatcher.AreThereAnyPendingRequests())
			return true;

		for (auto& pair : TheDispatcher.Elevators())
		{
			if (pair.second.HasRequest() == true)
				return true;
		}

		return false;
	}

	static void SetNextMoveToElevator(clsElevator& Elevator)
	{
		clsElevator::enState NextStep = clsElevator::enState::Idle;

		if (Elevator.ElevatorFloor() == 8)
		{
			Elevator.ElevatorPreviousState = Elevator.ElevatorCurrentState;
			switch (Elevator.ElevatorCurrentState)
			{
			case clsElevator::enState::Idle:	    NextStep = clsElevator::enState::MovingDOWN;	 break;
			case clsElevator::enState::MovingDOWN:	NextStep = clsElevator::enState::MovingDOWN;	 break;
			case clsElevator::enState::MovingUP:	NextStep = clsElevator::enState::Idle;		     break;
			}
		}
		else if (Elevator.ElevatorFloor() == 0)
		{
			Elevator.ElevatorPreviousState = Elevator.ElevatorCurrentState;
			switch (Elevator.ElevatorCurrentState)
			{
			case clsElevator::enState::Idle:		NextStep = clsElevator::enState::MovingUP;	 break;
			case clsElevator::enState::MovingDOWN:	NextStep = clsElevator::enState::Idle;		break;
			case clsElevator::enState::MovingUP:	NextStep = clsElevator::enState::MovingUP;	break;
			}
		}
		else
		{
			if (Elevator.ElevatorCurrentState == clsElevator::enState::Idle)
			{
				if (Elevator.ElevatorPreviousState == clsElevator::enState::MovingUP)
				{
					if (Elevator.AreThereRequestsAbove())
					{
						NextStep = clsElevator::enState::MovingUP;
					}
					else
					{
						NextStep = clsElevator::enState::MovingDOWN;
					}
				}
				else if (Elevator.ElevatorPreviousState == clsElevator::enState::MovingDOWN)
				{
					if (Elevator.AreThereRequestsBelow())
					{
						NextStep = clsElevator::enState::MovingDOWN;
					}
					else
					{
						NextStep = clsElevator::enState::MovingUP;
					}
				}
				else
				{
					clsRequest TheClosestRequest = Elevator.TheClosestRequest();
					if (TheClosestRequest.GoingState() != clsRequest::enGoingState::CancelRequest)
					{
						if (TheClosestRequest.ReachedPickUpFloor)
						{
							if (Elevator.IsElevatorBelowTheFloor(TheClosestRequest.DestinationFloor()))
								NextStep = clsElevator::enState::MovingUP;
							else
								NextStep = clsElevator::enState::MovingDOWN;
						}
						else
						{
							if (Elevator.IsElevatorBelowTheFloor(TheClosestRequest.CurrentFloor()))
								NextStep = clsElevator::enState::MovingUP;
							else
								NextStep = clsElevator::enState::MovingDOWN;
						}

					}
					else
					{
						NextStep = clsElevator::enState::Idle;
					}
				}
			}
			else
			{
				NextStep = Elevator.ElevatorCurrentState;
			}
		}

		Elevator.ElevatorCurrentState = NextStep;
	}

	static void AttachNextStepStatusToElevator()
	{
		for (auto& pair : TheDispatcher.Elevators())
		{
			clsElevator& Elevator = pair.second;
			std::vector<clsRequest>& Requests = Elevator.ElevatorRequests();

			clsElevator::enState ElevatorPreviousSatate = Elevator.ElevatorCurrentState;

			if (Elevator.ReadyToMove)
			{
				SetNextMoveToElevator(Elevator);
				Elevator.ReadyToMove = false;
				continue;
			}

			std::vector<clsRequest>::iterator iter;
			bool Flag = false; // This flag to check if it is a Pick-up or Drop-off floor or not.
			iter = Requests.begin();
			while (iter != Requests.end())
			{
				if ( ( Elevator.IsElevatorInTheSameFloor( iter->CurrentFloor() ) )
					&& (iter->ReachedPickUpFloor == false) )
				{
					Flag = true;

					Elevator.ElevatorPreviousState = Elevator.ElevatorCurrentState;
					Elevator.ElevatorCurrentState = clsElevator::enState::Idle;

					Elevator.PickUP_Passengers();
					Elevator.ReadyToMove = true; // To allow elevator to mover after pick up or drop off passengers
					iter->ReachedPickUpFloor = true;
				}
				
				if ( ( Elevator.IsElevatorInTheSameFloor( iter->DestinationFloor() ) )
					&& (iter->ReachedPickUpFloor))
				{
					Flag = true;

					Elevator.ElevatorPreviousState = Elevator.ElevatorCurrentState;
					Elevator.ElevatorCurrentState = clsElevator::enState::Idle;

					Elevator.Drop_Passengers();
					iter = Requests.erase(iter);
				}
				else
				{
					iter++;
				}
			}

			if (Flag == false && Elevator.HasRequest())
			{
				SetNextMoveToElevator(Elevator);
			}

		}
	}

	static void DoNextStep()
	{
		for (auto& pair : TheDispatcher.Elevators())
		{
			clsElevator& Elevator = pair.second;

			switch (Elevator.ElevatorCurrentState)
			{
			case clsElevator::enState::Idle:
				// Don't Move
				break;
			case clsElevator::enState::MovingUP:
				// Move UP
				Elevator.MoveUp();
				break;
			case clsElevator::enState::MovingDOWN:
				// Move DOWN
				Elevator.MoveDown();
				break;
			default:
				break;
			}
		}
	}
};

