/** @file
 *	@brief	Core behavior for State Machine Engine.
 *
 *	\copyright
 *	Copyright (c) 2020 Kevin L. Becker. All rights reserved.
 *
 *	Created on: Jun 28, 2020
 *	@author Kevin L. Becker
 */

// ============================================================================
// ----	Include Files ---------------------------------------------------------
// ============================================================================

// ----	System Headers --------------------------

// ----	Project Headers -------------------------

// ----	Module Headers --------------------------
#include "cwsw_sme.h"


// ============================================================================
// ----	Constants -------------------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Type Definitions ------------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Global Variables ------------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Module-level Variables ------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Private Functions -----------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Public Functions ------------------------------------------------------
// ============================================================================

/** Search for the next state.
 *	If found, execute transition function, if any specified.
 */
pfStateHandler
Cwsw_Sme_FindNextState(
	ptTransitionTable	pTblTransition,		// 1st row of transition table
	uint32_t			szTblTransition,	// size in rows of transition table
	pfStateHandler		currentstate,
	tEvQ_Event			ev, 				// 1st two exit reasons
	uint32_t 			extra)				// 3rd exit reason
{
	pfStateHandler nextstate = currentstate;
	uint32_t tblidx = szTblTransition;
	while(tblidx--)
	{
		if(pTblTransition[tblidx].pfCurrent == currentstate)
		{
			if(pTblTransition[tblidx].reason1 == ev.evId)
			{
				// this might a domain-specific edit; in the button-reading component, we're using
				//	the evData field (reason2) to represent the button being acted upon, and we have
				//	enough resolution available in the reason3 field, so we don't need to use the
				//	`reason2` comparison.
			//	if(pTblTransition[tblidx].reason2 == ev.evData)
				{
					if(pTblTransition[tblidx].reason3 == extra)
					{
						nextstate = pTblTransition[tblidx].pfNext;
						if(pTblTransition[tblidx].pfTransition)
						{
							(void)printf("Transition %i selected\n", tblidx);
							pTblTransition[tblidx].pfTransition(ev, extra);
						}
						break;
					}	// reason3
				}		// reason2 - ignored since reason2 now carries the button
			}			// reason1
		}
	}

	return nextstate;
}


/** CWSW State Machine Engine task.
 *	This is the core SM Engine. It is intended to be called from the SME of a specific state machine.
 *
 *	@param[in] pTblTransitions 	The transition table of the calling SM.
 *	@param[in] sztbl 			Size of the caller's transition table.
 *	@param[in] CurrentState 	The current state.
 *	@param[in] ev 				Event parameter passed to the calling SME by the event dispatcher.
 *	@param[in] extra 			Extra parameter passed to the calling SME by the event dispatcher.
 *
 *	@returns The next state. If NULL, there is no next state and the caller should take appropriate action.
 */
pfStateHandler
Cwsw_Sme__SME(
	ptTransitionTable pTblTransitions, uint32_t sztbl,	// individual component's transition table
	pfStateHandler CurrentState,
	tEvQ_Event ev, uint32_t extra)
{
	pfStateHandler nextstate = CurrentState;
	tStateReturnCodes rc = kStateUninit;

	if(CurrentState) 	{ rc = CurrentState(&ev, &extra); }

	if(rc > kStateExit)
	{
		nextstate = Cwsw_Sme_FindNextState(pTblTransitions, sztbl, CurrentState, ev, extra);
	}
	return nextstate;
}
