#include "Car.hpp"

Car::Car(int _id):id(_id){
	isHired = false;
}

Car::Car(int _id, Battery _battery):
		id(_id), battery(_battery){
	isHired = false;
}

Car::Car(int _id, Battery _battery, Location _location):
		id(_id),battery(_battery), currlocation(_location){
	isHired = false;				
}


Car::Car(int _id, Battery _battery, Location _location, Distance dist, Revenue rev, bool isH):
	id(_id),battery(_battery), currlocation(_location), cumDistance(dist), totalRevenue(rev), isHired(isH){
}

int Car::getCarId(){
		return id;
}
