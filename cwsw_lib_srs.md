# Requirements: CWSW Library Component

\tableofcontents 

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

#### <a name="SR_LIB_0001">SR-LIB-0001  Determine initialization status

The Component shall provide an API for determining initialization status.

<br>

#### <a name="SR_LIB_0002">SR-LIB-0002	Initialize API

The Component shall provide an API for initializing the component.

The 
### Critical Sections / Protected Regions

#### Provide Critical Section API

##### <a name="SR_LIB_0003">SR-LIB-0003 Enable Critical Section

The Component shall provide an API for entering a Critical Section or Protected Region.

<br>
