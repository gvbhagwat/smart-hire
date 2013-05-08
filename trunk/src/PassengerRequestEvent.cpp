// Author: Gaurav Bhagwat

#include "PassengerRequestEvent.hpp"
#include "PassengerServicedNoRechargeEvent.hpp"
#include <iostream>
using namespace std;

/**
 * @brief
 *
 * @param _time
 * @param _scenario
 * @param source
 * @param dest
 * @param wait
 *
 * @return
 **/
PassengerRequestEvent::PassengerRequestEvent(int _time, BaseScenario& _scenario, Location source, Location dest, int wait):
    Event(time), baseScenario(_scenario), sourceLocation(source), destLocation(dest), waitingTime(wait) {
    time = _time;
}

/**
 * @brief
 *
 * @param eventList
 **/
void PassengerRequestEvent::handle(EventList& eventList) {

    bool serviceResult = false;			// flag
    std::vector<Car*> selectedCars;		// new vector of chosen cars

    if (baseScenario.getModeServiceQuality() == GUARANTEED_TIME) {
        // For each car
        for(unsigned int i=0 ; i<baseScenario.cars.size() ; i++) {

            // find the time required by the car to reach to passenger
            int timeCarLocationToSource = baseScenario.leastTimeMatrix[ baseScenario.cars[i]->currlocation.id ][ sourceLocation.id ];

            // First filter : screen the cars which are nto available nor can they satisfy waiting time criteria
            if( baseScenario.cars[i]->availibility == 0 && ( timeCarLocationToSource < waitingTime ) ) {

                // For these screened cars, find total distance taken to complete the journey as per customer's requests
                int distanceCarLocationToDestination = baseScenario.shortestDistanceMatrix[ sourceLocation.id ][ destLocation.id ] +
                                                       baseScenario.shortestDistanceMatrix[ baseScenario.cars[i]->currlocation.id ][ sourceLocation.id ];

                // Now, calculate the battery requirements of the journey
                int currentCharge = baseScenario.cars[i]->battery.getCurrentCharge();
                int DOD = baseScenario.cars[i]->battery.getDepthOfDischarge();
                int chargeRequired = baseScenario.cars[i]->battery.chargeRequiredByDistance(distanceCarLocationToDestination);

                // Second Filter: Screen the cars which have enough battery for the journey
                if( ( currentCharge - DOD ) > chargeRequired ) {

                    // add those selected cars to a new set
                    int selId = baseScenario.cars[i]->getCarId();
                    Battery b (baseScenario.cars[i]->battery);
                    Location l (baseScenario.cars[i]->currlocation);
                    Distance d (baseScenario.cars[i]->cumDistance);
                    Revenue r(baseScenario.cars[i]->totalRevenue);

                    selectedCars.push_back(new Car(selId,b,l,d,r, false));

                }
            }
        }



        // if there are no cars that can satisfy the time requirements (and the battery requirements)
        if(selectedCars.empty()) {

            // Publish the event failure
            baseScenario.updateServicePerLocationStats(time,sourceLocation.id,destLocation.id,waitingTime,(int)serviceResult);
            return;
        }
        // case when cars do exist which can satisfy the criteria
        else {

            // Optimization #01: select the car with minimum time required, choose from the "selected Cars"
            int minTime = 100000;
            Car* choosenCar = NULL ;
            for(unsigned int i=0 ; i<selectedCars.size() ; i++) {

                int timeCarLocationToSource=baseScenario.leastTimeMatrix[selectedCars[i]->currlocation.id][sourceLocation.id];
                if( timeCarLocationToSource < minTime) {
                    minTime = timeCarLocationToSource;
                    choosenCar=selectedCars[i];
                }
            }

            int choosenCarId=choosenCar->getCarId();

            // The car has been chosen, now update its distance, battery and revenue statistics

            // First "hire" the car
            baseScenario.cars[choosenCarId]->availibility = 1;

            // Second A:  calculate the total distance required
            int distCarToSource  =  baseScenario.shortestDistanceMatrix[ sourceLocation.id ][ destLocation.id ];
            int distSourceToDest =  baseScenario.shortestDistanceMatrix[ baseScenario.cars[choosenCarId]->currlocation.id ][ sourceLocation.id ];

            // Second B: Update the distance by loss and by gain
            baseScenario.cars[choosenCarId]->cumDistance.addMeteredDistance(distSourceToDest);
            baseScenario.cars[choosenCarId]->cumDistance.addWastage(distCarToSource);

            // Second C: Update the revenue generated by the travel and/or losses
            baseScenario.cars[choosenCarId]->totalRevenue.addEarningsByDistance(distSourceToDest);
            baseScenario.cars[choosenCarId]->totalRevenue.addLossesByDistance(distCarToSource);


            // Third: discharge the battery
            baseScenario.cars[choosenCarId]->battery.dischargeBatteryByDistance( distCarToSource + distSourceToDest );


            // Fourth: update the service result
            serviceResult = true;

            // Fifth: Publish the event stats (successful)
            baseScenario.updateServicePerLocationStats(time,sourceLocation.id,destLocation.id,waitingTime, (int)serviceResult);

            // Finally, and most important, schedule car free event after the travel time

            // calculate the time
            int timeCarLocationToDestination = time +
                                               baseScenario.leastTimeMatrix[ sourceLocation.id ][ destLocation.id ] +
                                               baseScenario.leastTimeMatrix[ baseScenario.cars[choosenCarId]->currlocation.id ][ sourceLocation.id ];

            // generate a new event
            eventList.push( new PassengerServicedNoRechargeEvent(timeCarLocationToDestination, baseScenario, choosenCarId) );

            return;
        }
    }
	//THE SERVICE QUALITY IS NOT GUARANTEED BY WAITING TIME AND DELAY IS ALLOWED
    else {

		int delay = 0;
        // For each car
        for(unsigned int i=0 ; i<baseScenario.cars.size() ; i++) {

            // First filter : screen the cars which are not available
            if( baseScenario.cars[i]->availibility == 0 ) {

                // For these screened cars, find total distance taken to complete the journey as per customer's requests
                int distanceCarLocationToDestination = baseScenario.shortestDistanceMatrix[ sourceLocation.id ][ destLocation.id ] +
                                                       baseScenario.shortestDistanceMatrix[ baseScenario.cars[i]->currlocation.id ][ sourceLocation.id ];

                // Now, calculate the battery requirements of the journey
                int currentCharge = baseScenario.cars[i]->battery.getCurrentCharge();
                int DOD = baseScenario.cars[i]->battery.getDepthOfDischarge();
                int chargeRequired = baseScenario.cars[i]->battery.chargeRequiredByDistance(distanceCarLocationToDestination);

                // Second Filter: Screen the cars which have enough battery for the journey
                if( ( currentCharge - DOD ) > chargeRequired ) {

                    // add those selected cars to a new set
                    int selId = baseScenario.cars[i]->getCarId();
                    Battery b (baseScenario.cars[i]->battery);
                    Location l (baseScenario.cars[i]->currlocation);
                    Distance d (baseScenario.cars[i]->cumDistance);
                    Revenue r(baseScenario.cars[i]->totalRevenue);

                    selectedCars.push_back(new Car(selId,b,l,d,r, false));

                }
            }
        }



        // if there are no cars that can satisfy the battery requirements
        if(selectedCars.empty()) {

            // Publish the event failure
            baseScenario.updateServicePerLocationStats(time,sourceLocation.id,destLocation.id,waitingTime,delay,(int)serviceResult);
            return;
        }
        // case when cars do exist which can satisfy the criteria
        else {

            // Optimization #01: select the car with minimum time required, choose from the "selected Cars"
            int minTime = 100000;
            Car* choosenCar = NULL ;
            for(unsigned int i=0 ; i<selectedCars.size() ; i++) {

                int timeCarLocationToSource=baseScenario.leastTimeMatrix[selectedCars[i]->currlocation.id][sourceLocation.id];
                if( timeCarLocationToSource < minTime) {
                    minTime = timeCarLocationToSource;
                    choosenCar=selectedCars[i];
                }
            }

            int choosenCarId=choosenCar->getCarId();

            // The car has been chosen, now update its distance, battery and revenue statistics

            // First "hire" the car
            baseScenario.cars[choosenCarId]->availibility = 1;

            // Second A:  calculate the total distance required
            int distCarToSource  =  baseScenario.shortestDistanceMatrix[ sourceLocation.id ][ destLocation.id ];
            int distSourceToDest =  baseScenario.shortestDistanceMatrix[ baseScenario.cars[choosenCarId]->currlocation.id ][ sourceLocation.id ];

            // Second B: Update the distance by loss and by gain
            baseScenario.cars[choosenCarId]->cumDistance.addMeteredDistance(distSourceToDest);
            baseScenario.cars[choosenCarId]->cumDistance.addWastage(distCarToSource);

            // Second C: Update the revenue generated by the travel and/or losses
            baseScenario.cars[choosenCarId]->totalRevenue.addEarningsByDistance(distSourceToDest);
            baseScenario.cars[choosenCarId]->totalRevenue.addLossesByDistance(distCarToSource);



            // Third: discharge the battery
            baseScenario.cars[choosenCarId]->battery.dischargeBatteryByDistance( distCarToSource + distSourceToDest );


            // Fourth: update the service result
            serviceResult = true;

            // calculate the time
            int timeCarLocationToDestination = time +
                                               baseScenario.leastTimeMatrix[ sourceLocation.id ][ destLocation.id ] +
                                               baseScenario.leastTimeMatrix[ baseScenario.cars[choosenCarId]->currlocation.id ][ sourceLocation.id ];

			delay = waitingTime - timeCarLocationToDestination;
            
			// Fifth: Publish the event stats (successful)
            baseScenario.updateServicePerLocationStats(time,sourceLocation.id,destLocation.id,waitingTime,delay,(int)serviceResult);
			
            // Finally, and most important, schedule car free event after the travel time
            // generate a new event
            eventList.push( new PassengerServicedNoRechargeEvent(timeCarLocationToDestination, baseScenario, choosenCarId) );

            return;
        }

    }
}

