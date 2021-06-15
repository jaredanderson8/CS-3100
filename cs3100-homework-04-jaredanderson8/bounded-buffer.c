#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define N 50

int MAXK1 = 20;
int MAXK2 = 20;
int MAXT1 = 2;
int MAXT2 = 2;

pthread_t producer_tid;
pthread_t consumer_tid;

void init_buffer();
void *producer_thr_fn(void *buffer);
void *consumer_thr_fn(void *buffer);
int random_generator(int lower, int upper);
void print_buffer(char *message);
void P(int* p);
void V(int* p);

int buffer[N];
int f = 0;
int e = 1;

int main(void)
{
    init_buffer();

    int err;

    err = pthread_create(&producer_tid, NULL, producer_thr_fn, NULL);
    if (err != 0)
    {
        printf("%d can’t create thread", err);
        exit(1);
    }
    err = pthread_create(&consumer_tid, NULL, consumer_thr_fn, NULL);
    if (err != 0)
    {
        printf("%d can’t create thread", err);
        exit(1);
    }

    sleep(50);

    return 0;
}

void init_buffer()
{
    for (size_t i = 0; i < N; i++)
    {
        buffer[i] = 0;
    }
}

int next_in;

void *producer_thr_fn(void *arg)
{
    // TODO: Implement the producer function
    while(1)
    {
        int k1 = random_generator(1, MAXK1);

        for(int i = 0; i < k1; i++)
        {
            P(&e);
            buffer[(next_in + k1) % N] += 1;
        }

        next_in = (next_in + k1) % N;
        int t1 = random_generator(0, MAXT1);
        sleep(t1);

        V(&f);
    }
}

int next_out;

void *consumer_thr_fn(void *arg)
{
    // TODO: Implement the consumer function
    while(1)
    {
        int t2 = random_generator(0, MAXT2);
        sleep(t2);

        int k2 = random_generator(1, MAXK2);

        for(int i = 0; i < k2; i++)
        {
            P(&f);
            
            int data = buffer[(next_out + i) % N];
            if(data != 1)
            {
                printf("Race condition found.");
                exit(0);
            }
            buffer[(next_out + k2) % N] = 0;
        }

        V(&e);

        next_out = (next_out + k2) & N;
    }
}

int random_generator(int lower, int upper)
{
    srand(time(NULL));
    return rand() % (upper - lower + 1) + lower;
}

void print_buffer(char *message)
{
    printf("\n%s Buffer = ", message);
    for (size_t i = 0; i < N; i++)
    {
        printf("%d ", buffer[i]);
    }
    printf("End of Buffer\n");
    
}

void P(int* p)
{
    while(*p <= 0)
    {
        // wait
    }
    (*p)--;
}

void V(int *p)
{
    (*p)++;
}
