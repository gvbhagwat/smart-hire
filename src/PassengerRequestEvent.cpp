#include "PassengerRequestEvent.hpp"
#include <iostream>
using namespace std;

PassengerRequestEvent::PassengerRequestEvent(int _time, BaseScenario& _scenario, Location source, Location dest, int wait):
		Event(time), baseScenario(_scenario), sourceLocation(source), destLocation(dest), waitingTime(wait){
	time = _time;
//	cout<<"time = "<<_time<<" source = "<<source.id<<" destination = "<<dest.id<<endl;
	//cout<<"Now -->"<<endl;
//	cout<<"time = "<<getTime()<<" source = "<<sourceLocation.id<<" destination = "<<destLocation.id<<endl<<"---"<<endl;

}

void PassengerRequestEvent::handle(EventList& eventList){
	cout<<"Event handled at time "<<time<<endl;

	cout<<"Number of cars is "<<baseScenario.cars.size()<<endl;
}


