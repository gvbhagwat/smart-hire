#include "PassengerRequestEvent.hpp"
#include <iostream>
using namespace std;

PassengerRequestEvent::PassengerRequestEvent(int _time, BaseScenario& _scenario, Location source, Location dest, int wait):
    Event(time), baseScenario(_scenario), sourceLocation(source), destLocation(dest), waitingTime(wait) {
    time = _time;
}

void PassengerRequestEvent::handle(EventList& eventList) {

    cout<<"Event handled at time "<<time<<endl;

    std::vector<Car*> selectedCars;

	int firstFilterCount = 0;

    for(unsigned int i=0 ; i<baseScenario.cars.size() ; i++) {

        int timeCarLocationToSource = baseScenario.leastTimeMatrix[ baseScenario.cars[i]->currlocation.id ][ sourceLocation.id ];

        if( baseScenario.cars[i]->isHired == false && ( timeCarLocationToSource < waitingTime ) ) {

			firstFilterCount++;

            // cout << "First filter car Id = "<<baseScenario.cars[i]->getCarId()<<endl;

            int distanceCarLocationToDestination = baseScenario.shortestDistanceMatrix[ sourceLocation.id ][ destLocation.id ] +
                                                   baseScenario.shortestDistanceMatrix[ baseScenario.cars[i]->currlocation.id ][ sourceLocation.id ];

            int currentCharge = baseScenario.cars[i]->battery.getCurrentCharge();

            int DOD = baseScenario.cars[i]->battery.getDepthOfDischarge();

            int chargeRequired = baseScenario.cars[i]->battery.chargeRequiredByDistance(distanceCarLocationToDestination);

	        // cout<<" currCharge "<<currentCharge <<" DOD "<<DOD<<" chargeRequired "<<chargeRequired<<endl;
            // cout<<" currCharge -DOD "<<currentCharge -DOD <<" chargeRequired "<<chargeRequired<<endl;
            // cout<<" ----------"<<endl;


            if( ( currentCharge - DOD ) > chargeRequired ) {

               //  cout<<"Second Charge Filter"<<baseScenario.cars[i]->getCarId()<<endl;

                int selId = baseScenario.cars[i]->getCarId();
                Battery b (baseScenario.cars[i]->battery);
                Location l (baseScenario.cars[i]->currlocation);
                Distance d (baseScenario.cars[i]->cumDistance);
                Revenue r(baseScenario.cars[i]->totalRevenue);

                selectedCars.push_back(new Car(selId,b,l,d,r, false));

            }
        }
    }

    int minTime = 100000;

    // cout<<"Number of selected cars after 1st Filter "<<firstFilterCount<<endl;
    // cout<<"Number of selected cars after 2nd Filter "<<selectedCars.size()<<endl;

    if(selectedCars.empty()) {
        cout<<"No cars could pass even the Two fitlers :( "<<endl;
        return;
    }
    else {


        Car* choosenCar;

        for(unsigned int i=0 ; i<selectedCars.size() ; i++) {

            int timeCarLocationToSource=baseScenario.leastTimeMatrix[selectedCars[i]->currlocation.id][sourceLocation.id];

            if( timeCarLocationToSource < minTime) {

                minTime = timeCarLocationToSource;
                choosenCar=selectedCars[i];
            }
        }

        int choosenCarId=choosenCar->getCarId();

        cout<<"Out of selected cars: "<<selectedCars.size()<<" Final 3rd Filter Choosen Car:"<<choosenCarId<<endl;

		baseScenario.cars[choosenCarId]->isHired = true;

		int distanceCarLocationToDestination =
				baseScenario.shortestDistanceMatrix[ sourceLocation.id ][ destLocation.id ] +
				baseScenario.shortestDistanceMatrix[ baseScenario.cars[choosenCarId]->currlocation.id ][ sourceLocation.id ];

		baseScenario.cars[choosenCarId]->battery.dischargeBatteryByDistance( distanceCarLocationToDestination );
        
		//cout<<"Number of cars is was"<<baseScenario.cars.size()<<endl;
    }
}


