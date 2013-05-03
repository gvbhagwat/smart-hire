#include "PassengerServicedEventNoRecharge.hpp"
#include <iostream>
using namespace std;

/**
 * @brief 
 *
 * @param _time 
 * @param _scenario 
 * @param _carId 
 *
 * @return 
 **/
PassengerServicedEventNoRecharge::PassengerServicedEventNoRecharge(int _time, BaseScenario& _scenario, int _carId):
    Event(time), baseScenario(_scenario), carId(_carId) {
    time = _time;
}

/**
 * @brief 
 *
 * @param eventList 
 **/
void PassengerServicedEventNoRecharge::handle(EventList& eventList) {
	
	// cout<<"Serviced Event handled at "<<time<<endl;

	double currentCharge = baseScenario.cars[carId]->battery.getCurrentCharge();
	double depthofDischarge = baseScenario.cars[carId]->battery.getDepthOfDischarge();

	if(	(currentCharge - depthofDischarge) < depthofDischarge)
		baseScenario.cars[carId]->availibility = 2; // no battery left :( unusable
	else if( hasBatteryOverDishargeDepthButUnusable(carId) )
		baseScenario.cars[carId]->availibility = 2; // still unusable 
	else
		baseScenario.cars[carId]->availibility = 0; // OK!! available for hire..	

	// cout<<"Car availibility of car Id "<<carId<<" is "<<baseScenario.cars[carId]->availibility<<endl;

	return;

}



/**
 * @brief 
 *
 * @param carId 
 *
 * @return 
 **/
bool PassengerServicedEventNoRecharge::hasBatteryOverDishargeDepthButUnusable(int carId){
	
	bool hasInsufficientBattery = true;	
	double allRoutesDischarge[50][50];

	Battery b;

	for (int i = 0; i < 50; i++)
		for (int j = 0; j < 50; j++){

				allRoutesDischarge[i][j] = b.chargeRequiredByDistance( baseScenario.shortestDistanceMatrix[i][j] );

				// not the case of source==source 
				// and that the stored battery is greater than the least requirement for all the routes
				if (i != j && baseScenario.cars[carId]->battery.getCurrentCharge() > allRoutesDischarge[i][j] )
						hasInsufficientBattery = false;
			}

	return hasInsufficientBattery;
}


