#include <stdio.h>
#include <stdlib.h>

int NUM_PROCESS = 3;
int K = 100;

struct process
{
    int id;
    int active;    // 1: at the time of process arrival; 0: at the time of process termination
    int arrival_time;
    int total_cpu_time;
    int remaining_cpu_time;
    int turnaround_time;
};

double average_turnaround_time(struct process table[]);
void init_process_table_with_3values(struct process table[]);
void update_process_active_status(struct process table[], int current_time);
void fifo(struct process table[]);
void sjf(struct process table[]);
void srt(struct process table[]);

int main()
{
    struct process process_table[NUM_PROCESS];

    init_process_table_with_3values(process_table);
    fifo(process_table);
    printf("FIFO=%.2f ", average_turnaround_time(process_table));

    init_process_table_with_3values(process_table);
    sjf(process_table);
    printf("SJF=%.2f ", average_turnaround_time(process_table));

    init_process_table_with_3values(process_table);
    srt(process_table);
    printf("SRT=%.2f", average_turnaround_time(process_table));

    return 0;

}

void fifo(struct process table[])
{
    int n = NUM_PROCESS;
    int waitTime[NUM_PROCESS];  
    int totalWaitTime = 0;
    int totalTurnAroundTime = 0;
    
    waitTime[0] = 0;
    for (int  i = 1; i < n ; i++ )
    {  
        waitTime[i] =  table[i-1].total_cpu_time + waitTime[i-1]; 
    }

    for (int  i = 0; i < n ; i++)  
    {
        table[i].turnaround_time = table[i].total_cpu_time + waitTime[i] - table[i].arrival_time;
    }
}

void sjf(struct process table[])
{
    int n = NUM_PROCESS;
    int waitTime[NUM_PROCESS];
    int totalTime = 0;
    int idOfCurrent = 0;

    for(int i = 0; i < n; i++)
    {
        totalTime = totalTime + table[i].total_cpu_time;
    }

    for(int k = 0; k < totalTime; k++)
    {
        for(int i = 0; i < n; i++)
        {
            if(table[i].arrival_time == k)
            {
                table[i].active = 1;
            }
            if(table[i].remaining_cpu_time <= 0 && table[i].active != 0)
            {
                table[i].active = 0;
            }

            if(table[idOfCurrent].active == 0)
            {
                for(int j = 0; j < n; j++)
                {
                    int temp = 0;
                    if(table[j].active)
                    {
                        if(table[j].total_cpu_time < table[temp].total_cpu_time)
                        {
                            temp = j;
                        }
                        idOfCurrent = temp;
                    }
                }
            }
        }

        for(int i = 0; i < n; i++)
        {
            if(table[i].active == 1)
            {
                if(i == idOfCurrent)
                {
                    table[i].remaining_cpu_time--;
                }

                table[i].turnaround_time++;
            }
        }
    }
}

void srt(struct process table[])
{
    int n = NUM_PROCESS;
    int waitTime[NUM_PROCESS];
    int totalTime = 0;
    int idOfSmallest = 0;

    for(int i = 0; i < n; i++)
    {
        totalTime = totalTime + table[i].total_cpu_time;
    }

    for(int k = 0; k < totalTime; k++)
    {
        for(int i = 0; i < n; i++)
        {
            if(table[i].arrival_time == k)
            {
                table[i].active = 1;
            }
            if(table[i].remaining_cpu_time <= 0 && table[i].active != 0)
            {
                table[i].active = 0;
            }

            if(table[idOfSmallest].active == 0)
            {
                for(int j = 0; j < n; j++)
                {
                    int temp = 0;
                    if(table[j].active)
                    {
                        if(table[j].remaining_cpu_time < table[temp].remaining_cpu_time)
                        {
                            temp = j;
                        }
                        idOfSmallest = temp;
                    }
                }
            }

            if(table[i].remaining_cpu_time < table[idOfSmallest].remaining_cpu_time && table[i].active == 1)
            {
                idOfSmallest = i;
            }    
        }
        
        for(int i = 0; i < n; i++)
        {
            if(table[i].active == 1)
            {
                if(i == idOfSmallest)
                {
                    table[i].remaining_cpu_time--;
                }

                table[i].turnaround_time++;
            }
        }
    }
}

void init_process_table_with_3values(struct process table[])
{
    int arrival_time_array[3] = {0, 1, 3};
    int total_cpu_time_array[3] = {6, 3, 2};


    for (size_t i = 0; i < 3; i++)
    {
        table[i].id = i;
        table[i].active = 0; // active depends on the arrival time
        table[i].arrival_time = arrival_time_array[i];
        table[i].total_cpu_time = total_cpu_time_array[i];
        table[i].remaining_cpu_time = table[i].total_cpu_time;
        table[i].turnaround_time = 0;
    }

}

double average_turnaround_time(struct process table[])
{
    double total_time = 0.0;
    for (size_t i = 0; i < NUM_PROCESS; i++)
    {
        total_time += table[i].turnaround_time;
    }
    return total_time / NUM_PROCESS;
}


void update_process_active_status(struct process table[], int current_time)
{
    for (size_t i = 0; i < NUM_PROCESS; i++)
    {
        if(current_time >= table[i].arrival_time && table[i].remaining_cpu_time > 0)
        {
            table[i].active = 1;
        }
        else
        {
            table[i].active = 0;
        }

    }
}

