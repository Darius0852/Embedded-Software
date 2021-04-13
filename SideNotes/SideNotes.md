Frequently used terms in RTOS
1. Task: It is a piece of code that is schedulable on the CPU to execute.

2. Scheduler: It is responsible for selecting a task from the ready state list to the running state. Schedulers are often implemented so they keep all computer resources busy (as in load balancing).

3. Preemption: It is the act of temporarily interrupting an already executing task with the intention of removing it from the running state without its co-operation.

4. Context Switching: In priority-based preemption, the scheduler compares the priority of running tasks with a priority of ready task list on every systick interrupt. If there is any task in the list whose priority is higher than running task then context switch occurs. Basically, in this process contents of different tasks get saved in their respective stack memory.

5. Types of Scheduling policies:

Preemptive Scheduling: In this type of scheduling, tasks run with equal time slice without considering the priorities.
Priority-based Preemptive: High priority task will run first.
Co-operative Scheduling: Context switching will happen only with the co-operation of running tasks. Task will run continuously until task yield is called.​
6. Kernel Objects: For signaling the task to perform some work, the synchronization process is used. To perform this process Kernel objects are used. Some Kernel objects are Events, Semaphores, Queues, Mutex, Mailboxes, etc. We will see how to use these objects in upcoming tutorials.

From the above discussion, we have got some basic ideas about the RTOS concept and now we can implement the FreeRTOS project in Arduino. So, let's get started by installing FreeRTOS libraries in Arduino IDE.

