#include <cstdlib>
#include <iostream>
#include <vector>

#include "sim.hpp"
#include "BaseScenario.hpp"
#include "Event.hpp"

using namespace std;

void testing();
void carTesting();


extern "C" {
	void config_init(const char*);
}

int main(int argc, char** argv)
{
		
	// Initialize config parameters
	config_init(argv[1]);

	//carTesting();

	// The scenario to execute. Will be instantiated depending on context
	BaseScenario* scenario;

	// The event list for the simulator
	EventList eventList;

	// The virtual simulation time
	double time;
	
	// Seed random number generator (used in event generation)
	seedRandomizer();

	// For now, the scenario is TCP
	scenario = new BaseScenario(eventList,
							    NUMBER_OF_CARS,
								PASSENGER_REQUEST_COUNT,
								SEED_CAR_LOCATION,
								SEED_ITINERARY);

	scenario->initializeScenario();

	//((BaseScenario*)scenario)->printShortestDistancematrix();

	// Main simulation loop
	while( !eventList.empty() && time < SIM_DURATION )
	{
		//std::cout<<"Event List not Empty"<<std::endl;	

		// Get next event (with smallest timestamp)
		Event* event = eventList.top();

		eventList.pop();
		
		// Set current time to time of event
		time = event->getTime();
		cout<<"Event time : "<<time<<endl;

		// Handle the event
		event->handle(eventList);

		// Delete the event object to free memory
		delete event;

		// Update statistics for scenario
		//scenario->updateStatistics(time);
	}

	//std::cout<<"Event List Empty"<<std::endl;	
		

	// Kill the scenario
	delete scenario;

	// Exit
	return 0;
}

void carTesting(){

	int i = 0;
	Battery b(BATTERY_MAX_CHARGE, BATTERY_DEPTH_OF_DISCHARGE, BATTERY_DISCHARGE_PER_METRE);
	Location l;

	Car* c1 = new Car(i,b,l);
	Car* c2 = new Car(i+1,b,l);

	cout<<"----------------------"<<endl<<"TESTING CAR CLASS AND ITS VECTORS"<<endl<<"------------------------"<<endl;
	cout<<"location l = (id,lat,long) = "<<l.id<<" "<<l.latitude<<" "<<l.longitude<<endl;
	cout<<"b.current_rate = "<<b.getCurrentCharge()<<endl;
	cout<<"b.depth_of_ischarge = "<<b.getDepthOfDischarge()<<endl;
	cout<<"b.inital_rechargeCount = "<<b.getRechargeCount()<<endl;

	cout<<"---Car "<<c1->getCarId()<<" ---"<<endl;
	cout<<"location l = (id,lat,long) = "<<c1->currlocation.id<<" "<<c1->currlocation.latitude<<" "<<c1->currlocation.longitude<<endl;
	cout<<"b.current_rate = "<<c1->battery.getCurrentCharge()<<endl;
	cout<<"b.depth_of_ischarge = "<<c1->battery.getDepthOfDischarge()<<endl;
	cout<<"b.inital_rechargeCount = "<<c1->battery.getRechargeCount()<<endl;
	
	cout<<"---Car "<<c2->getCarId()<<" ---"<<endl;
	cout<<"location l = (id,lat,long) = "<<c2->currlocation.id<<" "<<c2->currlocation.latitude<<" "<<c2->currlocation.longitude<<endl;
	cout<<"b.current_rate = "<<c2->battery.getCurrentCharge()<<endl;
	cout<<"b.depth_of_ischarge = "<<c2->battery.getDepthOfDischarge()<<endl;
	cout<<"b.inital_rechargeCount = "<<c2->battery.getRechargeCount()<<endl;

	l.id = 3;
	l.longitude = 4;
	l.latitude = 3;


	b.dischargeBatteryByDistance(100);
	
	cout<<endl<<" VALUES OF B AND L INITIALLLY CHANGED TO "<<endl<<endl;
	cout<<"location l = (id,lat,long) = "<<l.id<<" "<<l.latitude<<" "<<l.longitude<<endl;
	cout<<"b.current_rate = "<<b.getCurrentCharge()<<endl;
	cout<<"b.depth_of_ischarge = "<<b.getDepthOfDischarge()<<endl;
	cout<<"b.inital_rechargeCount = "<<b.getRechargeCount()<<endl;
	
	
	cout<<endl<<" VALUES OF c1 and c2 are now: "<<endl<<endl;
	cout<<"---Car "<<c1->getCarId()<<" ---"<<endl;
	cout<<"location l = (id,lat,long) = "<<c1->currlocation.id<<" "<<c1->currlocation.latitude<<" "<<c1->currlocation.longitude<<endl;
	cout<<"b.current_rate = "<<c1->battery.getCurrentCharge()<<endl;
	cout<<"b.depth_of_ischarge = "<<c1->battery.getDepthOfDischarge()<<endl;
	cout<<"b.inital_rechargeCount = "<<c1->battery.getRechargeCount()<<endl;
	
	cout<<"---Car "<<c2->getCarId()<<" ---"<<endl;
	cout<<"location l = (id,lat,long) = "<<c2->currlocation.id<<" "<<c2->currlocation.latitude<<" "<<c2->currlocation.longitude<<endl;
	cout<<"b.current_rate = "<<c2->battery.getCurrentCharge()<<endl;
	cout<<"b.depth_of_ischarge = "<<c2->battery.getDepthOfDischarge()<<endl;

	Battery b1(BATTERY_MAX_CHARGE, BATTERY_DEPTH_OF_DISCHARGE, BATTERY_DISCHARGE_PER_METRE);
	
	std::vector<Car> cars;
	
	for(int i = 1; i <=  NUMBER_OF_CARS; i++){

		cars.push_back(i);

	}

	for(std::vector<Car>::iterator it = cars.begin(); it != cars.end(); ++it){

			(*it).battery = b1;
			(*it).battery.dischargeBatteryByDistance(2500);
			cout<<"Car id: "<<(*it).getCarId()<<" and curr battery "<<(*it).battery.getCurrentCharge()<<endl;
		}

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
