#ifndef LOCATION_HPP
#define LOCATION_HPP

class Location{

	public:

	int id;
	double latitude;
	double longitude;

	Location();
	Location(int id);
	Location(int id, double lat, double longi);
	
	Location( const Location& other);
};

#endif
