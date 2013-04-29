#ifndef CAR_HPP
#define CAR_HPP

/*
 * type which will probably belong to the simulator's event queue.
 * Unhandled events with the least time-stamp are handled first.
 */

#include "Battery.hpp"
#include "Distance.hpp"
#include "Location.hpp"


class Car {

	protected:

	/* Car id */
	int id;
	
	public:
	
	/* Battery of the car */
	Battery battery;

	/* Cumulative Revenue collected by the car till the current time */
	Revenue revenue;
	
	/* Cumulative Distance travelled by the car till the current time */
	Distance distance;

	/* STATE - isHired*/
	bool isHired;

	/* STATE - current Location of the Car */
	Location currlocation;

	public:

	Car(int id);

	Car(int id, Battery battery);

	Car(int id, Battery battery, Location currLocation);
	

	//GETTERS
	
	/**
	 * @return car id of the car
	 */
	int getCarId();


};

#endif
