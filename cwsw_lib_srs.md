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
| <a name="SR_LIB_0001">SR_LIB_0001</a>	| Determine initialization status		| The Component shall provide an API for determining initialization status.						| Draft		| N/A			| (none)	|
| <a name="SR_LIB_0003">SR_LIB_0003</a>	| Initialize API						| The Component shall provide an API for initializing the component.							| Draft 	| N/A			| (none)	|
| <a name="SR_LIB_0004">SR_LIB_0004</a>	| Responsibilities of Initialize method | The Initialize method shall set the component's operating internal state to initial status.	| Draft		| N/A			| (none)	|


### Critical Sections / Protected Regions

#### Provide Critical Section API

| ID 									| Title 								| Description 																				| Status 	| Trace From	| Comment 	|
| :---:									| :---									| :---																						| :---		| :---			| :---		|
| <a name="SR_LIB_0002">SR_LIB_0002</a>	| Enable Critical Section				| The Component shall provide an API for entering a Critical Section or Protected Region.	| Draft		| (tbd)			| (none)	|

<br>
