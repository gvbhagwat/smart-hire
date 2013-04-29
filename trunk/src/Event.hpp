#ifndef EVENT_HPP
#define EVENT_HPP

#include <deque>
#include <queue>


class Event;
class EventOrdering;

/**
 * The EventList type is an alias for a priority queue of
 * Event objects ordered by their time-stamps (smallest first)
 */
typedef std::priority_queue<Event*,std::deque<Event*>,EventOrdering> EventList;


/**
 * The unit of discrete event simulation. Event is a generic
 * type which will probably belong to the simulator's event queue.
 * Unhandled events with the least time-stamp are handled first.
 */
class Event {
	
	protected:
		/* Time-stamp of the event's occurence */
		double time;

	public:
		/* Create a new event with given timestamp */
		Event(double time) : time(time) {}

		/* Returns the time-stamp of the event */
		const double getTime() { return time; }

		/* Handle this event */
		virtual void handle(EventList& eventList) = 0;
};


/**
 * Implements a comparator for Event objects .
 */
class EventOrdering {
	public:
		/**
		 * As our priority queue implementation is a max-heap, and
		 * we want the min-event to be removed first, we define our
		 * comparator to tell us which is greater instead of lesser.
		 */
		bool operator() (Event* e1, Event* e2)
		{
			return e1->getTime() > e2->getTime();	
		}
};

#endif
