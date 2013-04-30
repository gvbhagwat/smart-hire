#ifndef DISTANCE_HPP
#define DISTANCE_HPP

/*
 * type which will probably belong to the simulator's event queue.
 * Unhandled events with the least time-stamp are handled first.
 */

class Distance {
	
	protected:

	/* Metered Distance travelled  (in metres) */
	unsigned int metered;

	/* Non-metered Distance travelled  (in metres) */
	unsigned int wastage;

	public:

	Distance();

	Distance(const Distance& other);
	
	void addMeteredDistance(int metres);

	unsigned int getMeteredDistance();

	void addWastage(int wastage);

	unsigned int getWastage();

	unsigned int getTotalDistance();
	
};



#endif
