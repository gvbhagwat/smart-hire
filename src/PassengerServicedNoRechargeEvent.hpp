#ifndef PASSENGER_REQ_HPP
#define PASSENGER_REQ_H

#include "Event.hpp"
#include "BaseScenario.hpp"

class PassengerServicedNoRechargeEvent : public Event{
	

	protected:

	BaseScenario& baseScenario;
	int carId;

	public:

	PassengerServicedNoRechargeEvent(int time, BaseScenario& baseScenario, int CarId);
	bool hasBatteryOverDishargeDepthButUnusable(int carId);
	void handle(EventList& eventList);
};

#endif
