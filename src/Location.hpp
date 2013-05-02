#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <string>
using namespace std;
class Location{

	public:

	int id;
	string name;
	double latitude;
	double longitude;

	Location();
	Location(int id);
	Location(int id, string name);
	Location(int id, double lat, double longi);
	
	Location( const Location& other);
};

#endif
