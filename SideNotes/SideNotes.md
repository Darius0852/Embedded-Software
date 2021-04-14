# Useful Notes when learning RTOS

## Frequently used terms in RTOS
1. Task: It is a piece of code that is schedulable on the CPU to execute.

2. Scheduler: It is responsible for selecting a task from the ready state list to the running state. Schedulers are often implemented so they keep all computer resources busy (as in load balancing).

3. Preemption: It is the act of temporarily interrupting an already executing task with the intention of removing it from the running state without its co-operation.

4. Context Switching: In priority-based preemption, the scheduler compares the priority of running tasks with a priority of ready task list on every systick interrupt. If there is any task in the list whose priority is higher than running task then context switch occurs. Basically, in this process contents of different tasks get saved in their respective stack memory.

5. Types of Scheduling policies:

Preemptive Scheduling: In this type of scheduling, tasks run with equal time slice without considering the priorities.
Priority-based Preemptive: High priority task will run first.
Co-operative Scheduling: Context switching will happen only with the co-operation of running tasks. Task will run continuously until task yield is called.

6. Kernel Objects: For signaling the task to perform some work, the synchronization process is used. To perform this process Kernel objects are used. Some Kernel objects are Events, Semaphores, Queues, Mutex, Mailboxes, etc. We will see how to use these objects in upcoming tutorials.

From the above discussion, we have got some basic ideas about the RTOS concept and now we can implement the FreeRTOS project in Arduino. So, let's get started by installing FreeRTOS libraries in Arduino IDE.

## What is Semaphore?
In previous tutorials, we have discussed about task priorities and also get to know that a higher priority task pre-empts a lower priority task so while execution of high priority task there may be a possibility that data corruption can happen in lower priority task because it is not executed yet and data is coming continuously to this task from a sensor which causes data loss and malfunctioning of the whole application.

So, there is a need to protect resources from data loss and here Semaphore plays an important role.

Semaphore is a signaling mechanism in which a task in a waiting state is signaled by another task for execution. In other words, when a task1 finished its work, then it will show a flag or increment a flag by 1 and then this flag is received by another task (task2) showing that it can perform its work now. When task2 finished its work then the flag will be decreased by 1.

So, basically, it is a “Give” and “Take” mechanism and semaphore is an integer variable that is used to synchronize access to resources.

Types of Semaphore in FreeRTOS:

Semaphore is of two types.

Binary Semaphore
Counting Semaphore
1. Binary Semaphore: It has two integer values 0 and 1. It is somewhat similar to the Queue of length 1. For example, we have two tasks, task1 and task2. Task1 sends data to task2 so task2 continuously checks the queue item if there is 1, then it can read the data else it has to wait until it becomes 1. After taking the data, task2 decrement the queue and make it 0 That means task1 again can send the data to task2.

From the above example, it can be said that binary semaphore is used for synchronization between tasks or between tasks and interrupt.

2. Counting Semaphore: It has values greater than 0 and can be thought of queue of length more than 1. This semaphore is used for counting events. In this usage scenario, an event handler will ‘give’ a semaphore each time an event occurs (incrementing the semaphore count value), and a handler task will ‘take’ a semaphore each time it processes an event (decrementing the semaphore count value).

The count value is, therefore, the difference between the number of events that have occurred and the number that has been processed.
