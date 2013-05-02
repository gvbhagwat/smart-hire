#ifndef BASESCENARIO_HPP
#define BASESCENARIO_HPP

#include "Scenario.hpp"
#include "Car.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class BaseScenario: public Scenario{

	protected:

	string distanceMatrixResourceFile;
	string timeMatrixResourceFile;
	string stationVectorResourceFile;

	int nCars;
	int nCustomerRequests;

	ofstream carRevenueDump;
	ofstream carBatteryDump;
	ofstream carDistanceDump;
	ofstream locationDump;

	// protected member functions
	
	// Initialization
	
	int initializeDistanceMatrix();
	int initializeTimeMatrix();
	int initializeStationVector();

	int initializeCars(double seed);
	int initializeEvents(double seed);

	// Update Stats
	
	int updateCarBatteryStats(double time);
	int updateCarRevenueStats(double time);
	int updateCarDistanceStats(double time);

	int updateServicePerLocationStats(double time);

	public:
	
	int shortestDistanceMatrix[50][50];
	int leastTimeMatrix[50][50];

	std::vector<Location> stations;
	std::vector<Car> cars;

	BaseScenario(EventList& eventList, string distanceResourceFile, string timeResourceFile, string stationVectorResourceFile, int nCars, int CustomerReuqests);

	~BaseScenario();

	int initializeSimulation(double seedCarLocation, double seedCarItinerary);

	EventList& getEventList();

	int updateStatistics(double time); 

};


#endif
