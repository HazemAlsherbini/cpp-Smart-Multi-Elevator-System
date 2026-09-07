#pragma once

class clsRequest
{
public:
	enum enGoingState { GoingUP, GoingDOWN , CancelRequest };

private:
	short _CurrentFloor;
	short _DestinationFloor;
	enGoingState _GoingState;
	bool _ElevatorReachedPickUpFloor = false;
	bool _TheRequestIsAttachedToAnElevator = false;
	bool _TheRequestIsPending = false;


public:
	clsRequest(short CurrentFloor = 0, short DestinationFloor = 0)
	{
		_CurrentFloor = CurrentFloor;
		_DestinationFloor = DestinationFloor;
		setGoingState();
	}

	short CurrentFloor() 
	{ 
		return _CurrentFloor;
	}

	short DestinationFloor() 
	{
		return _DestinationFloor;
	}

	enGoingState GoingState()
	{
		return _GoingState;
	}

	void setTheRequestIsAttachedToAnElevator(bool Value)
	{
		_TheRequestIsAttachedToAnElevator = Value;
	}
	bool getIsTheRequestAttachedToAnElevator()
	{
		return _TheRequestIsAttachedToAnElevator;
	}
	__declspec(property(get = getIsTheRequestAttachedToAnElevator,
		put = setTheRequestIsAttachedToAnElevator)) bool TheRequesIsAttached;

	void setIsTheRequestPending(bool Value)
	{
		_TheRequestIsPending = Value;
	}
	bool getIsTheRequestPending()
	{
		return _TheRequestIsPending;
	}
	__declspec(property(get = getIsTheRequestPending,
		put = setIsTheRequestPending)) bool TheRequestIsPending;

	void set_ElevatorReachedPickUpFloor_Value(bool Value)
	{
		_ElevatorReachedPickUpFloor = Value;
	}
	bool get_ElevatorReachedPickUpFloor_Value()
	{
		return _ElevatorReachedPickUpFloor;
	}
	__declspec(property(get = get_ElevatorReachedPickUpFloor_Value,
		put = set_ElevatorReachedPickUpFloor_Value)) bool ReachedPickUpFloor;

	void setGoingState()
	{
		if (_DestinationFloor == _CurrentFloor)
			_GoingState = enGoingState::CancelRequest;
		else if (_DestinationFloor > _CurrentFloor)
			_GoingState = enGoingState::GoingUP;
		else
			_GoingState = enGoingState::GoingDOWN;
	}
};

