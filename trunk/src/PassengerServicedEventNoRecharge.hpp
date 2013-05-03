#ifndef PASSENGER_REQ_HPP
#define PASSENGER_REQ_H

#include "Event.hpp"
#include "BaseScenario.hpp"

class PassengerServicedEventNoRecharge : public Event{
	

	protected:

	BaseScenario& baseScenario;
	int carId;

	public:

	PassengerServicedEventNoRecharge(int time, BaseScenario& baseScenario, int CarId);
	bool hasBatteryOverDishargeDepthButUnusable(int carId);
	void handle(EventList& eventList);
};

#endif
