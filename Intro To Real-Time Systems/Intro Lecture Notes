# Introduction to Real-Time Systems
## “Any processing system that interacts with its environment in time scales dictated by the needs of that environment”
Different from RTOS (Real-time operating system) which supports the construction of real-time systems

### Covers a wide range of applications e.g.
	- Airline seat reservations
	- Online order processing
	- Communications
		- Telecoms(mobile phones, set-top boxes, PDA’s, ect)
		- Networking (net hubs, switches, ect)
- Process Control
	- Oil industry: refining, petrochemical
	- Utilities: Gas, Electricity, Water.
- Embedded microprocessor systems
	- Computer peripherals (printers, disks, mice, keyboards)
	- White goods controllers (washing machines, ovens, ect)
	- Toys
	- Automotive systems (ABS, engine management, ect)

## Feedback
- Stresses the importance of the ENVIRONMENT
	- Designer must know the target application and its associated operational environment
- Fails to emphasize the FEEDBACK nature of the real-time system.

## Feedback Systems
Computer and Environment send signals between each other to solve problems.
- This has serious implications for TESTING
	- Can I prompt the environment to generate precise timed sequences actions?
- Much of the early literature on Real-Time Systems relates to business systems with emphasis on
	- Enquiry or transactional processing
	- logical file design
	- System integrity and reliability
	- System recovery

- They exhibit what is referred to as ‘soft; discrete feedback
	- e.g. order processing system

- Many of these ideas are equally applicable to ‘engineering type real-time systems’.

## Distributed Process Control System
- Both Require
	- A central database with a secure access mechanism
	- A protocol between the central machine and the local data collection units.
	- An error recovery mechanism to avoid catastrophic failure.
	- To work within external timing constraints
		- SOFT: Timings are NOT very critical
		- HARD: Timings are very critical

## Soft/Hard Systems
- *Soft* realtime systems
	- times are quite important
	- missed or extended deadlines are acceptable

The soft real-time definition allows for frequently missed declines, and as long as tasks are timely executed their results continue to have value.
Completed tasks may have increasing value up to the deadline and decreasing value past it.

- *Hard* Real-time systems e.g. ‘fly-by-wire’ aircraft systems
	- times are VERY important
	- missed or extended deadlines may give problems

The hard real-time definition considers missed dealing to be a system failure. This scheduling is used extensively in mission critical systems where failure to conform to timing constraints results in a. Loss of life or property.

## data Quality

- Most real-time systems have a mix of hard and soft activities 
	- Soft activities are likely to outnumber hard activities
	- Hard activities are more  difficult to design and test out.
- Relates to an attribute  of data
	- FRESHNESS/STALENESS
		- The quicker data becomes ‘stale’ the harder the system, e.g.
			- Temperature of this room
			- Pitch of a fighter aircraft

## Features of Real Time Systems

- There are 3 features that differentiate real-time systems from conventional systems

*Critical timing*
- Basic speed
- Response
- Data rates

*Interface to the real world*

*Critical Operation*
- Reliability
- Error Handling

## Critical Timing - Basic Speed

- Relevant to PERIODIC activities (synchronous/repetitive)
- Does the computer have sufficient computational power to set required deadlines e.g. consider the calculation of a control action.

- Sample Rate
	- defines allowed compute time

- if (actual compute time > allowed compute time)
	- unintentional modification of sample rate
	- implies different control action (could be bad)

## Critical Timing - Basic Speed

- Potential solutions
	- Use faster computer hardware
		- realistic with rate of evolution of modern hardware. 
- Add fast peripheral hardware
	- e.g. graphics, wireless, FPGAs
	- costly, specialized.

- Use different algorithms
	- Use best algorithm possible
	- important aspect of DESIGN

- Trade-off memory for compute time
	- related to algorithm selection
	- speed | memory storage | accuracy

- Modify coding
	- Often architecture dependent
	- Last resort
	- A good designer should know something about the tools he is using, e.g. the compiler

## Critical Timing - Response

- Relevant to APERIODIC activities (asynchronous/sporadic)
	- the ability to react to an event within specified scales
	- or
	- the time between an event occurring and the computer initiating a suitable response

- To confuse the situation
	- A system is likely to have to deal with a number of possible events rather than just one.
	- These events will have a relative importance i.e. a PRIORITY
	e.g. in a modern passenger jet the following will have a set priority
		- failure of primary hydraulic circuit
		- failure of cabin air-conditioning 
		- failure of emergency lightning circuit
	- Each can tolerate different response times, and therefore can be handled on different timescales.

- Priority may be time and situation dependent
	- If main lighting circuit failed then failure of emergency lighting circuit will assume greater importance.

- Response will be hardware dependent 
	- Events are often tied to interrupts
	- Response = F(interrupt response, …….)
	- Problems with modern computer architectures
		- Cache system
		- Dynamic instruction re-ordering
	- Accurate calculation may be impossible!

- Response will be software dependent
	- The software path between an event occurring and a valid response being generated can be lengthy. Many (unknown!) layers of code may be involved.
	- Underlying operating systems will have a major impact on response capability.
	- General-purpose OS (Unix/Linus) poor in this respect.

- For the designer there will be a number of trade-offs
	- response | speed | cost | safety margins
Stresses the need for GOOD DESIGN.

## Critical Timing - Data Rates

- Important factor in ‘sizing’ a compute system.
	- Feedback loops
		- what sample rates are neccessary?
	- digitized analogue signals
	- data storage requirements

- Trend is towards increasing data rates
	- more system feedback
		- more sensors and more actuators
			- E.g. self-driving cars
	- more accurate sensors
		- 8-bits -> 10 bits -> 12 bits -> …
	- Use of line and area imaging sensors
		- Optical mice, distance detectors, mobile phones!

## Features of Real-Time Systems
### REMINDER
- There are 3 features that differentiate real-time systems from conventional systems

	- *Critical Timing*
	- *Interface to the real world*
	- *Critical Operation*

## Real-World Interface
- Hardware
	- Input/Output Interface units, digital + analogue
	- Well defined area with good design methods and good off-the-shelf products.

- Software
	- *Computer*
		- Digital, discrete, using 2-state components
		- Noise free
		- Predictable, deterministic, repeatable
		- Linear
		- Sequential, synchronous devices
	- *Real-Wolrd*
		- Analogue, continuous variables
		- Noisy
		- Non-deterministic
		- Non-linear
		- Asynchronous: events may only be predicted by probability
			- keyboard press
			- alarm condition
			- time to perform an operation

*REAL TIME SYSTEMS ATTEMPT TO MATCH THERE TWO INCOMPATIBLE STRUCTURES*

## The process view of a real-time system
- The key to tackling such problems is to view systems as an aggregate set of parallel-acting, co-operating processes.
- Consider a “Supermarket” system::
	- Consists of 4 processes
		- Delivery of goods
		- Warehousing of goods
		- Stacking of shop shelves
		- Customer purchase of goods

- Need to consider
	- Interactivity storage to smooth cooperation
	- Asynchronous nature of activities

## Features of Real Time Systems
### REMINDER
- There are 3 features of real time systems that differentiate real time from conventional systems
	- Critical Timing
		- Basic Speed
		- Response
		- Data rates

	- Interface to the real world

	- Critical Operation
		- Reliability
		- Error handling
	

## Critical Operation - Reliability

- Hardware Realiability
	- Well established area with good mathematical tools.
	-  Driven by space, military and industrial requirements

- Software reliability
“Probability that a given software program operates for some given time without software error, on a machine for which it was designed, given that it is used within design limits.”
	- Poorly designed subject area: What is a software error?
	- Problem: Software does not fail like hardware.
	- Real-time systems introduce a new class of errors
		- Time dependent interaction errors (deadlock, etc).
		- Complicates the testing process.
	- No general mathematical techniques.

FYI - DEADLOCK is a common problem in multiprocessing systems, parallel computing and distributed systems, where software and hardware locks are used to handle shared resources and implement process synchronization.

## Critical Operation - Error Handling

- In a real-time system an error cannot be ignored.
- In a totally automatic system there must be contingency plans for all errors. Complicates the design process.
- System must be able to handle multiple errors in some form of priority structure.
	- Who defines the priorities?
	- Will they change? Are they context dependent?
- Modern languages (e.g. Ada) are introducing code structures to assist error handling strategies.
- System design becomes so important. Consider the consequences of differing reaction modes
	- Don’t react - DANGER
	- Under-react - DANGER
	- Over-react - Waste resources, cost implication








