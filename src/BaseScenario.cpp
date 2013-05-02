#include "BaseScenario.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "sim.hpp"
using namespace std;

BaseScenario::BaseScenario(EventList& eventList, int _cars, int _cust, double seedCar, double seedIti):
		Scenario(eventList), nCars(_cars), nCustomerRequests(_cust), seedCarLocation(seedCar), seedItinerary(seedIti){

	// open all the simulation dump dat files
/*
CARS_BATTERY_POWER_DAT_FILE  		= "../simdumps/carsBatteryPower.dat"
CARS_BATTERY_RECHARGE_COUNT_FILE  	= "../simdumps/carsBatteryRechargeCount.dat"

CARS_REVENUE_EARNINGS_DAT_FILE 		= "../simdumps/carsRevenueEarnings.dat"
CARS_REVENUE_LOSSES_DAT_FILE 		= "../simdumps/carsRevenueLosses.dat"
CARS_REVENUE_TOTAL_DAT_FILE 		= "../simdumps/carsRevenueTotal.dat"

CARS_DISTANCE_EARNINGS_DAT_FILE 	= "../simdumps/carsDistanceEarnings.dat"
CARS_DISTANCE_LOSSES_DAT_FILE 		= "../simdumps/carsDistanceLosses.dat"
CARS_DISTANCE_TOTAL_DAT_FILE 		= "../simdumps/carsDistanceTotal.dat"

SERVICE_PER_LOCATION_STATS_FILE 	= "../simdumps/servicePerLocation.dat"

*/

	batteryPowerStats.open(CARS_BATTERY_POWER_DAT_FILE);
	batteryRechargeCountStats.open(CARS_BATTERY_RECHARGE_COUNT_FILE);
	revenewEarningStats.open (CARS_REVENUE_EARNINGS_DAT_FILE);
	revenewLossesStats.open (CARS_REVENUE_LOSSES_DAT_FILE);
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
void BaseScenario::printHeader(ofstream& outputstream){
//Will print the header row in dumps.
	outputstream<<"Time\t";
	for(int i=0;i<50;i++){
		outputstream<<"car_"<<i<<"\t";
	}
	outputstream<<"\n";
}
BaseScenario::~BaseScenario(){

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

int BaseScenario::initializeDistanceMatrix(){
	
	int i= 0,j =0;
	string line;

	// define the ifstream object
	ifstream distanceData(DISTANCE_MATRIX_RESOURCE_FILE);
	
	if(distanceData.is_open()){
					
		while(std::getline(distanceData,line)){
			
			stringstream lineStream(line);
			string cell;

			while(getline(lineStream, cell, ',')){

				//convert string into and int
				istringstream (cell) >> shortestDistanceMatrix[i][j];
				j++;
			
					if(j == NUMBER_OF_STATIONS){
						i++; j=0;
				}
			}

		}
	}

	distanceData.close();
	return 0;
}

int BaseScenario::initializeTimeMatrix(){
		return 0;
}

int BaseScenario::initializeStationVector(){
	return 0;
}

int BaseScenario::initializeCars(double seedLocation){
	return 0;
}

int BaseScenario::initializeEvents(double seedItinerary){
	return 0;
}

//public function

int BaseScenario::initializeScenario(){

	int status = 0;

    status += initializeDistanceMatrix();

	status += initializeStationVector();

	status += initializeTimeMatrix();

	status += initializeCars(seedCarLocation);

	status += initializeEvents(seedItinerary);

	return status;
}

// public getter function

EventList& BaseScenario::getEventList(){
		return eventList;
}

// protected member function for data dump
//

int BaseScenario::updateCarBatteryStats(double time){
		return 0;
}

int BaseScenario::updateCarRevenueStats(double time){
		return 0;
}

int BaseScenario::updateCarDistanceStats(double time){
		return 0;
}

int BaseScenario::updateServicePerLocationStats(double time){
		return 0;
}


int BaseScenario::updateStatistics(double time){

	int status = 0;

	status += updateCarBatteryStats(time);

	status += updateCarRevenueStats(time);

	status += updateCarDistanceStats(time);

	status += updateServicePerLocationStats(time);

	return status;
}

// auxillary testing functions

void BaseScenario::printShortestDistancematrix(){
	for(int i = 0; i < 50; i++)
		for(int j = 0; j < 50; j++){
			cout<<i<<","<<j<<"#"<<shortestDistanceMatrix[i][j]<<endl;
		}
}