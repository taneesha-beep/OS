#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE], in = 0, out = 0;
sem_t empty, full, mutex;

void *producer(void *arg)
{
    long id = (long)arg;
    for (int i = 0; i < 3; i++)
    { // produce 3 items each
        int item = rand() % 100;

        sem_wait(&empty);
        sem_wait(&mutex);

        buffer[in] = item;
        printf("\nProducer %ld produced %d at %d", id, item, in);
        in = (in + 1) % BUFFER_SIZE;

        sem_post(&mutex);
        sem_post(&full);
    }
    return NULL;
}

void *consumer(void *arg)
{
    long id = (long)arg;
    for (int i = 0; i < 3; i++)
    { // consume 3 items each
        sem_wait(&full);
        sem_wait(&mutex);

        int item = buffer[out];
        printf("\nConsumer %ld consumed %d from %d", id, item, out);
        out = (out + 1) % BUFFER_SIZE;

        sem_post(&mutex);
        sem_post(&empty);
    }
    return NULL;
}

int main()
{
    int n;
    printf("Enter number of producers and consumers: ");
    scanf("%d", &n);

    pthread_t producers[n], consumers[n];
    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);

    for (long i = 1; i <= n; i++)
    {
        pthread_create(&producers[i - 1], NULL, producer, (void *)i);
        pthread_create(&consumers[i - 1], NULL, consumer, (void *)i);
    }

    for (int i = 0; i < n; i++)
    {
        pthread_join(producers[i], NULL);
        pthread_join(consumers[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
    return 0;
}
