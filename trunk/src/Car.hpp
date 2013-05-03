#ifndef CAR_HPP
#define CAR_HPP

/**
 * The simulation entity worked with
 * Car encapsulates the Battery, Revenue generated or lost and the total Distance travelled
 */

#include "Battery.hpp"
#include "Distance.hpp"
#include "Location.hpp"
#include "Revenue.hpp"


class Car {

	protected:

	/* Car id */
	int id;
	
	public:
	
	/* Battery of the car */
	Battery battery;
	
	/* STATE - current Location of the Car */
	Location currlocation;
	
	/* Cumulative Distance travelled by the car till the current time */
	Distance cumDistance;

	/* Cumulative Revenue collected by the car till the current time */
	Revenue totalRevenue;
	
	/* STATE - isHired*/
	bool isHired;


	public:

	Car(int id);

	Car(int id, Battery battery);

	Car(int id, Battery battery, Location currLocation);
	
	Car(int id, Battery battery, Location currLocation, Distance cumDistance, Revenue rev, bool isHired);


	

	

	//GETTERS
	
	/**
	 * @return car id of the car
	 */
	int getCarId();


};
#endif
