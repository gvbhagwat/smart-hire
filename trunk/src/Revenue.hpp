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

	Revenue( const Revenue& other);

	
	/**
	 * add the profitable income
	 * @param directly specify the amount
	 */
	void addEarnings(double amount);

	/**
	 * add to the profitable income calcuated by the metering model
	 * @param distance travelled recently
	 */
	void addEarningsByDistance(int metres);

	/**
	 * @return the earnings
	 */
	double getEarnings();

	/**
	 * add to the losses
	 * @param directly specify the amount
	 */
	void addLosses(double amount);


	/**
	 * add to the losses by distance travelled as per the metering model
	 * @param specify the distance travelled
	 */
	void addLossesByDistance(int metres);


	/**
	 * @return losses
	 */
	double getLosses();

	/**
	 * @return losses + revenue
	 *
	 */
	double getTotalRevenue();


};



#endif
