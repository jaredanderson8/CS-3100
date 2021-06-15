/*
hole = free memory space
block = occupied memory space
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

const int N = 100;
const double avg_size = 8.0;
const double std = 2.0;
int X = 5;
int search_count = 0;

double rand_gen();
double normalRandom();
void reset_memory(int memory[]);
void init_memory(int memory[]);
int generate_random_request();
double memory_utilization(int memory[]);
void release_occupied_block(int memory[]);

int first_fit(int memory[], int s);
int next_fit(int memory[], int s, int last_allocation);
int best_fit(int memory[], int s);
int worst_fit(int memory[], int s);

void WriteRequestIntoBlock(int memory[], int s, int index);
void PrinMem(int memory[]);
int last_allocation = 0;

int main()
{
    int memory[N];
    double memory_utilizations[X];
    reset_memory(memory);
    init_memory(memory);

    //printf("Before Allocation: \n");
    //PrinMem(memory);
    printf("First-fit with d of %f ", avg_size);
    printf("and a v of %f \n", std);

    int total_search = 0;
    int requests = 0;
    for (size_t i = 0; i < X; i++)
    {
        int fail = 0;  // -1 = fail, 0 = succeed
        while( fail > -1)
        {
            int s = generate_random_request();
            //printf("requesting: %d \n", s);

            // call your memory allocation method below:
            fail = first_fit(memory, s);
            //fail = next_fit(memory, s, last_allocation);
            //fail = best_fit(memory, s);
            //fail = worst_fit(memory, s);

            requests++;
            total_search += search_count;
            search_count = 0;
        }
        
        memory_utilizations[i] = memory_utilization(memory);
        release_occupied_block(memory);
    }

    // display the results
    double ratio = (double)total_search / (double)requests;
    printf("ratio = %f\n", ratio);
    double total = 0.0;
    for (size_t i = 0; i < X; i++)
    {
        total += memory_utilizations[i];
    }
    printf("Average memory utilizatioin = %f\n", total / X);

    //printf("After Allocation: \n");
    //PrinMem(memory);
    
    return 0;
}

void PrinMem(int memory[])
{
    int i = 0;
    while (i < N)
    {
        printf("%d ", memory[i]);

        i++;
    }
    printf("\n");
}

// 0: succeed; -1: failed to allocate
int first_fit(int memory[], int s)
{
    // TODO: implement the first fit strategy
    int i = 0;
    while (i < N)
    {
        if(memory[i] < 0)
        {
            if(s <= abs(memory[i]))
            {
                WriteRequestIntoBlock(memory, s, i);
                return 0;
            }
        }
        i++;
    }

    return -1;
}

// return the index of the hole being allocated, or -1 if failed
int next_fit(int memory[], int s, int last_allocation)
{
    // TODO: implement the next fit strategy
    int i = 0;
    while (i < N)
    {
        if(i + last_allocation > N)
        {
            if(memory[i + last_allocation - N] < 0)
            {
                if(s <= abs(memory[i]))
                {
                    WriteRequestIntoBlock(memory, s, i);
                    return 0;
                }
            }
        }
        else
        {
            if(memory[i + last_allocation] < 0)
            {
                if(s <= abs(memory[i]))
                {
                    WriteRequestIntoBlock(memory, s, i);
                    return 0;
                }
            }
        }
        
        i++;
    }

    return -1;
}

int best_fit(int memory[], int s)
{
    // TODO: implement the best fit strategy
    int indexBestFit = -1;
    int sizeBestFit = 0;

    int i = 0;
    while(i < N)
    {
        if(memory[i] < 0)
        {
            if(abs(memory[i]) == s)
            {
                indexBestFit = i;
                sizeBestFit = memory[i];
                break;
            }
            else
            {
                if(abs(memory[i]) < sizeBestFit && abs(memory[i]) >= s)
                {
                    indexBestFit = i;
                    sizeBestFit = memory[i];
                }
            }
        }

        i++;
    }

    if(indexBestFit > -1)
    {
        WriteRequestIntoBlock(memory, s, indexBestFit);
        return 0;
    }

    return -1;
}

int worst_fit(int memory[], int s)
{
    // TODO: implement the worst fit strategy
    int indexWorstFit = -1;
    int sizeWorstFit = 0;

    int i = 0;
    while(i < N)
    {
        if(memory[i] < 0)
        {
            if(abs(memory[i]) > sizeWorstFit && abs(memory[i]) >= s)
            {
                indexWorstFit = i;
                sizeWorstFit = memory[i];
            }
        }

        i++;
    }

    if(indexWorstFit > -1)
    {
        WriteRequestIntoBlock(memory, s, indexWorstFit);
        return 0;
    }

    return -1;
}

void WriteRequestIntoBlock(int memory[], int s, int index)
{
    int originalSize = abs(memory[index]);

    int i = index;
    while(i < (index + s))
    {
        memory[i] = s;

        i++;
    }

    while(i < (index + originalSize))
    {
        memory[i] = -1 * (originalSize - s);

        i++;
    }
}

void reset_memory(int memory[])
{
    for (size_t i = 0; i < N; i++)
    {
        memory[i] = 0;
    }
}

int generate_random_request()
{
    srand(time(NULL));
    int s = N;
    while(s < 1 || s > N-1)
    {
        s = (int)(normalRandom() * std + avg_size);
    }
    return s;
}

void init_memory(int memory[])
{
    srand(time(NULL));
    int hole_or_block = rand() % 2;

    int i = 0;
    while(i < N)
    {
        int size = N;
        while(size < 0 || size > N-1)
        {
            size = (int)(normalRandom() * std + avg_size);
        }

        if(i + size >= N)
        {
            size = N - i;
        }

        int value = size;
        if(hole_or_block == 0)
        {
            value = -value;
            hole_or_block = 1;
        }
        else
        {
            hole_or_block = 0;
        }
        
        for (size_t j = 0; j < size; j++)
        {
            memory[i] = value;
            i++;
        }
    } 
}

double rand_gen() {
   return ( (double)(rand()) + 1. )/( (double)(RAND_MAX) + 1. );
}
double normalRandom() {
   double v1=rand_gen();
   double v2=rand_gen();
   return cos(2*3.14*v2)*sqrt(-2.*log(v1));
}

double memory_utilization(int memory[])
{
    int occupied = 0;
    for (size_t i = 0; i < N; i++)
    {
        if (memory[i] > 0)
        {
            occupied++;
        }
    }
    return (double)occupied / (double)N;
    
}

void release_occupied_block(int memory[])
{
    int occupied_indexes[N];
    int number_occupied_blocks = 0;

    int i = 0;
    while(i < N)
    {
        if(memory[i] > 0)
        {
            occupied_indexes[number_occupied_blocks] = i;
            number_occupied_blocks++;
        }
        i += abs(memory[i]);
    }

    srand(time(NULL));
    int lower = 0;
    int upper = number_occupied_blocks - 1;
    int random_index = rand() % (upper - lower + 1) + lower;
    int block_index = occupied_indexes[random_index];
    int block_size = memory[block_index];
    int new_hole_size = block_size;
    int new_index = block_index;
    if(block_index > 0)
    {
        int before_value = memory[block_index - 1];
        if(before_value < 0)
        {
            new_hole_size += abs(before_value);
            new_index -= abs(before_value);
        }
    }
    if(block_index + block_size < N)
    {
        int after_value = memory[block_index + block_size];
        if(after_value < 0)
        {
            new_hole_size += abs(after_value);
        }
    }

    for (size_t i = 0; i < new_hole_size; i++)
    {
        memory[new_index+i] = -new_hole_size;
    }
}
