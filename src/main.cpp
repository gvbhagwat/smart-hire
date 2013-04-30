#include <cstdlib>
#include <iostream>

#include "sim.hpp"
#include "BaseScenario.hpp"
#include "Event.hpp"

using namespace std;

extern "C" {
	void config_init(const char*);
}

int main(int argc, char** argv)
{
	// Initialize config parameters
	config_init(argv[1]);

	// The scenario to execute. Will be instantiated depending on context
	Scenario* scenario;

	// The event list for the simulator
	EventList eventList;

	// The virtual simulation time
	double time;
	
	// Seed random number generator (used in event generation)
	seedRandomizer();

	// For now, the scenario is TCP
	//scenario = new TcpScenario(eventList, FTP);

	// Main simulation loop
	while( !eventList.empty() && time < SIM_TIME )
	{
		std::cout<<"Event List not Empty"<<std::endl;	

		// Get next event (with smallest timestamp)
		Event* event = eventList.top();
		eventList.pop();
		
		// Set current time to time of event
		time = event->getTime();

		// Handle the event
		event->handle(eventList);

		// Delete the event object to free memory
		delete event;

		// Update statistics for scenario
		scenario->updateStatistics(time);
	}

	std::cout<<"Event List Empty"<<std::endl;	
		

	// Kill the scenario
	delete scenario;

	// Exit
	return 0;
}
	
