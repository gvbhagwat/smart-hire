#include "BaseScenario.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include "sim.hpp"
using namespace std;


/**
 * @brief
 *
 * @param eventList
 * @param _cars
 * @param _cust
 * @param seedCar
 * @param seedIti):
 */
BaseScenario::BaseScenario(EventList& eventList, int _cars, int _cust, double seedCar, double seedIti):
    Scenario(eventList), nCars(_cars), nCustomerRequests(_cust), seedCarLocation(seedCar), seedItinerary(seedIti) {

    // open all the simulation dump dat files
    revenewLossesStats.open (CARS_REVENUE_LOSSES_DAT_FILE);
    batteryPowerStats.open(CARS_BATTERY_POWER_DAT_FILE);
    batteryRechargeCountStats.open(CARS_BATTERY_RECHARGE_COUNT_FILE);
    revenewEarningStats.open (CARS_REVENUE_EARNINGS_DAT_FILE);
    revenewTotalStats.open (CARS_REVENUE_TOTAL_DAT_FILE);
    distanceEarningStats.open (CARS_DISTANCE_EARNINGS_DAT_FILE);
    distanceLossesStats.open (CARS_DISTANCE_LOSSES_DAT_FILE);
    distanceTotalStats.open (CARS_DISTANCE_TOTAL_DAT_FILE);
    servicePerLocationStats.open (SERVICE_PER_LOCATION_STATS_FILE);

    printHeader(batteryPowerStats);

    printHeader(batteryRechargeCountStats);
    printHeader(revenewEarningStats);
    printHeader(revenewLossesStats);
    printHeader(revenewTotalStats);
    printHeader(distanceEarningStats);
    printHeader(distanceLossesStats);
    printHeader(distanceTotalStats);
    printHeader(servicePerLocationStats);
}


/**
 * @brief
 */
BaseScenario::~BaseScenario() {

    // close all the dat files
    batteryPowerStats.close();
    batteryRechargeCountStats.close();
    revenewEarningStats.close();
    revenewLossesStats.close();
    revenewTotalStats.close();
    distanceEarningStats.close();
    distanceLossesStats.close();
    distanceTotalStats.close();
    servicePerLocationStats.close();
    // destroy the event List
}

// protected functions

/**
 * @breif Will print the header row in dumps.
 *
 * @param outputstream
 */
void BaseScenario::printHeader(ofstream& outputstream) {

    outputstream<<"Time\t";
    for(int i=0; i<50; i++) {
        outputstream<<"car_"<<i<<"\t";
    }
    outputstream<<"\n";
}


/**
 * @brief
 *
 * @return
 */
int BaseScenario::initializeDistanceMatrix() {

    int i= 0,j =0;
    string line;

    // define the ifstream object
    ifstream distanceData(DISTANCE_MATRIX_RESOURCE_FILE);

    if(distanceData.is_open()) {

        while(std::getline(distanceData,line)) {

            stringstream lineStream(line);
            string cell;

            while(getline(lineStream, cell, ',')) {

                //convert string into and int
                istringstream (cell) >> shortestDistanceMatrix[i][j];
                j++;

                if(j == NUMBER_OF_STATIONS) {
                    i++;
                    j=0;
                }
            }

        }

        distanceData.close();
        return 1;
    }
    else return 0;

    return 1;
}


/**
 * @brief
 *
 * @return
 */
int BaseScenario::initializeTimeMatrix() {

    int i= 0,j =0;
    string line;

    // define the ifstream object
    ifstream timeData(TIME_MATRIX_RESOURCE_FILE);

    if(timeData.is_open()) {

        while(std::getline(timeData,line)) {

            stringstream lineStream(line);
            string cell;

            while(getline(lineStream, cell, ',')) {

                //convert string into and int
                istringstream (cell) >> leastTimeMatrix[i][j];
                j++;

                if(j == NUMBER_OF_STATIONS) {
                    i++;
                    j=0;
                }
            }

        }


        timeData.close();

        return 1;

    }
    else return 0;

}


/**
 * @brief
 *
 * @return
 */
int BaseScenario::initializeStationVector() {

    string line;
    int locationid = 0;

    // define the ifstream object
    ifstream stationData(STATION_COORDINATES_RESOURCE_FILE);

    if(stationData.is_open()) {

        while(std::getline(stationData,line)) {
            Location newLocation(locationid, line);
            stations.push_back(newLocation);
        }
        stationData.close();
        return 1;
    }
    else
        return 0;

}


/**
 * @brief
 *
 * @param seedLocation
 *
 * @return
 */
int BaseScenario::initializeCars(double seedLocation) {

    int i,locationId;
    Battery initialBattery;
    int nStations = stations.size();

    //srand is library function to define the seed
    srand(seedCarLocation);
    //	seedRandomizer();

    for(i=0; i<nCars; i++) {
        locationId = rand() % nStations;
        Location initialLocation(locationId);
        initialLocation.name = stations[locationId].name;
        cars.push_back(new Car(i,initialBattery,initialLocation));

    }
    return 1;
}



/**
 * @brief
 *
 * @param seedItinerary
 *
 * @return
 */
int BaseScenario::initializeEvents(double seedItinerary) {

    int sourceLocation, destinationLocation, waitingTime; //waiting time in seconds
    int timeofRequests;
    int nStations = (int)this->stations.size();

    //randomizing the output
    srand(seedItinerary);

    for(int i = 0; i < this->nCustomerRequests; i++) {

        sourceLocation = rand() % nStations;
        destinationLocation = rand() % nStations;
        waitingTime = rand() % (MAX_WAITING_TIME - MIN_WAITING_TIME) + MIN_WAITING_TIME;
        timeofRequests = (rand() % (SIM_DURATION)) + SIM_START;

        cout<<"Request generated at time : "<<timeofRequests<<" from source = "<<sourceLocation<<" to destination = "<<destinationLocation<<" wait = "<<waitingTime<<endl;

    }



    return 0;
}

//public function



/**
 * @brief
 *
 * @return
 */
int BaseScenario::initializeScenario() {

    int status = 0;
    //order is important atleast before cars load all the data
    status += initializeDistanceMatrix();

    status += initializeStationVector();

    status += initializeTimeMatrix();

    status += initializeCars(seedCarLocation);

    status += initializeEvents(seedItinerary);

    return status;
}

// public getter function


/**
 * @brief
 *
 * @return
 */
EventList& BaseScenario::getEventList() {
    return eventList;
}

// protected member function for data dump
//


/**
 * @brief
 *
 * @param time
 *
 * @return
 */
int BaseScenario::updateCarBatteryStats(double time) {
    return 0;
}


/**
 * @brief
 *
 * @param time
 *
 * @return
 */
int BaseScenario::updateCarRevenueStats(double time) {
    return 0;
}


/**
 * @brief
 *
 * @param time
 *
 * @return
 */
int BaseScenario::updateCarDistanceStats(double time) {
    return 0;
}


/**
 * @brief
 *
 * @param time
 *
 * @return
 */
int BaseScenario::updateServicePerLocationStats(double time) {
    return 0;
}


/**
 * @brief
 *
 * @param time
 *
 * @return
 */
int BaseScenario::updateStatistics(double time) {

    int status = 0;

    status += updateCarBatteryStats(time);

    status += updateCarRevenueStats(time);

    status += updateCarDistanceStats(time);

    status += updateServicePerLocationStats(time);

    return status;
}

// auxillary testing functions

/**
 * @brief
 */
void BaseScenario::printShortestDistancematrix() {
    /*	for(int i = 0; i < 50; i++)
    	for(int j = 0; j < 50; j++){
    		cout<<i<<","<<j<<"#"<<shortestDistanceMatrix[i][j]<<" "<<leastTimeMatrix[i][j]<<endl;
    	}
    	*/
    for(int i =0; i < nCars; i++) {

        cout<<"car id #"<<cars[i]->getCarId()<<" currCharge "<<cars[i]->battery.getCurrentCharge()<<" location #"<<cars[i]->currlocation.id<<" "<<cars[i]->currlocation.name<<endl;

    }
}




