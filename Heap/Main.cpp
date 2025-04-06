#include <iostream>
#include <ctime>
#include "SimulationExecutive.h"
#include "ServerNetwork.h"


/*
* With a small amount of events in the server network,
* the event set outperforms.  However when a larger num
* is considered like 1000 and runsim(1000), the tree/heap
* works better as shown in the attatched excel file with
* graphs
*/


void main()
{
	//
	/*
	class test : public EventAction
	{
	public:
		test()
		{
		}
		void Execute()
		{
			std::cout << "event action recieved" << std::endl;
		}
	};

	Time ia = 1;
	Time ia2 = 2;
	Time ia3 = 3;
	Time ia4 = 4;
	Time ia5 = 5;


	SimulationExecutive::ScheduleEventIn(ia, new test);
	SimulationExecutive::ScheduleEventIn(ia2, new test);
	SimulationExecutive::ScheduleEventIn(ia3, new test);
	SimulationExecutive::ScheduleEventIn(ia4, new test);
	SimulationExecutive::ScheduleEventIn(ia5, new test);

	SimulationExecutive::RunSimulation();
	*/


	
	SimulationExecutive::InitializeSimulation();
	ServerNetwork(10000, 5);
	
	int start_s = clock();

	SimulationExecutive::RunSimulation(1000);

	int stop_s = clock();
	std::cout << "Execution time for RunSimulation: " << (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000 << std::endl;
	
	system("PAUSE");
}
