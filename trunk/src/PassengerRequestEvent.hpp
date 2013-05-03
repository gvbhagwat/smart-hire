#ifndef PASSENGER_REQ_HPP
#define PASSENGER_REQ_H

#include "Event.hpp"
#include "BaseScenario.hpp"

class PassengerRequestEvent : public Event{
	

	protected:

	BaseScenario& baseScenario;
	Location sourceLocation;
	Location destLocation;
	int waitingTime;


	public:

	PassengerRequestEvent(int time, BaseScenario& baseScenario, Location source, Location dest, int wait);
	void handle(EventList& eventList);

};

#endif
