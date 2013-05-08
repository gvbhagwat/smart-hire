#ifndef BASESCENARIO_HPP
#define BASESCENARIO_HPP

#include "Scenario.hpp"
#include "sim.hpp"
#include "Car.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class BaseScenario: public Scenario{

	protected:

	int nCars;
	int nCustomerRequests;
	double seedCarLocation;
	double seedItinerary;
	double seedRechargeLocation;

	int modeServiceQuality;
	int modeCarOperation;

	ofstream batteryPowerStats,
		batteryRechargeCountStats,
		revenewEarningStats,
		revenewLossesStats,
		revenewTotalStats,
		distanceEarningStats,
		distanceLossesStats,
		distanceTotalStats,
		passengerReqArrivalStats,
		servicePerLocationStats;


	// protected member functions
	void printHeader(ofstream& outputstream);
	void printHeaderServicePerLocation(ofstream& outputstream);
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




	public:
	
	void printShortestDistancematrix();
	int shortestDistanceMatrix[50][50];
	int leastTimeMatrix[50][50];

	std::vector<Location> stations;
	std::vector<Car*> cars;
	
	EventList& getEventList();

	// From the base class

	BaseScenario(EventList& eventList, int nCars, int CustomerReuqests, double seedCarLocation, double seedItinerary);
	BaseScenario(EventList& eventList, int nCars, int CustomerReuqests, double seedCarLocation, double seedItinerary, int modeServiceQuality, int modeCarOperation);
	~BaseScenario();
	int initializeScenario();
	int updateStatistics(double time);

	int updateServicePerLocationStats(double time, int sourceId, int destId, int waitingTime, int result);
	int updateServicePerLocationStats(double time, int sourceId, int destId, int waitingTime, int delay, int result);

	int getModeServiceQuality();
	int getModeCarOperation();
	

};


#endif
