#include "BaseScenario.hpp"
#include <iostream>
using namespace std;

BaseScenario::BaseScenario(EventList& eventList, string dFile, string tFile, string sFile, int _cars, int _cust):
		Scenario(eventList), distanceMatrixResourceFile(dFile), timeMatrixResourceFile(tFile), nCars(_cars), nCustomerRequests(_cust){

	// open all the simulation dump dat files
}

BaseScenario::~BaseScenario(){

	// close all the dat files

	// destroy the event List	
}

// protected functions

int BaseScenario::initializeDistanceMatrix(){
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
