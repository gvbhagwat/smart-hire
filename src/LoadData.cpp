#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
int Distance[50][50],Time[50][50];

using namespace std;
string Station[50];
int main()
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
	  if(j==50)
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
	  istringstream ( cell ) >> Time[i][j];
	  j++;
	  if(j==50)
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
  
  for(i=0;i<50;i++){
    for(j=0;j<50;j++){
      cout<<i<<","<<j<<"#"<<Time[i][j]<<" ";
    }
    cout<<endl;
  }
  for(i=0;i<50;i++){
    cout<<Station[i]<<endl;
  }

}
