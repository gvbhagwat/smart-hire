#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdlib> //for srand() and rand()

int Distance[50][50],TimeToTravel[50][50];
int carLocation[100];	//just for testing
int passengerRequestCount,carCount,seedCarLocation,seedItinerary;
int minWaitingTime,maxWaitingTime,NUMBER_OF_STATIONS;
int simStartTime,simDuration,timeOfRequest;

void loadDatabase();
void printDatabase();
void init();
void publishCars();
void pushPassengerRequests();
void PassengerRequestEvent(int,int,int,int);

using namespace std;
string Station[50];
void init()
{
	carCount=100;
	seedCarLocation=352;
	passengerRequestCount=50;
	seedItinerary=234;
	minWaitingTime=120;		//in seconds
	maxWaitingTime=1200;	//in seconds
	NUMBER_OF_STATIONS=50;
	simStartTime=0;			//in seconds
	simDuration=3600*5;		//in seconds
	publishCars();
	pushPassengerRequests();
}

void publishCars()
{
	int i,LocationID;

	//srand is library function to define the seed
	srand(seedCarLocation);
	for(i=0;i<carCount;i++)
	{
		LocationID=rand()%NUMBER_OF_STATIONS;
		carLocation[i]=LocationID;	//temp. to be deleted later
		//cout<<LocationID<<endl;
		
		//insert here a code to update car vector. 
		//
		//Car.id=i
		//Car.location=LocationID
		//
	}
}
void pushPassengerRequests(){
	int i,source,destination,waitingTime;
	srand(seedItinerary);
	for (i=0;i<passengerRequestCount;i++){
		source=rand()%NUMBER_OF_STATIONS;
		destination=rand()%NUMBER_OF_STATIONS;
		waitingTime=rand()%(maxWaitingTime-minWaitingTime) + minWaitingTime;
		timeOfRequest=rand()% simDuration+ simStartTime;
		if(i==10){	//just to test, no other significance of this condition
			PassengerRequestEvent(timeOfRequest,source,destination,waitingTime);
		}
		//cout<<source<<endl<<destination<<endl<<waitingTime<<endl<<timeOfRequest<<endl;
		//cout<<timeOfRequest<<endl;
		//insert code here to update passengerRequest Event and push on to the event queue
		//
		//
		//addInQueue event(sourse,destination,waitingtime,timeOfRequest)
		//
		//
	}
}
void PassengerRequestEvent(int time_of_request,int source,int destination, int max_waiting_time)
{
	int i,min,choosenCar;
	min=100000;
	//select eligible cars
	for(i=0;i<carCount;i++)
	{
		// Select cars which are currently free and can service the customer.
		if(/* !car.hire && */ TimeToTravel[carLocation[i]][source] < max_waiting_time) 
		{
			
			/*
			if (car.battery.getCharge()>car.battery.chargeRequiredByDistance(Distance[carLocation[i]][source]+Distance[source][destination]) )
			{
				objective1();
			}
			*/
			cout<<i<<endl;
			if(TimeToTravel[carLocation[i]][source] < min)
			{
				min=TimeToTravel[carLocation[i]][source];
				choosenCar=i;
			}
		}
		//select cars which are currently unavailable but can service the customer within max_waiting_time
		//2nd increment
		/*
			scan the que from time_of_request to max_waiting_time for PassengerServicedEvent
			{
				carID=ID of the car releaased in PassengerServicedEvent
				releasedLocation=Location of the car releaased in PassengerServicedEvent
				
				if(TimeToTravel[releasedLocation][source] < max_waiting_time-(time_of_PassengerServicedEvent-time_of_request)){
					cout<<i<<endl;
				}
			}
		*/
		
	}
	cout<<"ChoosenCar="<<choosenCar<<endl;
	
}

void loadDatabase()
{

	int i,j;

	string line;

	//Load DistanceDatabase into an Distance matrix
	i=0;j=0;
	ifstream  DistanceData("../resources/Distance.csv");
	while(std::getline(DistanceData,line))
	{
		stringstream  lineStream(line);
		string        cell;
		while(getline(lineStream,cell,','))
		{
			//convert String into an int
			istringstream ( cell ) >> Distance[i][j];
			j++;
			if(j==NUMBER_OF_STATIONS)
			{
				i++;
				j=0;
			}
		}
	}

	//Load TimeDatabase into an Time matrix
	i=0;j=0;
	ifstream  TimeData("../resources/Distance.csv");
	while(std::getline(TimeData,line))
	{
		stringstream  lineStream(line);
		string        cell;
		while(getline(lineStream,cell,','))
		{
			//convert String into an int
			istringstream ( cell ) >> TimeToTravel[i][j];
			j++;
			if(j==NUMBER_OF_STATIONS)
			{
				i++;
				j=0;
			}
		}
	}

	//Load StationDatabase into an Station matrix
	i=0;
	ifstream  StationData("../resources/Station.txt");
	while(std::getline(StationData,line))
	{
		Station[i]=line;
		i++;
	} 
}

void printDatabase()
{
	int i,j;
	//Printing Time matrix
	for(i=0;i<NUMBER_OF_STATIONS;i++)
	{
		for(j=0;j<NUMBER_OF_STATIONS;j++)
		{
			cout<<i<<","<<j<<"#"<<TimeToTravel[i][j]<<" ";
		}
		cout<<endl;
	}
	//Printing Station matrix
	for(i=0;i<NUMBER_OF_STATIONS;i++)
	{
		cout<<Station[i]<<endl;
	}

}
void writeToFile()
{
	ofstream myfile;
	myfile.open ("example.txt");
  	myfile << "Writing this to a file.\n";
  	myfile.close();
}
int main()
{
	writeToFile();
	loadDatabase();
	//  printDatabase();
	init();
}

