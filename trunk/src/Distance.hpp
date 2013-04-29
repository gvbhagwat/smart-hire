#ifndef DISTANCE_HPP
#define DISTANCE_HPP

/*
 * type which will probably belong to the simulator's event queue.
 * Unhandled events with the least time-stamp are handled first.
 */

class Distance {
	
	protected:

	/* Metered Distance travelled  (in metres) */
	double metered;

	/* Non-metered Distance travelled  (in metres) */
	double wastage;

	public:

	Distance();

	void addMeteredDistance(double metres);
	double getMeteredDistance();

	void addWastage(double wastage);
	double getWastage();

	double getTotalDistance();
	
};



#endif
