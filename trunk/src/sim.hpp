#ifndef SIM_HPP
#define SIM_HPP


/* Global configuration parameters */
extern "C" {
	#include "config.h"
}

#define MSEC	config_get_double("MSEC")
#define SEC		config_get_double("SEC")
#define BYTES	config_get_int("BYTES")
#define KB		config_get_int("KB")
#define MB		config_get_int("MB")
#define bps		config_get_double("bps")
#define Kbps	config_get_double("Kbps")
#define Mbps	config_get_double("Mbps")


#define SIM_TIME 					config_get_double("SIM_TIME")
#define FLOW_PLOT_REAL_TIME			config_get_int("FLOW_PLOT_REAL_TIME")		
#define FLOW_DAT_FILE 				config_get_string("FLOW_DAT_FILE")
#define THROUGHPUT_DAT_FILE 		config_get_string("THROUGHPUT_DAT_FILE")
#define THROUGHPUT_PLOT_GRANULARITY config_get_double("THROUGHPUT_PLOT_GRANULARITY")

/* Router config */
#define BUFFER_SIZE				config_get_int("BUFFER_SIZE")
#define LINK_SPEED          	config_get_double("LINK_SPEED")
#define EXTERNAL_DELAY_MEAN     config_get_double("EXTERNAL_DELAY_MEAN")	
#define EXTERNAL_DELAY_OFFSET	config_get_double("EXTERNAL_DELAY_OFFSET")

/* TCP config */
#define MAX_SEGMENT_SIZE            config_get_int("MAX_SEGMENT_SIZE")
#define INITIAL_CONGESTION_WINDOW   config_get_int("INITIAL_CONGESTION_WINDOW")
#define INITIAL_TIMEOUT_VALUE       config_get_double("INITIAL_TIMEOUT_VALUE")
#define INITIAL_SSTHRESH			config_get_int("INITIAL_SSTHRESH")

/* Flow generation */
#define DOS_FILE_SIZE	config_get_int("DOS_FILE_SIZE")
#define FTP_FILE_SIZE 	config_get_int("FTP_FILE_SIZE")
#define FTP_FLOW_COUNT	config_get_int("FTP_FLOW_COUNT")

/* LR-DoS parameters */
#define LR_DOS_PEAK_RATE		config_get_double("LR_DOS_PEAK_RATE")
#define LR_DOS_BURST_LENGTH		config_get_double("LR_DOS_BURST_LENGTH")
#define LR_DOS_PERIOD			config_get_double("LR_DOS_PERIOD")


/* Some common utility functions */
#define MIN(a, b)	((a < b) ? a : b)
#define MAX(a, b)	((a > b) ? a : b)
void seedRandomizer();
double frand();
double UNIFORM(double a, double b);
double EXP(double lambda);
void wait(unsigned int msec);

#endif
