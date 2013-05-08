#include "BaseScenario.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include "sim.hpp"
#include "PassengerRequestEvent.hpp"

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
    passengerReqArrivalStats.open(PASSENGER_REQ_ARRIVAL_STATS_FILE);

    printHeader(batteryPowerStats);

    printHeader(batteryRechargeCountStats);
    printHeader(revenewEarningStats);
    printHeader(revenewLossesStats);
    printHeader(revenewTotalStats);
    printHeader(distanceEarningStats);
    printHeader(distanceLossesStats);
    printHeader(distanceTotalStats);
    printHeaderServicePerLocation(servicePerLocationStats);
}


BaseScenario::BaseScenario(EventList& eventList, int _cars, int _cust, double seedCar, double seedIti, int modeServQual, int modeCarOp):
    Scenario(eventList), nCars(_cars), nCustomerRequests(_cust), seedCarLocation(seedCar), seedItinerary(seedIti), modeServiceQuality( modeServQual ),
	   	modeCarOperation(modeCarOp) {

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
    passengerReqArrivalStats.open(PASSENGER_REQ_ARRIVAL_STATS_FILE);

    printHeader(batteryPowerStats);

    printHeader(batteryRechargeCountStats);
    printHeader(revenewEarningStats);
    printHeader(revenewLossesStats);
    printHeader(revenewTotalStats);
    printHeader(distanceEarningStats);
    printHeader(distanceLossesStats);
    printHeader(distanceTotalStats);
    printHeaderServicePerLocation(servicePerLocationStats);
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
    passengerReqArrivalStats.close();
    // destroy the event List
}

int BaseScenario::getModeCarOperation(){
		return modeCarOperation;
}

int BaseScenario::getModeServiceQuality(){
		return modeServiceQuality;
}


// protected functions

/**
 * @breif Will print the header row in dumps.
 *
 * @param outputstream
 */
void BaseScenario::printHeader(ofstream& outputstream) {

    outputstream<<"#Time\t";
    for (int i=0; i<50; i++) {
        outputstream<<"car_"<<i<<"\t";
    }
    outputstream<<"\n";
}

void BaseScenario::printHeaderServicePerLocation(ofstream& outputstream) {
	if( modeServiceQuality == GUARANTEED_TIME )
	    outputstream<<"Time\t"<<"sourceId\t"<<"destId\t"<<"waitTime\t"<<"result"<<endl;
	else
	    outputstream<<"Time\t"<<"sourceId\t"<<"destId\t"<<"waitTime\t"<<"result\t"<<"delay"<<endl;
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

    if (distanceData.is_open()) {

        while (std::getline(distanceData,line)) {

            stringstream lineStream(line);
            string cell;

            while (getline(lineStream, cell, ',')) {

                //convert string into and int
                istringstream (cell) >> shortestDistanceMatrix[i][j];
                j++;

                if (j == NUMBER_OF_STATIONS) {
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

    if (timeData.is_open()) {

        while (std::getline(timeData,line)) {

            stringstream lineStream(line);
            string cell;

            while (getline(lineStream, cell, ',')) {

                //convert string into and int
                istringstream (cell) >> leastTimeMatrix[i][j];
                j++;

                if (j == NUMBER_OF_STATIONS) {
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

    if (stationData.is_open()) {

        while (std::getline(stationData,line)) {
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

    for (i=0; i<nCars; i++) {
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

    int sourceLocationId, destinationLocationId, waitingTime; //waiting time in seconds
    int timeofRequests;
    int nStations = (int)this->stations.size();
    int is9am,is8am,isNight,is6am;

    //randomizing the output
    srand(seedItinerary);

    is9am=1;
    is8am=1;
    is6am=1;
    isNight=1;

    for (int i = 0; i < this->nCustomerRequests; i++) {

        sourceLocationId = rand() % nStations;
        Location source(sourceLocationId, stations[sourceLocationId].name);

        destinationLocationId = rand() % nStations;
        Location dest(destinationLocationId, stations[destinationLocationId].name);

        waitingTime = rand() % (MAX_WAITING_TIME - MIN_WAITING_TIME) + MIN_WAITING_TIME;
        timeofRequests = (rand() % (SIM_DURATION)) + SIM_START;

        //cout<<"Request generated at time : "<<timeofRequests<<" from source = "<<
        //sourceLocationId<<" to destination = "<<destinationLocationId<<" wait = "<<waitingTime<<endl;


        //Code to genarates passenger arrival request as per 9AM 5PM distribution
        if( i % 5 == 0) {
            if(is9am == 1) {
                timeofRequests = (rand() % (SIM_DURATION/24)) +  (SIM_DURATION/24)*9 + SIM_START;
                is9am = 0;
            }
            else {
                timeofRequests = (rand() % (SIM_DURATION/24)) +  (SIM_DURATION/24)*17 + SIM_START;
                is9am = 1;
            }
        }
        if( i % 5 == 1) {
            if(is8am == 1) {
                timeofRequests = (rand() % (SIM_DURATION/24)) +  (SIM_DURATION/24)*8 + SIM_START;
                is8am = 2;
            }
            else if(is8am == 2) {
                timeofRequests = (rand() % (SIM_DURATION/24)) +  (SIM_DURATION/24)*10 + SIM_START;
                is8am = 3;
            }
            else if(is8am == 3) {
                timeofRequests = (rand() % (SIM_DURATION/24)) +  (SIM_DURATION/24)*16 + SIM_START;
                is8am = 4;
            }
            else if(is8am == 4) {
                timeofRequests = (rand() % (SIM_DURATION/24)) +  (SIM_DURATION/24)*18 + SIM_START;
                is8am = 1;
            }
        }
        if( i % 5 == 2 || i % 5 ==3) {
            if(is6am == 1) {
                timeofRequests = (rand() % (SIM_DURATION/12)) +  (SIM_DURATION/24)*6 + SIM_START;
                is6am = 2;
            }
            else if(is6am == 2) {
                timeofRequests = (rand() % (SIM_DURATION/12)) +  (SIM_DURATION/24)*11 + SIM_START;
                is6am = 3;
            }
            else if(is6am == 3) {
                timeofRequests = (rand() % (SIM_DURATION/8)) +  (SIM_DURATION/24)*13 + SIM_START;
                is6am = 4;
            }
            else if(is6am == 4) {
                timeofRequests = (rand() % (SIM_DURATION/12)) +  (SIM_DURATION/24)*19 + SIM_START;
                is6am = 1;
            }
        }
        if( i % 5 == 4) {
            if(isNight == 1) {
                timeofRequests = (rand() % (SIM_DURATION/8)) +  (SIM_DURATION/24)*21 + SIM_START;
                isNight = 2;
            }
            else if( isNight ==2) {
                timeofRequests = (rand() % (SIM_DURATION/8)) +  (SIM_DURATION/24)*0 + SIM_START;
                isNight = 3;
            }
            else if( isNight ==3) {
                timeofRequests = (rand() % (SIM_DURATION/8)) +  (SIM_DURATION/24)*3 + SIM_START;
                isNight = 1;
            }

        }

        //Print Pasenger request Arrival time in file for analysis
        passengerReqArrivalStats<<timeofRequests<<endl;

	    getEventList().push(new PassengerRequestEvent(timeofRequests,*this,source,dest,waitingTime));


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

    batteryPowerStats<<time<<"\t";
    for ( int i=0 ; i < (int)this->cars.size(); i++) {

        batteryPowerStats<<this->cars[i]->battery.getCurrentCharge()<<"\t";

    }
    batteryPowerStats<<endl;
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

    revenewLossesStats<<time<<"\t";
    revenewEarningStats<<time<<"\t";
    revenewTotalStats<<time<<"\t";

    for ( int i=0 ; i < (int)this->cars.size(); i++) {
        revenewLossesStats<<this->cars[i]->totalRevenue.getLosses()<<"\t";
        revenewEarningStats<<this->cars[i]->totalRevenue.getEarnings()<<"\t";
        revenewTotalStats<<this->cars[i]->totalRevenue.getTotalRevenue()<<"\t";
    }
    revenewLossesStats<<endl;
    revenewEarningStats<<endl;
    revenewTotalStats<<endl;

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

    /*  distanceEarningStats.open (CARS_DISTANCE_EARNINGS_DAT_FILE);
        distanceLossesStats.open (CARS_DISTANCE_LOSSES_DAT_FILE);
        distanceTotalStats.open (CARS_DISTANCE_TOTAL_DAT_FILE); */
    distanceEarningStats<<time<<"\t";
    distanceLossesStats<<time<<"\t";
    distanceTotalStats<<time<<"\t";
    for ( int i=0 ; i < (int)this->cars.size(); i++) {
        distanceEarningStats<<this->cars[i]->cumDistance.getMeteredDistance()<<"\t";
        distanceLossesStats<<this->cars[i]->cumDistance.getWastage()<<"\t";
        distanceTotalStats<<this->cars[i]->cumDistance.getTotalDistance()<<"\t";
    }
    distanceEarningStats<<endl;
    distanceLossesStats<<endl;
    distanceTotalStats<<endl;
    return 0;
}


/**
 * @brief
 *
 * @param time
 *
 * @return
 */
int BaseScenario::updateServicePerLocationStats(double time, int sourceId, int destId, int wait, int result) {
    // cout<<"update stats called with result "<<result<<endl;
    servicePerLocationStats<<time<<"\t"<<sourceId<<"\t"<<destId<<"\t"<<wait<<"\t"<<result<<endl;
    return 0;
}

/**
 * @brief
 *
 * @param time
 *
 * @return
 */
int BaseScenario::updateServicePerLocationStats(double time, int sourceId, int destId, int wait, int delay, int result) {
    // cout<<"update stats called with result "<<result<<endl;
    servicePerLocationStats<<time<<"\t"<<sourceId<<"\t"<<destId<<"\t"<<wait<<"\t"<<result<<"\t"<<delay<<endl;
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
    for (int i =0; i < nCars; i++) {

        cout<<"car id #"<<cars[i]->getCarId()<<" currCharge "<<cars[i]->battery.getCurrentCharge()<<" location #"<<cars[i]->currlocation.id<<" "<<cars[i]->currlocation.name<<endl;

    }
}




