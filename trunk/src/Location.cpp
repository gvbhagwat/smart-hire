#include "Location.hpp"

Location::Location(){

	id = -1;
	latitude = 0.0;
	longitude = 0.0;

}

Location::Location(const Location& other):
		id( other.id ), latitude( other.latitude ), longitude( other.longitude ){
}

Location::Location(int id){
  	this->id = id; latitude = 0.0; longitude = 0.0;
}


Location::Location(int _id, double _latitude, double _longitude):
	id(_id),latitude(_latitude),longitude(_longitude){
}

