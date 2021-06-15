#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#define N 100
#define M 20

int disk[N];     // A disk consists of n concentric tracks, numbered 0 through n - 1.
int requests[M]; // A sequence of m integers in the range [0 : n - 1], where each integer t is a request to seek to track t.

int read_input(char *filename);
int fifo();
int sstf();
int scan();
int c_scan();

int main(void)
{
    // read the requests from the input file
    char *filename = "input.txt";
    if (read_input(filename) != 0)
    {
        printf("Cannot open the file");
        exit(1);
    }

    printf("FIFO=%d", fifo());

    if (read_input(filename) != 0)
    {
        printf("Cannot open the file");
        exit(1);
    }

    printf(" SSTF=%d", sstf());

    if (read_input(filename) != 0)
    {
        printf("Cannot open the file");
        exit(1);
    }

    printf(" Scan=%d", scan());

    if (read_input(filename) != 0)
    {
        printf("Cannot open the file");
        exit(1);
    }

    printf(" C-Scan=%d", c_scan());

    return 0;
}

int fifo()
{
    // TODO
    int total = 0;
    int currentPos = 0;

    int i = 0;
    while(i < M)
    {
        total += abs(requests[i] - currentPos);
        currentPos = requests[i];
        requests[i] = -1;
        i++;
    }

    return total;
}

int sstf()
{
    // TODO
    int total = 0;
    int currentPos = 0;

    total += requests[0];
    currentPos = requests[0];
    requests[0] = -1;

    int i = 1;
    while(i < 20)
    {
        int smallestDistance = 0;

        int j = 0;
        while(j < 20)
        {
            if(requests[j] >= 0)
            {
                if(abs(requests[j] - currentPos) < abs(requests[smallestDistance] - currentPos))
                {
                    smallestDistance = j;
                }
            }

            j++;
        }
        //printf("\nsmallest found at %d", smallestDistance);
        //printf(" : %d", requests[smallestDistance]);
        //printf("\nTotal: %d", total);

        total += abs(requests[smallestDistance] - currentPos);
        currentPos = requests[smallestDistance];
        requests[smallestDistance] = -1;
        i++;
    }

    return total; 
}

int scan()
{
    // TODO
    int total = 0;
    int currentPos = 0;
    int biggest = 0;
    bool up = true;

    int k = 0;
    while(k < M)
    {
        if(requests[k] > requests[biggest])
        {
            biggest = k;
        }
        k++;
    }
    //printf("biggest: %d", biggest);

    total += requests[0];
    currentPos = requests[0];
    requests[0] = -1;

    int i = 1;
    while(i < 20)
    {
        int next = 0;
        
        int j = 0;
        while(j < 20)
        {
            if(up)
            {
                if(requests[j] >= 0 && requests[j] > currentPos)
                {
                    if(abs(requests[j] - currentPos) < abs(requests[next] - currentPos))
                    {
                        next = j;
                    }
                }
            }
            else
            {
                if(requests[j] >= 0)
                {
                    if(abs(requests[j] - currentPos) < abs(requests[next] - currentPos))
                    {
                        next = j;
                    }
                }
            }

            j++;
        }

        if(next == biggest)
        {
            up = false;
            //printf("\nswitch ******************************************");
        }

        //printf("\nnext found at %d", next);
        //printf(" : %d", requests[next]);
        //printf("\nTotal: %d", total);

        total += abs(requests[next] - currentPos);
        currentPos = requests[next];
        requests[next] = -1;
        i++;
    }

    return total;
}

int c_scan()
{
    // TODO
    int total = 0;
    int currentPos = 0;
    int biggest = 0;
    bool up = true;

    int k = 0;
    while(k < M)
    {
        if(requests[k] > requests[biggest])
        {
            biggest = k;
        }
        k++;
    }
    //printf("biggest: %d", biggest);

    total += requests[0];
    currentPos = requests[0];
    requests[0] = -1;

    int i = 1;
    while(i < 20)
    {
        int next = 0;
        
        int j = 0;
        while(j < 20)
        {
            if(up)
            {
                if(requests[j] >= 0 && requests[j] > currentPos)
                {
                    if(abs(requests[j] - currentPos) < abs(requests[next] - currentPos))
                    {
                        next = j;
                    }
                }
            }
            else
            {
                if(next == 0 )
                {
                    int k = 0;
                    while(k < 20)
                    {
                        if(requests[k] >= 0)
                        {
                            next = k;
                            break;
                        }
                        k++;
                    }
                }

                if(requests[j] >= 0)
                {
                    if(abs(requests[j] - currentPos) < abs(requests[next] - currentPos))
                    {
                        next = j;
                        //printf("\nnext set equal to: %d", j);
                    }
                }
            }

            j++;
        }

       // printf("\nnext found at %d", next);
        //printf(" : %d", requests[next]);
        //printf("\nTotal: %d", total);

        total += abs(requests[next] - currentPos);
        currentPos = requests[next];
        requests[next] = -1;
        i++;

        if(next == biggest)
        {
            up = false;
            total += currentPos;
            currentPos = 0;
            //printf("\nswitch ******************************************");
        }
    }

    return total;
}

int read_input(char *filename)
{
    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Could not open file %s", filename);
        return 1;
    }
    int i = 0;
    int num;
    while (fscanf(fp, "%d", &num) > 0)
    {
        requests[i] = num;
        i++;
    }
    fclose(fp);
    return 0;
}

