#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int readcount = 0, sharedvar = 99;
sem_t mutex, wrt;

void *reader(void *arg)
{
    sem_wait(&mutex);
    readcount++;
    if (readcount == 1)
        sem_wait(&wrt);
    sem_post(&mutex);

    printf("\nReader %ld is reading sharedvar = %d", (long)arg, sharedvar);

    sem_wait(&mutex);
    readcount--;
    if (readcount == 0)
        sem_post(&wrt);
    sem_post(&mutex);
    return NULL;
}

void *writer(void *arg)
{
    printf("\nWriter %ld is trying to enter", (long)arg);
    sem_wait(&wrt);
    sharedvar++;
    printf("\nWriter %ld changed sharedvar to %d", (long)arg, sharedvar);
    sem_post(&wrt);
    return NULL;
}

int main()
{
    int n;
    printf("Enter the number of readers and writers: ");
    scanf("%d", &n);

    pthread_t readers[n], writers[n];
    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    for (long i = 1; i <= n; i++)
    {
        pthread_create(&writers[i - 1], NULL, writer, (void *)i);
        pthread_create(&readers[i - 1], NULL, reader, (void *)i);
    }

    for (int i = 0; i < n; i++)
    {
        pthread_join(writers[i], NULL);
        pthread_join(readers[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&wrt);
    return 0;
}
