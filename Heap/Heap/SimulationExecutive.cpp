#include <iostream>
#include <vector>
#include "SimulationExecutive.h"

using namespace std;

struct SimulationExecutive::Event
{
	Event(Time time, EventAction *ea)
	{
		_time = time;
		_ea = ea;
	}
	Time _time;
	EventAction *_ea;
};

class SimulationExecutive::EventSet
{
public:
	EventSet()
	{
	}

	void AddEvent(Time time, EventAction *ea)
	{
		Event *e = new Event(time, ea);
		//propogate up
		if (tree.empty())
		{
			tree.emplace(tree.begin(), e);
		}
		else
		{
			int i = tree.size();
			tree.emplace_back(e);
			while (time < tree.at(floor((i-1) / 2))->_time)
			{
				Event* tmp = tree.at(floor((i-1) / 2));
				tree.at(floor((i - 1) / 2)) = e;
				tree.at(i) = tmp;
				i = floor((i - 1) / 2);
			}	
		}
	}

	Time GetTime()
	{
		return tree.at(0)->_time;
	}

	EventAction *GetEventAction()
	{
		if (tree.size() == 1)
		{
			Event* e = tree.at(0);
			tree.erase(tree.begin());
			return e->_ea;
		}
		else {
			Event* front = tree.at(0);
			Event* back = tree.at(tree.size() - 1);
			int i = 0;
			tree[0] = back;
			tree.erase(tree.end() - 1);

			//heapify
			bool stay = true;
			while ((tree.size() - 1) > ((2 * i) + 1) && stay == true && !tree.empty())
			{
				if (tree.at((2 * i) + 1)->_time <= back->_time)
				{
					Event* tmp = tree.at(i);
					tree.at(i) = tree.at((2 * i) + 1);
					tree.at((2 * i) + 1) = tmp;
					i = (2 * i) + 1;
				}
				else if (tree.at((2 * i) + 2)->_time <= back->_time)
				{
					Event* tmp = tree.at(i);
					tree.at(i) = tree.at((2 * i) + 2);
					tree.at((2 * i) + 2) = tmp;
					i = (2 * i) + 2;
				}
				else
				{
					stay = false;
				}
			}

			return front->_ea;
		}
	}

	bool HasEvent()
	{
		return  !tree.empty();
	}

private:
	vector<Event*> tree;
};

SimulationExecutive::EventSet SimulationExecutive::_eventSet;
Time SimulationExecutive::_simTime = 0.0;

void SimulationExecutive::InitializeSimulation()
	{
		_simTime = 0.0;
	}

Time SimulationExecutive::GetSimulationTime() 
{ 
	return _simTime; 
}

void SimulationExecutive::RunSimulation()
{
	while (_eventSet.HasEvent()) {
		_simTime = _eventSet.GetTime();
		EventAction *ea = _eventSet.GetEventAction();
		ea->Execute();
		delete ea;
	}
}

void SimulationExecutive::RunSimulation(Time endTime)
{
	while (_eventSet.HasEvent() && _simTime <= endTime) {
		_simTime = _eventSet.GetTime();
		EventAction *ea = _eventSet.GetEventAction();
		ea->Execute();
		delete ea;
	}
}

void SimulationExecutive::ScheduleEventIn(Time delta, EventAction *ea)
{
	_eventSet.AddEvent(_simTime + delta, ea);
}

void SimulationExecutive::ScheduleEventAt(Time time, EventAction *ea)
{
	_eventSet.AddEvent(time, ea);
}