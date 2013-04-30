#include "Location.hpp"

Location::Location(){

	id = -1;
	latitude = 0.0;
	longitude = 0.0;

}

Location::Location(int id){
  	this->id = id; latitude = 0.0; longitude = 0.0;
}


Location::Location(int _id, double _latitude, double _longitude):
	id(_id),latitude(_latitude),longitude(_longitude){
}

