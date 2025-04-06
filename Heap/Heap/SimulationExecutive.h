#pragma once

typedef double Time;

class EventAction
{
public:
	EventAction() {};
	virtual void Execute() = 0;
};

class EventCondition
{
public:
	EventCondition() {};
	virtual bool Evaluate() = 0;
};

class SimulationExecutive
{
public:
	static void InitializeSimulation();
	/*
	Behavior - Initializes the simulation.  Simulation time is initialized to 0.
	*/

	static Time GetSimulationTime();
	/*
	Behavior - returns the current simulation time.
	*/

	static void RunSimulation();
	/*
	Behavior - Executes the simulation.  It continually selects the event with
	the smallest timestamp for execution until there are no events left to
	execute (selection of simultaneous events not specified).  Prior to
	advancing time, the set of registered conditional events are each evaluated
	and should their condition be met, their event action is executed.
	*/
	
	static void RunSimulation(Time endTime);
	/*
	Behavior - Identical to the above behavior except that the simulation will
	also terminate if (simulation time > endTime).
	*/
	
	static void ScheduleEventIn(Time delta, EventAction *ea);
	/*
	Behavior - Scheduled the event action ea to be executed when the simulation
	time equals the current simulation time plus delta.
	*/

	static void ScheduleEventAt(Time time, EventAction *ea);
	/*
	Behavior - Scheduled the event action ea to be executed when the simulation
	time equals time.
	*/

private:
	struct Event;
	class EventSet;
	static EventSet _eventSet;
	static Time _simTime;
};
