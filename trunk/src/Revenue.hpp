#ifndef REVENUE_HPP
#define REVENUE_HPP

/*
 * type which will probably belong to the simulator's event queue.
 * Unhandled events with the least time-stamp are handled first.
 */
#include "Distance.hpp"

class Revenue {
	
	protected:

	/* Profitable revenue */
	double earnings;

	/* Non-Profitable revenue */
	double losses;

	public:

	Revenue();
	
	void addEarnings(double amount);
	void addEarnings(double amount, Distance& d);

	double getEarnings();

	void addLosses(double amount);
	void addLosses(double amount, Distance& d);

	double getLosses();

};



#endif
