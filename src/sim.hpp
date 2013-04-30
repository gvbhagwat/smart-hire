#ifndef SIM_HPP
#define SIM_HPP


/* Global configuration parameters */

extern "C" {
	#include "config.h"
}

/* Units of Measurements */
#define SEC			config_get_double("SEC")
#define MINUTES		config_get_int("MINUTES")
#define HOURS		config_get_int("HOURS")
#define METRE		config_get_int("METRE")
#define KM			config_get_int("KM")

/* Simulation Parameters */
#define NUMBER_OF_CARS		config_get_int("NUMBER_OF_CARS")

/* Simulation time */
#define SIM_TIME 			config_get_double("SIM_TIME")
#define SIM_START 			config_get_double("SIM_START")
#define SIM_END				config_get_double("SIM_END")

/* Simulation Resources */
#define DISTANCE_MATRIX_RESOURCE_FILE 		config_get_string("DISTANCE_MATRIX_RESOURCE_FILE")
#define TIME_MATRIX_RESOURCE_FILE 			config_get_string("TIME_MATRIX_RESOURCE_FILE")
#define STATION_COORDINATES_RESOURCE_FILE 	config_get_string("STATIONS_COORDINATES_RESOURCE_FILE")

/* Simulation Output Dumps */
#define CARS_BATTERY_POWER_DAT_FILE 			config_get_string("CARS_BATTERY_POWER_DAT_FILE")
#define CARS_BATTERY_RECHARGE_COUNT_FILE 		config_get_string("CARS_BATTERY_RECHARGE_COUNT_FILE")

#define CARS_REVENUE_EARNINGS_DAT_FILE	 		config_get_string("CARS_REVENUE_EARNINGS_DAT_FILE")
#define CARS_REVENUE_LOSSES_DAT_FILE  			config_get_string("CARS_REVENUE_LOSSES_DAT_FILE ")
#define CARS_REVENUE_TOTAL_DAT_FILE 			config_get_string("CARS_REVENUE_TOTAL_DAT_FILE")

#define CARS_DISTANCE_EARNINGS_DAT_FILE 		config_get_string("CARS_DISTANCE_EARNINGS_DAT_FILE")
#define CARS_DISTANCE_LOSSES_DAT_FILE	 		config_get_string("CARS_DISTANCE_LOSSES_DAT_FILE")
#define CARS_DISTANCE_TOTAL_DAT_FILE 			config_get_string("CARS_DISTANCE_TOTAL_DAT_FILE")

#define SERVICE_PER_LOCATION_STATS_FILE 		config_get_string("SERVICE_PER_LOCATION_STATS_FILE")

/* Some common utility functions */
// #define MIN(a, b)	((a < b) ? a : b)
// #define MAX(a, b)	((a > b) ? a : b)

void seedRandomizer();
double frand();
double UNIFORM(double a, double b);
double EXP(double lambda);


#endif
