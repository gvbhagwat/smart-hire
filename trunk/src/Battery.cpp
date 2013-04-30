#include "Battery.hpp"
#include "sim.hpp"

/**
 * Constructor
 *
 * @param initial charge.. determined by BATTERY_MAX_CHARGE sim parameter
 * @param minimum permissible charge determined BATTERY_DEPTH_OF_DISCHARGE parameter
 * @param rate by which discharge must happen according to distance travlled
 */
Battery::Battery(double pinitialCharge, double pdepthofDischarge, double pdischargePerMetre):
		charge(pinitialCharge),depthOfDischarge(pdepthofDischarge), dischargePerMetre(pdischargePerMetre){
	// initialization is counted as recharge				
	rechargeCount = 1;
}


/**
 * @return charge left
 */
double Battery::getCurrentCharge(){
	return charge;
}

/**
 * @return min charge possible
 */
double Battery::getDepthOfDischarge(){
	return depthOfDischarge;
}


/**
 * @return rechargeCount
 */
double Battery::getRechargeCount(){
	return rechargeCount;
}

/**
 * recharges battery to MAX_CHARGE and increments the count to 1
 *
 */
void Battery::rechargeBattery(){
	charge = BATTERY_MAX_CHARGE;
	rechargeCount++;
}

/**
 * @param amount
 * @return charge left
 */
double Battery::dischargeBattery(double amount){
	charge -= amount;
	return charge;
}

/**
 * The simplest model adapted is linear discharging rate per metre the
 * car travels
 *
 * @param the distance traveled by the vehicle
 * @return charge left
 */
double Battery::dischargeBatteryByDistance(int metres){
	double amount = dischargePerMetre * metres;
	return dischargeBattery(amount);
}

