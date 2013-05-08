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

/* Simulation seed */
#define SEED_CAR_LOCATION	config_get_int("SEED_CAR_LOCATION")
#define SEED_ITINERARY		config_get_int("SEED_ITINERARY")

/* Simulation time */
#define SIM_DURATION 		config_get_int("SIM_DURATION")
#define SIM_START 			config_get_int("SIM_START")
#define SIM_END				config_get_int("SIM_END")

/* Simulation Modes Car Operation*/
#define NO_RECHARGE			config_get_int("NO_RECHARGE")
#define RECHARGE			config_get_int("RECHARGE")
  
/* Simulation Modes Quality of Service */
#define GUARANTEED_TIME		config_get_int("GUARANTEED_TIME")
#define DELAYED_TIME		config_get_int("DELAYED_TIME")


/* Simulation Mode as Simulation Parameter */
#define CAR_OPERATION		config_get_int("CAR_OPERATION")
#define SERVICE_QUALITY		config_get_int("SERVICE_QUALITY")




/* Simulation Parameters CUSTOMER INFORMATION */
#define MIN_WAITING_TIME						config_get_int("MIN_WAITING_TIME")
#define MAX_WAITING_TIME						config_get_int("MAX_WAITING_TIME")
#define PASSENGER_REQUEST_COUNT					config_get_int("PASSENGER_REQUEST_COUNT")
#define NUMBER_OF_STATIONS						config_get_int("NUMBER_OF_STATIONS")

/* Simulation Parameters CAR INFORMATION*/
#define NUMBER_OF_CARS							config_get_int("NUMBER_OF_CARS")

#define BATTERY_DEPTH_OF_DISCHARGE				config_get_double("BATTERY_DEPTH_OF_DISCHARGE")
#define BATTERY_DISCHARGE_PER_METRE				config_get_double("BATTERY_DISCHARGE_PER_METRE")
#define BATTERY_MAX_CHARGE						config_get_double("BATTERY_MAX_CHARGE")

#define FARE_MINIMUM							config_get_double("FARE_MINIMUM")
#define DISTANCE_MINIMUM_FARE_IN_METRES			config_get_int("DISTANCE_MINIMUM_FARE_IN_METRES")
#define FARE_ABOVE_MINIMUM_FARE_PER_KM			config_get_double("FARE_ABOVE_MINIMUM_FARE_PER_KM")


/* Simulation Resources */
#define DISTANCE_MATRIX_RESOURCE_FILE 			config_get_string("DISTANCE_MATRIX_RESOURCE_FILE")
#define TIME_MATRIX_RESOURCE_FILE 				config_get_string("TIME_MATRIX_RESOURCE_FILE")
#define STATION_COORDINATES_RESOURCE_FILE 		config_get_string("STATION_COORDINATES_RESOURCE_FILE")

/* Simulation Output Dumps */
#define CARS_BATTERY_POWER_DAT_FILE 			config_get_string("CARS_BATTERY_POWER_DAT_FILE")
#define CARS_BATTERY_RECHARGE_COUNT_FILE 		config_get_string("CARS_BATTERY_RECHARGE_COUNT_FILE")

#define CARS_REVENUE_EARNINGS_DAT_FILE	 		config_get_string("CARS_REVENUE_EARNINGS_DAT_FILE")
#define CARS_REVENUE_LOSSES_DAT_FILE  			config_get_string("CARS_REVENUE_LOSSES_DAT_FILE")
#define CARS_REVENUE_TOTAL_DAT_FILE 			config_get_string("CARS_REVENUE_TOTAL_DAT_FILE")

#define CARS_DISTANCE_EARNINGS_DAT_FILE 		config_get_string("CARS_DISTANCE_EARNINGS_DAT_FILE")
#define CARS_DISTANCE_LOSSES_DAT_FILE	 		config_get_string("CARS_DISTANCE_LOSSES_DAT_FILE")
#define CARS_DISTANCE_TOTAL_DAT_FILE 			config_get_string("CARS_DISTANCE_TOTAL_DAT_FILE")

#define SERVICE_PER_LOCATION_STATS_FILE 		config_get_string("SERVICE_PER_LOCATION_STATS_FILE")

#define PASSENGER_REQ_ARRIVAL_STATS_FILE 		config_get_string("PASSENGER_REQ_ARRIVAL_STATS_FILE")

/* Meta configuration */
#define EXEC_TRACE	config_get_int("EXEC_TRACE")
#define SIM_TRACE	config_get_int("SIM_TRACE")	

/* Some common utility functions */

#define MIN(a, b)	((a < b) ? a : b)
#define MAX(a, b)	((a > b) ? a : b)

void seedRandomizer();
double frand();
double UNIFORM(double a, double b);
double EXP(double lambda);


#endif
