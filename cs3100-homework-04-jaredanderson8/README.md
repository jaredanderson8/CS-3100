# CS3100-Template-04

## Homework objective
Implement the solution to the bounded buffer problem from the section titled Semaphores, with and without any P or V operations. Observe and eliminate a race condition.

## Race Condition
A race condition arises in software when a computer program, to operate properly, depends on the sequence or timing of the program's processes or threads. Critical race conditions cause invalid execution and software bugs. Critical race conditions often happen when the processes or threads depend on some shared state. Operations upon shared states are done in critical sections that must be mutually exclusive. Failure to obey this rule can corrupt the shared state.

A race condition can be difficult to reproduce and debug because the end result is nondeterministic and depends on the relative timing between interfering threads. Problems of this nature can therefore disappear when running in debug mode, adding extra logging, or attaching a debugger. Bugs that disappear like this during debugging attempts are often referred to as a "Heisenbug". It is therefore better to avoid race conditions by careful software design.

## Debugging
By analyzing in what orders statements may exeuct, it is often helpful to find race conditions. This analysis can be done at several levels of detail. The right level of detail depends on how the code is written, the programming language, the runtime environment, the operating system, and the hardware. If analysis at a high level doesn’t help you find the problem, then you may break things down to finer-grained operations.

A typical strategy that you can find suggested on many forums on the web is to add extensive extra logging to the program, effectively print out almost every variable so you can map what you expect to what's happening. Keep track of the data structure that crashes the program or triggers some weried states. Use your understanding of the program to find out what other parts of the program may affect it. It is important to find the statements or part of the program which are racing to change the data structure, hopefully leading to find and fix the problem. You may also use breakpoints in the program and step trhough until you observe the race condition. Remember, because it is related to race conditions, you might not be able to replicate the issue every time you run the test. 

## Instruction
This template gives you starter code for CS 3100 Homework. In this homework, you will implement the solution to the bounded buffer problem, described in "4.2 Semaphores". 

* The buffer is a large array of n integers, initialized to all zeros.
* The producer and the consumer are separate concurrent threads in a process.
* The producer executes short bursts of random duration. During each burst of length k1, the producer adds a 1 to the next k1 slots of the buffer, modulo n.
* The consumer also executes short bursts of random duration. During each burst of length k2, the consumer reads the next k2 slots and resets each to 0.
* A race condtion occurs if any slot contains a number greater than 1: the consumer was unable to keep up and thus the producer has added a 1 to a slot that has not yet been reset. Or a race condtion occurs if the consumer reads a number zero from any slot: the consumer overtakes the producer and accesses empty slots.
* Both producer and consumer sleep periodically for random time intervals to emulate unpredictable execution speeds.
 
The simulation mimics the above behavior by repeating the following steps:

```
producer thread:
while (1)
   get random number k1
   for i from 0 to k1
      buffer[(next_in + i) mod n] += 1
      
   next_in = (next_in + k1) mod n
   get random number t1
   sleep for t1 seconds
   
consumer thread:
while(1) 
   get random number t2
   sleep for t2 seconds
   get random number k2
   for i from 0 to k2
      data = buffer[(next_out + i) mod n]
      if (data != 1) exit and report race condition
      buffer[(next_out + i) mod n] = 0
   
   next_out = (next_out + k2) mod n
```


## Your task
* Implement the above simulation for two functions: ```producer_thr_fn``` and ```consumer_thr_fn```, first without any P or V operations, experiment with different values of n, k, and t until a race condition is observed.
* Modify the solution by including the necessary P and V operations in the code to solve the race condition problem. 
