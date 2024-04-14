#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include <semaphore.h>

#define ARRAY_SIZE 5

int shared_array[ARRAY_SIZE] = {1, 2, 3, 4, 5}; // Initial array values
sem_t mutex, wrt;

// Function prototypes
void *reader(void *arg);
void *writer(void *arg);
void runAsynchronously(int numReaders, int numWriters);

int main() {
    int numReaders, numWriters;
    printf("Enter the number of readers: ");
    scanf("%d", &numReaders);
    printf("Enter the number of writers: ");
    scanf("%d", &numWriters);
    runAsynchronously(numReaders, numWriters);
    return 0;
}

// Reader function
void *reader(void *arg) {
    int reader_id = *((int *)arg);

    sem_wait(&mutex);
    if (shared_array[0] == -1) {
        sem_post(&mutex);
        printf("Reader %d is waiting because a writer is writing\n", reader_id);
        sem_wait(&mutex);
    }
    sem_post(&mutex);

    // Calculate the sum of array elements
    int sum = 0;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        sum += shared_array[i];
    }

    printf("Reader %d calculated the sum of array elements: %d\n", reader_id, sum);
    sleep(1);

    sem_wait(&mutex);
    sem_post(&mutex);

    printf("Reader %d completed reading, CS is free\n", reader_id);
    return NULL;
}

// Writer function
void *writer(void *arg) {
    int writer_id = *((int *)arg);

    sem_wait(&wrt);
    // Modify array values
    int factor = 2;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        shared_array[i] *= factor;
    }
    printf("Writer %d multiplied array elements by %d\n", writer_id, factor);
    sleep(1);
    shared_array[0] = -1; // Indicates that a writer is currently writing
    sem_post(&wrt);

    sem_wait(&mutex);
    shared_array[0] = 1; // Indicates that no writer is currently writing
    sem_post(&mutex);

    printf("Writer %d completed writing, CS is free\n", writer_id);
    return NULL;
}

// Run the program asynchronously
void runAsynchronously(int numReaders, int numWriters) {
    pthread_t readers[numReaders];
    pthread_t writers[numWriters];
    int i, reader_ids[numReaders], writer_ids[numWriters];
    for (i = 0; i < numReaders; i++) {
        reader_ids[i] = i + 1;
    }
    for (i = 0; i < numWriters; i++) {
        writer_ids[i] = i + 1;
    }
    
    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    printf("Running asynchronously.\n");

    // Reader-Reader (RR) case
    printf("\nReader-Reader (RR) case:\n");
    for (i = 0; i < numReaders; i++) {
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }
    for (i = 0; i < numReaders; i++) {
        pthread_join(readers[i], NULL);
    }

    // Reader-Writer (RW) case
    printf("\nReader-Writer (RW) case:\n");
    pthread_create(&readers[0], NULL, reader, &reader_ids[0]);
    pthread_create(&writers[0], NULL, writer, &writer_ids[0]);
    pthread_join(readers[0], NULL);
    pthread_join(writers[0], NULL);

    // Writer-Writer (WW) case
    printf("\nWriter-Writer (WW) case:\n");
    for (i = 0; i < numWriters; i++) {
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }
    for (i = 0; i < numWriters; i++) {
        pthread_join(writers[i], NULL);
    }

    // Writer-Reader (WR) case
    printf("\nWriter-Reader (WR) case:\n");
    pthread_create(&writers[0], NULL, writer, &writer_ids[0]);
    pthread_create(&readers[0], NULL, reader, &reader_ids[0]);
    pthread_join(readers[0], NULL);
    pthread_join(writers[0], NULL);

    sem_destroy(&mutex);
    sem_destroy(&wrt);
}

