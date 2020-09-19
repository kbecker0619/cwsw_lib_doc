# State Machine Engine

random, mostly unorganized thoughts. <br>
this is a scratchpad for ideation, not an official design document. <br>
tab chars: 4

## overall background
* coded to C99, primarily because
	* i want to use the standardized scalar types not available in C90
	* i want to be free to use C++-style comments
* however, since VS 2010 doesn't know C99, some things "look" closer to C90
* packaged in one repo, though broken into separate components.
* UT and documentation apply at the package level.

## Simple State
a simple state has
* internal variables (implies its own C file)
* entry action (no arguments)
  * has access to state's own unique attributes
* exit action (no arguments)
  * has access to state's own unique attributes

## Compound State (heirarchical)
* list of internal events and their associated reactions
  each "reaction" is a cwsw event handler
  * child / nested SMs are implemented by the event dispatcher - 
  * this implies that each state has its own event-association table

## State Machine
a SM is composed of {
* 1 or more states
* connections between states
}
the SME needs to know how the states are connected together

## State Machine Engine
state:	{
each state has the following attributes:
* guard functions
  * this replaces or stands in leiue of the UML's condition guard
  * a guard function is only called once an eligible exit event is received

internal reactions could be handled by an internal-event-association list, but could also be 
	handled within a specific switch case

to the SM engine, the event queue is the "normal" event queue, not the extended one, because it does
	its own things when an event is received
to the individual state, the list of internal reactions could be an extended queue

event -> guard(). if no guard, or guard returns TRUE, then d: updated by OS scheduler 	* unmanaged: unknown to OS, so not updated 	* managed: must be at least module-global, but can be static. 		? does this mean a function-local but static timer can be managed? 	* unmg: primarily envisioned to be driven within the module's task function 	* function-local, non-static timers can be created, but extra care must be taken to limit (for example) persistent effects (such as event-handler association) that would become invalid upon function exit 	* managed: no de-registration (?) 	  * no technical reason, but adds a lot of complexity to maintain list of active items 	  * should have a crc or some form of validity check 	    * should not include dynamic members in crc. primarily concerned about e.g. next-timer links, and if present, previous-timer links 		* a method needs to be available that will allow validity checking of "this" timer - e.g., if a function-local timer goes out of scope, then hopefully its memory will be overwritten "quickly" and the task could tell if the timer was corrupted or valid 		* if valid, then a re-linking of the timers would be done	
}


one row of a state machine descriptor:
when a state is transitioned into, the SME 
* calls the entry action
* calls the state function (w/ event)

when the SME receives an event:
* if the event is a transition event for the current state:
  * if there is a guard function, calls the guard (w/ event)
	* if the guard function returns FALSE, no action taken
  * if there is no guard, or if the guard returns TRUE
	* 
	
	




# Adding a real module to tedlos

Adding DI module to read the keyboard. On Windows, this will correlate keys `1`-`8` as an array of 8 buttons. On some of the dev kits I have, keys will be the physical buttons on that board.

## New task
~On DOS, we'll use `kbhit()` to detect if a key has been pressed, and purposely avoid grabbing the value the 1st time we see it, because we want to simulate debouncing a physical switch.~

_(can't get `kbhit()` to work from within Eclipse)_ Create a stupid simple textual input for debugging purposes: format is a binary value for a timer, then a string of 1s and 0s to represent bouncing contacts, followed by another time value, followed by more of the same.  in this string "2" represents Button #2, "3" is button 3, etc.  `0` is release of same.

* new event added to OS queue
* new alarm in new file
* new task 
in new file
