#include "Location.hpp"

Location::Location(){

	id = -1;
	name = "NULL";
	latitude = 0.0;
	longitude = 0.0;

}

Location::Location(const Location& other):
		id( other.id ), name(other.name),latitude( other.latitude ), longitude( other.longitude ){
}

Location::Location(int id){
  	this->id = id; latitude = 0.0; longitude = 0.0;name = "NULL";
}

Location::Location(int _id, string _name):
		id(_id), name(_name){

 latitude = 0.0; longitude = 0.0;
}

Location::Location(int _id, double _latitude, double _longitude):
	id(_id),latitude(_latitude),longitude(_longitude){
			name = "null";
}

