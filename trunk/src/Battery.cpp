#include "Battery.hpp"
#include "sim.hpp"


/**
 * @brief 
 *
 * @return 
 **/
Battery::Battery(){

	charge =BATTERY_MAX_CHARGE;
	depthOfDischarge = BATTERY_DEPTH_OF_DISCHARGE;
	dischargePerMetre = BATTERY_DISCHARGE_PER_METRE;

	rechargeCount = 1;
}

/**
 * @brief 
 *
 * @param other 
 *
 * @return 
 **/
Battery::Battery( const Battery& other):
		charge(other.charge), depthOfDischarge(other.depthOfDischarge),
		dischargePerMetre(other.dischargePerMetre), rechargeCount(other.rechargeCount){
}


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
 * @brief 
 *
 * @return 
 **/
double Battery::getDischargePerMetre(){
	return dischargePerMetre;
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

