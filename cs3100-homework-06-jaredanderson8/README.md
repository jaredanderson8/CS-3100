# CS3100-Template-06

## Homework objective
Compare the performance of the disk scheduling algorithms FIFO, SSTF, Scan, C-Scan.

## Instruction
This template gives you starter code for CS 3100 Homework. In this homework, you will implement the disk scheduling algorithms FIFO, SSTF, Scan, C-Scan, described in "9.3 Disk scheduling". 

* A disk consists of n concentric tracks, numbered 0 through n - 1.
* A disk scheduling algorithms accepts a sequence of m integers in the range [0 : n - 1], where each integer t is a request to seek to track t.
* Each scheduling algorithm generates an ordering according to which the m requests are serviced.
* When a request is serviced, the program should read a value from the disk or write a value to the disk. You may randomly decide what to do: read or write. You may also decide what value to read or write, it is entirely up to you. The focus is the scheduling algorithms.
* Note: each scheduling algorithm should service the first request in the sequence, then decide the ordering of the rest of the requests according to the algorithm. 

## Your task
* Implement the 4 scheduling algorithms. Each program reads the generated sequence of requests and returns the total number of tracks traversed by the r/w arm.
