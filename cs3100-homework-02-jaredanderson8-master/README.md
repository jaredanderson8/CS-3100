# CS3100-Template-02

## Homework Objective
Implement process creation hierarchy using a linked list

## Instruction
This template gives you starter code for CS 3100 Homework. In this homework, you will implement the process creation hierarchy using a linked list to keep track of child processes as described in "2. Processse, Threads, and Resources". 

The PCBs are <b>simplified</b> as follows:

* All PCBs are stored in an array of size N, named PCBArray.
* Each process is referred to by the PCBArray index, 0 through N-1.
* Each PCB is a structure consisting of only the two fields: `parent`: a PCBArray index corresponding to the process's creator, and `children`: a pointer to a linked list, where each list element contains the PCBArray index of one child process.

The necessary functions are <b>simplified</b> as follows:

`create(p)` represents the create function executed by process PCBArray[p]. The function creates a new child process PCBArray[q] of process PCBArray[p] by performing the following tasks:
* allocate a free PCBArray[q]
* record the parent's index, p, in PCBArray[q]
* initialize the list of children of PCBArray[q] as empty
* create a new link containing the child's index q and appends the link to the linked list of PCBArray[p]

`destroy(p)` represents the destroy function executed by process PCB[p]. The function recursively destroys all descendent processes (child, grandchild, etc.) of process PCBArray[p] by performing the following tasks: for each element q on the linked list of children of PCBArray[p]:
* destroy(q) /* recursively destroy all progenies */
* free PCBArray[q]
* deallocate the element q from the linked list

Note that to simplify the implementation, destroy(p) does not destroy the process p itself.

## Your task
In this homework, you need to implement the two functions `create(p)` and `destroy(p)`.
