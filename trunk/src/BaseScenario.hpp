#ifndef BASESCENARIO_HPP
#define BASESCENARIO_HPP

#include "Scenario.hpp"
#include "Car.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <boost/numeric/ublas/matrix.hpp>

using namespace std;
using namespace boost::numeric::ublas;

class BaseScenario: public Scenario{

	protected:

	string distanceMatrixResourceFile;
	string timeMatrixResourceFile;
	string stationVectorResourceFile;

	int nCars;
	int nCustomerRequests;

	matrix<int> shortestDistanceMatrix;
	matrix<int> leastTimeMatrix;
	std::vector<Location> stations;
	std::vector<Car> cars;


	ofstream carRevenueDump;
	ofstream carBatteryDump;
	ofstream carDistanceDump;
	ofstream locationDump;

	// protected member functions
	
	// Initialization
	
	bool initializeDistanceMatrix();
	bool initializeTimeMatrix();
	bool initializeStationVector();

	bool initializeCars();
	bool initializeEvents();

	// Update Stats
	
	bool updateCarBatteryStats(double time);
	bool updateCarRevenueStats(double time);
	bool updateCarDistanceStats(double time);

	bool updateServicePerLocationStats(double time);

	public:

	BaseScenario(EventList& eventList, string distanceResourceFile, string timeResourceFile, string stationVectorResourceFile, int nCars, int CustomerReuqests);

	~BaseScenario();

	bool initializeSimulation(double seedCarLocation, double seedCarItinerary);

	EventList& getEventList();
	matrix<int>& getShortestDistanceMatrix();
	matrix<int>& getLeastTimeMatrix();
	std::vector<Car>& getCars();
	std::vector<Location>& getStations();

	void updateStatistics(double time); 

};


#endif
