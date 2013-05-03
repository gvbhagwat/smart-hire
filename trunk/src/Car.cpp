#include "Car.hpp"

Car::Car(int _id):id(_id){
	availibility = 0;
}

Car::Car(int _id, Battery _battery):
		id(_id), battery(_battery){
	availibility = 0;
}

Car::Car(int _id, Battery _battery, Location _location):
		id(_id),battery(_battery), currlocation(_location){
	availibility = 0;				
}


Car::Car(int _id, Battery _battery, Location _location, Distance dist, Revenue rev, int isH):
	id(_id),battery(_battery), currlocation(_location), cumDistance(dist), totalRevenue(rev), availibility(isH){
}

int Car::getCarId(){
		return id;
}
