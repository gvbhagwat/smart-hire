#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <ctime>

#include "sim.hpp"

using namespace std;

/* Seed random number generator using current time */
void seedRandomizer()
{
	srand(time(NULL));
}

/* Generate a uniform random number in [0,1] */
double frand()
{
	return double(rand())/RAND_MAX;
}

/* Generates a uniformly distrubted random number */
double UNIFORM(double a, double b)
{
	return frand()*(b-a) + a;
}

/* Generate an exponentially distributed random number */
double EXP(double lambda)
{
	return (-1/lambda)*log(frand());
}


/* Wait for specified number of milliseconds */
void wait(unsigned int msec)
{
	clock_t goal = clock() + (CLOCKS_PER_SEC/1000)*msec;
	while (clock() < goal);
}

