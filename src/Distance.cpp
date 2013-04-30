#include "Distance.hpp"

Distance::Distance(){
		metered = 0;
		wastage = 0;
}

void Distance::addMeteredDistance(int metres){
		metered += metres;
}

unsigned int Distance::getMeteredDistance(){
		return metered;
}

void Distance::addWastage(int amount){
		wastage += amount;
}

unsigned int Distance::getWastage(){
		return wastage;
}

unsigned int Distance::getTotalDistance(){
		return metered+wastage;
}
