#include <cstdlib>
#include <iostream>

#include "sim.hpp"
#include "BaseScenario.hpp"
#include "Event.hpp"

using namespace std;

void testing();


extern "C" {
	void config_init(const char*);
}

int main(int argc, char** argv)
{
		
	// Initialize config parameters
	config_init(argv[1]);

	testing();

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
	while( !eventList.empty() && time < SIM_DURATION )
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

void testing(){

Battery b(BATTERY_MAX_CHARGE, BATTERY_DEPTH_OF_DISCHARGE, BATTERY_DISCHARGE_PER_METRE);

cout<<"Testing Battery class"<<endl;
cout<<"current rate = "<<b.getCurrentCharge()<<endl;
cout<<"depth of discharge = "<<b.getDepthOfDischarge()<<endl;
cout<<"inital rechargeCount = "<<b.getRechargeCount()<<endl;

cout<<"discharging after 1000 metres .. battery left = "<<b.dischargeBatteryByDistance(1000)<<endl;
cout<<"recharging battery.. "<<endl;

b.rechargeBattery();

cout<<"Charge is "<<b.getCurrentCharge()<<" and count is "<<b.getRechargeCount()<<endl;

Distance d;

d.addMeteredDistance(500);
d.addWastage(250);

d.addMeteredDistance(500);

cout<<d.getMeteredDistance()<<" "<<d.getWastage()<<" "<<d.getTotalDistance()<<endl;

cout<<"*******"<<endl;
cout<<"testing Revenue Model"<<endl;

Revenue r;

cout<<"Initial e = "<<r.getEarnings()<<" l = "<<r.getLosses()<<endl;
cout<<"min fare = "<<FARE_MINIMUM<<endl;
cout<<"hire per km = "<<FARE_ABOVE_MINIMUM_FARE_PER_KM<<endl;

r.addEarningsByDistance(500);
r.addEarningsByDistance(1000);
r.addEarningsByDistance(1500);


r.addLossesByDistance(500);
r.addLossesByDistance(1000);
r.addLossesByDistance(1500);


cout<<"Now e = "<<r.getEarnings()<<" l = "<<r.getLosses()<<endl;

	
}		