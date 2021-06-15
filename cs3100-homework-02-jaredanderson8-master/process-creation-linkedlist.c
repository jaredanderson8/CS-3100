#include <stdio.h>
#include <stdlib.h>
#define N 20

struct pcb
{
    int parent;                 // a PCB index corresponding to the process's creator
    struct Node * children;     // a pointer to a linked list, where each list element contains the PCB index of one child process

};

// linked list for children PCBs
struct Node
{
    int index;                   // a PCB index
    struct Node * next;
};

struct pcb PCBArray[N];

void create(int p);
void destroy(int p);
void print(int p);

int main(void)
{
    for (size_t i = 0; i < N; i++)
    {
        PCBArray[i].parent = -1;    // -1 for parent means the spot is makred as free (green)
    }

    // create PCBArray[0] as the only currently existing process
    PCBArray[0].parent = 0;

    // TESTING: please do not modify the following testing code
    create(0);
    create(0);
    create(0);
    create(2);
    create(4);
    create(5);
    create(3);
    destroy(4);
    create(3);  
    print(3);   

    return 0;
}


void create(int p)
{
	// TODO: add your code to implement the create function
    int q = p;
    while(q <= N)
    {
        if(PCBArray[q].parent == -1)
        {
            break;
        }

        q++;

    }

    PCBArray[q].parent = p;
    PCBArray[q].children = NULL;
    PCBArray[q].children = (struct Node*)malloc(sizeof(struct Node));
    if(!PCBArray[q].children)
    {
        printf("Error 1: malloc failed in create : %i ", PCBArray[q].parent);
    }

    if(PCBArray[p].children == NULL)
    {
        PCBArray[p].children = (struct Node*)malloc(sizeof(struct Node));
        //PCBArray[p].children->index = 0;
        PCBArray[p].children->next = NULL;
    }

    PCBArray[p].children->index = q;
    PCBArray[p].children->next = PCBArray[q].children;
}

void destroy(int p)
{
	// TODO: add your code to implement the destroy function
    if(PCBArray[p].children->next != NULL)
    {
        destroy(PCBArray[p].children->index);
        free(PCBArray[p].children->next);
        PCBArray[PCBArray[p].children->index].parent  = -1;
        PCBArray[p].children = NULL;
    }
}

// print information about a PCB at index p, please do not modify the print function
void print(int p)
{
    printf("PCB Index: %i ", p);
    if (PCBArray[p].parent > -1)
    {
        printf("Status: allocated; Parent PCB Index: %i; ", PCBArray[p].parent);
        printf("Children Index(es): ");
        struct Node * current = PCBArray[p].children;
        while ( current != NULL)
        {
            printf("%d ", current->index);
            current = current->next;
        }
        printf("\n");
    }
    else
    {
        printf("Status: free\n");
    }

}