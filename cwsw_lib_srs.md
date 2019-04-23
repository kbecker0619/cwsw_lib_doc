# Requirements: CWSW Library Component

\tableofcontents 

[TOC]

## Purpose of Component

The CWSW Library Component provides the foundation of the dependency tree for the CWSW suite of 
reusable software components. They are primarily intended for use in an embedded environment, but 
they may find utility in a variety of environments.

The Library component contains a minimal set of functions, with supporting User Defined Types, 
macros and function-like macros.

<br>

## Scope of Requirements

The requirements documented here cover functional and non-functional
requirements specific to the Library component.

<br>

## Requirements

### Operating State

| ID 									| Title 								| Description 																					| Status 	| Trace From	| Comment 	|
| :---:									| :---									| :---																							| :---		| :---			| :---		|
| <a name="SR_LIB_0000">SR_LIB_0000</a>	| Initialize API						| The Component shall provide an API for initializing the component.							| Draft 	| N/A			| |
| <a name="SR_LIB_0001">SR_LIB_0001</a>	| Determine initialization status		| The Component shall provide an API for determining initialization status.						| Draft		| SR_LIB_0000	| |
| <a name="SR_LIB_0002">SR_LIB_0002</a>	| Responsibilities of Initialize method | The Initialize method shall set the component's operating internal state to initial status.	| Draft		| SR_LIB_0000	| |
| <a name="SR_LIB_0003">SR_LIB_0003</a>	| Component's Uninitialized indication	| If executed prior to initialization, the features of the component that have stateful behavior by design, shall return an `Uninitilialized` indication.	| Draft | SR_LIB_0000	| "Return" could be via callback, component-level attribute, function output parameter, function return code, etc. |
| <a name="SR_LIB_0004">SR_LIB_0004</a>	| Component's Uninitialized behavior	| If executed prior to initialization, the features of the component that have stateful behavior by design, shall not change their operating state.			| Draft	| N/A	| SR_LIB_0000 |

<br>

### Tasking API

| ID 									| Title 								| Description 																					| Status 	| Trace From	| Comment 	|
| :---:									| :---									| :---																							| :---		| :---			| :---		|
| <a name="SR_LIB_0200">SR_LIB_0200</a>	| Tasking API							| The Component shall provide an API in support of OS tasks or threads.							| Draft		| N/A			| |

<br>

### Critical Sections / Protected Regions

| ID 									| Title 								| Description 																				| Status 	| Trace From	| Comment 	|
| :---:									| :---									| :---																						| :---		| :---			| :---		|
| <a name="SR_LIB_0300">SR_LIB_0300</a>	| Critical Section API					| The Component shall provide an API in support of Critical Sections, aka Protected Regions.| Draft		| N/A			| |
| <a name="SR_LIB_0301">SR_LIB_0301</a>	| Enter Critical Section API            | The Component shall provide an API for entering a Critical Section or Protected Region.	| Draft		| SR_LIB_0300	| |
| <a name="SR_LIB_0302">SR_LIB_0302</a> | Leave Critical Section API            | The Component shall provide an API for leaving a Critical Section or Protected Region.    | Draft     | SR_LIB_0300   | |
| <a name="SR_LIB_0303">SR_LIB_0303</a> | Critical Section Nesting Level: Incrementation    | The Component shall increment the Critical Section Nesting level for the requested protection type, with each invocation of the Enter Critical Section API, provided doing so will not violate counter constraints after incrementation.  | Draft | SR_LIB_0300 | |
| <a name="SR_LIB_0304">SR_LIB_0304</a> | Critical Section Nesting Level: Decrementation    | The Component shall decrement the Critical Section Nesting Level for the requested protection type, with each invocation of the Leave Critical Section API, provided doing so will not violate counter constraints after decrementation.  | Draft | SR_LIB_0300 | |
| <a name="SR_LIB_0305">SR_LIB_0305</a> | Critical Section Nesting Level: Data range        | The range of the Critical Section Nesting Counter(s) shall be from 0 to the value INT_MAX on the host system.   | Draft | SR_LIB_0300	| |
| <a name="SR_LIB_0306">SR_LIB_0306</a> | Critical Section Nesting Level, Invalid value     | If the Critical Section Nesting Level for the requested protection type is invalid, the Enter Critical Section API shall treat it as if it were at the floor (ambient, initialized) level. | Draft    | SR_LIB_0300 | |
| <a name="SR_LIB_0307">SR_LIB_0307</a> | Enter Critical Section Behavior, First Activation | If the Critical Section Nesting Level for the requested protection type is at the floor (ambient, initialized) count, upon activating the Enter Critical Section API, the Critical Section Protection mechanism specified by the argument shall be activated.   | Draft | SR_LIB_0300 | |
| <a name="SR_LIB_0308">SR_LIB_0308</a> | Enter Critical Section Behavior, Already Active   | If the Critical Section Nesting Level for the requested protection type is above the floor but still within the valid range, upon activating the Enter Critical Section API, no Enable Protection behavior shall be invoked.  | Draft | SR_LIB_0300 | |
| <a name="SR_LIB_0309">SR_LIB_0309</a> | Leave Critical Section Behavior, Already Active   | If the Critical Section Nesting Level for the requested protection type is above the floor but still within the valid range, upon activating the Leave Critical Section API, no Disable Protection behavior shall be invoked. | Draft | SR_LIB_0300 | |
| <a name="SR_LIB_0310">SR_LIB_0310</a> | Leave Critical Section Behavior, Last Deactivation| If the Critical Section Nesting Level for the requested protection type will be at the floor after decrementing, the Disable Protection behavior shall be invoked.    | Draft | SR_LIB_0300 | |

<br>
