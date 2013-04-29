#ifndef BATTERY_HPP
#define BATTERY_HPP

/*
 * type which will probably belong to the simulator's event queue.
 * Unhandled events with the least time-stamp are handled first.
 */

class Battery {
	
	protected:
		
	/* Battery charging left*/
	double charge;

	/* Battery left left*/
	double depthOfDischarge;
		
	/* Battery left left*/
	public:

	double getCurrentCharge();

	double consumeBattery(double dischargeAmount);

	void rechargeBattery();


};



#endif
