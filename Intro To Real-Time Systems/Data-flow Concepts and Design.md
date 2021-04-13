# Dataflow Concepts and Design
## Hardware Considerations
- The abstract nature of hardware has changed little over the years. The only differences are:
	- Raw speed.
	- Raw processing power.
	- Implementation technology.
	- Architecture.
	
- Hardware is much easier to design.
	- LSI/VLSI tools and methods

- Hardware is amenable to an established set of design techniques that have been proven in the field.

- In many cases, hardware selection is not critical.
	- Only critical for specialized applications.

- The real problem is SOFTWARE

## Process Model

- The underlying concept that separates Real-Time Systems from standard sequential systems is:

	- the idea of a PROCESS or a TASK describe PARALLEL activities.
(Both will be used interchangeably)
(Also similar to THREAD)

	- A PROCESS is defined as
“A single activity that is executable by a set of sequentially executed operations. (I.e. a single program)”

- How do they arise in practice?

## Process Model

“A single activity that is implemented by a set of sequentially executed operations. (i.e. a single program).”

- As with all forms of software design we must adopt a decomposition view::
					1 Large sequential unit
							 |
							\/
				’n’ small cooperative sequential units
							|
						       \/	
					’n’ PROCESSES

Example
- 	Closed loop control provides a mechanism to maintain a variable within               define limits.

Example system 
- Requirement 
	- Provide digital control of a single loop
(E.g. temperature of a fluid vat).
	- Allow interaction at the computer terminal to check and change controller parameters (e.g. PID constants)
	- Provide a facility to ‘log’ variables on the printer at selected times.
	

#Stage1: Controller loop only
	- Loop to run at a CONSTANT sample rate
	- Assume that the clock signal is available
	- Relatively simple to code
		- Microcontroller have timing subsystems

#Stage2: Controller loop + Keyboard Input
	- This solution has 2 major problems:
		- Time spent reading a line of keyboard data could cause a change to the control loop sample period. Hence, it could compromise the loop stability.
		- An infinite delay in keyboard data input could cause the complete blocking of control loop processing. Contravenes the property of ‘LIVENESS’.

LIVENESS - “if something is supposed to happen then eventually it should happen”.

- No activity should be indefinitely delayed.
- does not imply that it will operate correctly.

#Stage3 :: Full system
- Go through lecture diagram
- Problem - Activities that are UNRELATED in terms of their purpose, e.g. keyboard input and data logging, are forced to be related by the necessary sequencing of the complete program. This form of connection is called CONTROL COUPLING
	- Implies that TIMING and EROR problems can easily be populated through the system e.g. keyboard input can cause sample-time jitter.
- It is difficult to achieve the required features of Real-Time operation
	- Guaranteed response times
	- Allocation of priority between the activities to cope with sporadic events.
To change the ordering of activities required re-programming which may have side effects that are difficult to predict.

- The essential point of this technique is its ad-hoc nature. However, with modifications to impose some structure, the method has been used to implement some small-scale commercial and military systems using a system called a:  CYCLIC EXECUTIVE

## Cyclic Executive
- Split requirements into small repetitive activities.
- Synchronize the sequencing of these activities to a clock signal.
- A cyclic executive is an alternative to a real-time operating system. 
- It is a form of cooperative multitasking. The sole task is typically realized as an infinite loop in main(). Eg in C.

- All individual activities should complete within a ‘slot’. Otherwise, the timing structure will be distorted.
- Repetitive operations at different rates can be handled by careful design of the slot allocation. However, changes to sample rates may be difficult to incorporate. 
- Adding new activities may cause problems.

- The cyclic executive structure has the general form (pseudo-code):

for(;;) {
	wait_for_timing_signal();
	task1();
	wait_for_timing_signal();
	task2()
	…
}


- It repeats forever, goes through each task.

Using the keyboard example:
- Each function would be programmed as required. 
- The handling of the time information would be difficult, I.e. to get the *loop_sample* routine executed at the correct repetitive rate.


# To be continued





