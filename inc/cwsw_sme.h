/** @file
 *	@brief	Public API for the CWSW State Machine Engine (SME).
 *
 *	\copyright
 *	Copyright (c) 2020 Kevin L. Becker. All rights reserved.
 *
 *	Created on: Jun 23, 2020
 *	@author Kevin L. Becker
 */

#ifndef SME_H
#define SME_H

// ============================================================================
// ----	Include Files ---------------------------------------------------------
// ============================================================================

// ----	System Headers --------------------------

// ----	Project Headers -------------------------
#include "cwsw_swtimer.h"		/* tCwswSwAlarm */
#include "cwsw_evqueue_ex.h"	/* The SME is built on top of the event queue */

// ----	Module Headers --------------------------


#ifdef	__cplusplus
extern "C" {
#endif


// ============================================================================
// ----	Constants and Type Definitions ----------------------------------------
// ============================================================================

/** Return codes for the various State handlers.
 *	Each State Machine state has an internal lifetime, beginning with initialization (entry action),
 *	spending most of its time in the normal phase, and dying with an exit action. The values listed
 *	here are used internally by the state, and returned by the state function to communicate with
 *	the SME.
 */
typedef enum eStateReturnCodes {
	kStateUninit,		//!< initialization step for each state. It is an error if the state function returns this value.
	kStateOperational, 	//!< the lion's portion of the time, this is the expected return value from each state.
	kStateExit,			//!< the state is going to execute its exit action at the next invocation.
	kStateFinished		//!< The state has finished executing its exit action and has relinquished "current state" status.
} tStateReturnCodes;

/** Button Identifiers.
 *	This board
 * @param ev
 * @param extra
 * @return
 */

/** Prototype for the various State Machine handlers.
 *	The individual states in a CWSW SME are embodied by a function that looks similar to a CWSW event
 *	handler, except that it returns an error code. In this vision, the engine itself is a normal
 *	CWSW event handler, but to manage the SM, it needs to know details about the exit status of each
 *	state.
 *
 *	The SME itself (message pump) is responsible for
 *	- calling the current function;
 *	- determining the transition from one state to another;
 *	- calling the transition function, if defined.
 *
 *	The SME can be called by any method that dispatches CWSW events, but the design intent and the
 *	assumed context is that an associated alarm posts the event that calls the SME through its
 *	associated handler.
 *
 *	As designed, the SME's event queue is that of the OS or main dispatcher, but as this can get
 *	unmanagable for big projects, there's no problem with having each SME use its own event queue,
 *	if that's what's most expedient.
 *
 *	@param [in,out]	ev		Event from event dispatcher, passed via the SME. The individual state
 *							handlers update this with information regarding the operation of that state,
 *							which is in turn used by the SME to manage the SM.
 *	@param [in,out]	extra	Extra data from the event dispatcher, passed via the SME. The individual
 *							state handlers update this with information regarding the operation of
 *							that state, which is in turn used by the SME to manage the SM.
 *
 *	@returns	Code that indicates the state should remain the current state, if the state ended
 *				normally, or if there was an abnormal exit.
 */
typedef tStateReturnCodes (*pfStateHandler)(ptEvQ_Event ev, uint32_t *extra);


/** State transition table.
 *	In order for the SME to know how the states are connected together, it needs some metadata.
 *	This table provides that.
 */
typedef struct sTransitionTable {
	pfStateHandler	pfCurrent;	// current state
	uint32_t		reason1;	// normally, the event evId field, reused as a partial exit reason
	uint32_t		reason2;	// normally, the event evData field, reused as a partial exit reason
	uint32_t		reason3;	// normally, the "extra" argument to the state function, reused as a partial exit reason
	pfStateHandler	pfNext;		// next state
	/* the transition function has the same signature as an event handler. since in concept, it
	 * could be called in the transition of multiple states, the parameters to it are used to pass
	 * contextual information, not the parameters normal to event usage.
	 */
	ptEvQ_EvHandlerFunc	pfTransition;
} tTransitionTable, *ptTransitionTable;


// ============================================================================
// ----	Public Variables ------------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Public API ------------------------------------------------------------
// ============================================================================

extern pfStateHandler Cwsw_Sme_FindNextState(
	ptTransitionTable	pTblTransition,		// pointer to 1st row of transition table
	uint32_t			szTblTransition,	// size in rows of the transition table
	pfStateHandler		currentstate,
	tEvQ_Event			ev, 				// mis-appropriating an event because it happens to be a container suitable for the 1st two exit reason types
	uint32_t 			extra);				// mis-appropriating the "extra" field for the same reason - 3rd exit reason

extern pfStateHandler
Cwsw_Sme__SME(
	ptTransitionTable pTblTransitions, uint32_t sztbl,	// individual component's transition table
	pfStateHandler CurrentState,
	tEvQ_Event ev, uint32_t extra);

#ifdef	__cplusplus
}
#endif

#endif /* SME_H */
