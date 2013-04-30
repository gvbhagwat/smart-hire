#include "Revenue.hpp"
#include "sim.hpp"

Revenue::Revenue(){
		earnings = losses = 0.0;
}

Revenue::Revenue(const Revenue& other):
	earnings( other.earnings ), losses( other.losses ){
}

void Revenue::addEarnings(double amount){
		earnings += amount;
}

// GETTERS
//

double Revenue::getEarnings(){
	return earnings;
}

double Revenue::getLosses(){
	return losses;
}

double Revenue::getTotalRevenue(){
	return earnings + losses;
}


/**
 * earnings calculated as per the revenue model
 */
void Revenue::addEarningsByDistance(int metres){

	double fare = 0.0;

	if(metres - DISTANCE_MINIMUM_FARE_IN_METRES > 0)
		{
		   metres -= DISTANCE_MINIMUM_FARE_IN_METRES;
		   fare = FARE_MINIMUM + (metres / KM) * FARE_ABOVE_MINIMUM_FARE_PER_KM;
		}
	else 
		fare = FARE_MINIMUM;

	this->addEarnings(fare);
}

void Revenue::addLosses(double amount){
		losses += amount;
}

/**
 * losses calculated as per the revenue model
 */
void Revenue::addLossesByDistance(int metres){

	double fare = 0.0;

	if(metres - DISTANCE_MINIMUM_FARE_IN_METRES > 0)
		{
		   metres -= DISTANCE_MINIMUM_FARE_IN_METRES;
		   fare = FARE_MINIMUM + (metres / KM) * FARE_ABOVE_MINIMUM_FARE_PER_KM;
		}
	else 
		fare = FARE_MINIMUM;

	this->addLosses(fare);
}
