#include "BaseScenario.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "sim.hpp"
using namespace std;

BaseScenario::BaseScenario(EventList& eventList, int _cars, int _cust):
		Scenario(eventList), nCars(_cars), nCustomerRequests(_cust){

	// open all the simulation dump dat files
}

BaseScenario::~BaseScenario(){

	// close all the dat files

	// destroy the event List	
}

// protected functions

int BaseScenario::initializeDistanceMatrix(){
	
	int i,j;
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

		 distanceData.close();
		}
	}

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

int BaseScenario::initializeSimulation(double seedLocation, double seedCarItinerary){

	int status = 0;

    status += initializeDistanceMatrix();

	status += initializeStationVector();

	status += initializeTimeMatrix();

	status += initializeCars(seedLocation);

	status += initializeEvents(seedCarItinerary);

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
