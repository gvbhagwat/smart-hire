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

int Car::getCarId(){
		return id;
}
