/**
 * @author	: Gaurav Bhagwat
 * @version	: 1.0
 *
 */

#ifndef BATTERY_HPP
#define BATTERY_HPP

/**
 * Models the battery of the car. it captures the discharging and recharging functions 
 * to be used and also records the rechargeCount. 
 */
class Battery {
	
	protected:
		
	/// @brief Battery charging left
	double charge;

	/// @brief minimum charging that must be always kept.
	double depthOfDischarge;

	/// @brief discharging rate as the car travels. A simplistic model linear model used. Many complex models can be applied later.
	double dischargePerMetre;

	/// @brief number of times the batteries have been swapped and kept for recharging.
	unsigned int rechargeCount;

	public:

	/**
	 * @param initial charge
	 * @param minimum permissible recharge
	 * @param battery consumption 
	 */
	Battery(double initialcharge, double depthOfDischarge, double dischargePerMetre);

	/**
	 * @return current rate of charging 
	 */
	double getCurrentCharge();

	/**
	 * @return current rate of charging 
	 */
	double getDepthOfDischarge();

	/**
	 * @return total recharges happened
	 */
	double getRechargeCount();

	/**
	 * @param directly specifying the amount by which the discharging must occur
	 */
	double dischargeBattery(double dischargeAmount);

	/**
	 * @param specify the distance travelled and discharge the battery according to discharge model
	 */
	double dischargeBatteryByDistance(int metre);

	/**
	 * resets the battery level to 100% again and increments the rechargeCount
	 */
	void rechargeBattery();

};



#endif
