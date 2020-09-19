/** @file
 *	@brief	Stop Light State Machine.
 *
 *	Description:
 *	@note This file is a **template** to use as the basis for instantiation in a "real" SME. As such,
 *	this file does not compile and is not intended to compile. instead, it has the stuff in it that
 *	you'll need to modify for the instantiation.
 *
 *	The design is such that you'll probably want a fairly small, constraint SM to control - the
 *	vision we put into play was to control a stoplight, and/or read and debounce hardware buttons.
 *	Larger / nested state machines can easily be accommodated by using SMEs that control sub-SMEs.
 *
 *	\copyright
 *	Copyright (c) 2020 Kevin L. Becker. All rights reserved.
 *
 *	Created on: Jun 23, 2020
 *	@author Kevin L. Becker
 */

// ============================================================================
// ----	Include Files ---------------------------------------------------------
// ============================================================================

// ----	System Headers --------------------------

// ----	Project Headers -------------------------
#include "tedlos.h"		/* Event queue this SME uses. In the Template, this is TEDLOS, but this is not intended in any way to bias the implementation in your project. */

// ----	Module Headers --------------------------
#include "cwsw_sme.h"


// ============================================================================
// ----	Constants -------------------------------------------------------------
// ============================================================================

/** States for this State Machine.
 *	You will want to identify your own states and their names. This enumeration shows only one way
 *	to do it, and is pulled from the demonstration app (which implements one single-direction green-
 *	yellow-red stop light).
 */
typedef enum eSmStates { kStateNone, kStateRed, kStateGreen, kStateYellow } tSmStates;


// ============================================================================
// ----	Global Variables ------------------------------------------------------
// ============================================================================

/* proposed naming policy:
 * for public symbols that need to be public only for OS purposes, the symbol should have a
 * component prefix, followed by an identifier for that object, followed by its purpose. For timers,
 * this might be "StopLite_tmr_SME". The task might be "StopLite_tsk_SME".
 *
 * I have a desire that all timers should be grouped together in the map file when sorted by name,
 * likewise all task functions, but the same sort of list can be had by grepping *_tmr_*.
 */
tCwswSwAlarm	MyComponent_tmr_SME = {
	/* .tm			= */tmr20ms,			//!< timer maturation time.
	/* .reloadtm	= */tmr20ms,			//!< timer reload value.
	/* .pEvQX		= */&tedlos_evqx,		//!< Event queue for this SM. For the demo, we used the OS event queue, but this is not required.
	/* .evid		= */evStoplite_Task,	//!< Event ID posted upon timer maturation.
	/* .tmrstate	= */kTmrState_Enabled	//!< If the timer's not enabled, the alarm will not mature, and as a consequence, the task will not run.

};


// ============================================================================
// ----	Module-level Variables ------------------------------------------------
// ============================================================================

// this next variable is a standard part of the template. update it to point to your state timer.
static ptCwswSwAlarm const pMyTimer = &StopLite_tmr_SME;


// ============================================================================
// ----	State Functions -------------------------------------------------------
// ============================================================================

#if 0
/* the individual states are similar to a normal event handler, but return a value and take pointers.
 * - each state is responsible for maintaining its own internal state.
 * 	 normally, this means the state must auto-execute its own on-entry action and then transition to
 * 	 normal operation. upon exit (for us, maturation of its internal timer or receipt of a quit
 * 	 event or a go-to-other-color event), it must auto-execute its own at-exit action.
 * - each state knows how to "guard" each transition event.
 * - each state must handle its own internal reactions.
 * 	- in this implementation, all events are associated to the SME at the OS level, and the SME will
 * 	  call the correct state handler with the passed event.
 */
static tStateReturnCodes
StateRed(ptEvQ_Event pev, uint32_t *pextra)
{
	// this var is part of the template and this definition + initialization line should not be touched.
	static tStateReturnCodes statephase = kStateUninit;
	static tCwswClockTics tmrRedState = 0;	// this state's timer
	static tEvQ_EventID evId;				// used to return exit reasons 1 & 2

	/* this statephase management differs from that of the template version, for the following:
	 * - i prefer to have the default behavior assertively act to keep itself in the same state;
	 *   this would be similar to an "inhibitor" for a state that wants to change;
	 * - it seems simpler to me to adjust the statephase var in only one place, than the multiple
	 *   places where it's done in the template.
	 */
	switch(statephase++)
	{
	case kStateUninit:	/* on 1st entry, execute on-entry action */
	case kStateAbort:	/* upon return to this state after previous normal exit, execute on-entry action */
	default:			/* for any unexpected value, restart this state. */
		evId = pev->evId;
		Set(Cwsw_Clock, tmrRedState, tmr1000ms);
		statephase = kStateOperational;
		// state-specific behavior
		puts("RED on");
		break;

	case kStateOperational:
		if(pev->evId != evStoplite_Task)
		{
			// event only, no guard, for this transition.
			// update the exit reason1
			evId = pev->evId;
		}
		else if( Cwsw_GetTimeLeft(tmrRedState) > 0 )
		{
			// not all transition inhibitors are actively inhibiting; do the default action here,
			//	including any in-state reactions.
			--statephase;
		}
		break;

	case kStateExit:
		/* the at-exit behavior CAN NOT fail. it must be an atomic action that is failsafe. */
		// manage the state machine: set exit reasons (statephase needs to be > exit state, which it already is)
		pev->evId = evId;
		pev->evData = 0;
		*pextra = kStateRed;	// update argument to transition function

		// perform state-specific actions
		/* (no state-specific exit actions here) */
		break;
	}

	// the next line is part of the template and should not be touched.
	return statephase;
}
#endif


#if 0
static tStateReturnCodes
template_StateHandler(ptEvQ_Event pev, uint32_t *pextra)
{
	// this var is part of the template and this definition + initialization line should not be touched.
	static tStateReturnCodes statephase = kStateUninit;

	/* it is quite common for timer maturation to provoke an exit transition. if you define a simple
	 *	timer like this, you can poll it for expiration. the other alternative would be to define an
	 *	alarm, and use Cwsw_SwAlarm__Init() to arm it. then, you'd also have the option of having
	 *	the alarm post an event upon maturation; the tradeoff is that you need to call
	 *	Cwsw_SwAlarm__ManageTimer() in your default action, if you don't add the timer to the list
	 *	of alarms managed by the OS, or if your SME doesn't manage the timers - but remember, if you
	 *	define a local-to-this-function alarm, it's not available externally for anyone else to
	 *	manage.
	 */
	static tCwswClockTics tmrMyStateTimer = 0;

	// used to hold the exit reasons 1 & 2
	static tEvQ_EventID evId;

	switch(statephase)
	{
	case kStateUninit:	/* on 1st entry, execute on-entry action */
	case kStateAbort:	/* upon return to this state after previous normal exit, execute on-entry action */
	default:			/* for any unexpected value, restart this state. */
		/* the on-entry action could be
		 * - a separate function, or as we've done here,
		 * - a list of actions within the case.
		 */
		/* the on-entry behavior does not care about what event was passed to this function. while
		 * nothing prevents you from inspecting the incoming data, i believe this would deviate from
		 * standard UML state machine behavior. and having just said that, we're saving the incoming
		 * event ID as the default for exit reason 1.
		 */
		evId = pev->evId;	// save exit Reason1
		/* start my state timer. if your state doesn't need a timeout exit, you can kill this line.
		 * note: the period of the state alarm, must be larger than the periodicity of the SM engine;
		 * if the timeout of the state alarm is less than the rate at which the SME is called, it
		 * will always mature with every call to the SME.
		 */
		Set(Cwsw_Clock, tmrMyStateTimer, tmr1000ms);

		// unilaterally set statephase to normal. this is a nop for the premiere run, but necessary all other use cases
		statephase = kStateOperational;

		break;

	case kStateOperational:
		/* normal state behavior here, including handling in-state reactions to events
		 *	if there is a guard condition, evaluate that here.
		 */

		// add here, any other exit reasons not covered by in-state reactions above.
		// 	IF you need to override the default event that provokes the exit from this state, update
		//	`evId` here.
		//	be sure to increment statephase so as to execute the exit action.

		// if your state doesn't have a timer, you can eliminate this if() clause.
		if( Cwsw_GetTimeLeft(tmrMyStateTimer) <= 0 )
		{
			++statephase;	// if the timer's expired, execute the exit action the next time we're called.
		}
		break;

	case kStateExit:
		// for this edition of this state, no state-specific exit action is required.
		//	let the caller (normally the SME) know what event and what guard provoked the change.
		pev->evId = evId;	// save exit reason 1 (event that provoked the exit)
		pev->evData = 0;	// save exit reason 2 (no assigned purpose, use for your own purposes)
		*pextra = 0;		// save exit reason 3 (no assigned purpose, use for your own purposes)
//		++statephase;		// normally, the caller should know that a return code of kStateExit denotes the normal
							//	completion of this state. if you invalidate statephase, the caller should interpret
							//	that as a non-normal exit.
		break;
	}

	// the next line is part of the template and should not be touched.
	return statephase;
}
#endif

