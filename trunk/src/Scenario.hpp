#ifndef SCENARIO_HPP
#define SCENARIO_HPP

#include "Event.hpp"

/**
 * A general scenario to be simulated. This abstract class
 * needs to be implemented by particular simulation scenarios.
 */
class Scenario 
{

	protected:
		EventList& eventList;

	public:
		/**
		 * Create a scenario with with a reference to the event list
		 * used by the simulation.
		 */
		Scenario(EventList& eventList) : eventList(eventList) {}

		/* Virtual descructor so that child classes can perform finishing */
		virtual ~Scenario() {};
		
		/* Update statistics, if necessary */
		virtual int updateStatistics(double time) = 0;

};


#endif
