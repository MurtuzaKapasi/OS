#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

#define ARRAY_SIZE 5
int shared_array[ARRAY_SIZE] = {1, 2, 3, 4, 5}; // Initial array values
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_reader = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_writer = PTHREAD_COND_INITIALIZER;
int readers_count = 0;
int writers_count = 0;

// Function prototypes
void *reader(void *arg);
void *writer(void *arg);
void runSynchronized(int numReaders, int numWriters);

int main() {
    int numReaders, numWriters;
    printf("Enter the number of readers: ");
    scanf("%d", &numReaders);
    printf("Enter the number of writers: ");
    scanf("%d", &numWriters);
    runSynchronized(numReaders, numWriters);
    return 0;
}

// Reader function
void *reader(void *arg) {
    int reader_id = *((int *)arg);
    pthread_mutex_lock(&mutex);
    while (writers_count > 0) {
        printf("Reader %d is waiting because a writer is writing\n", reader_id);
        pthread_cond_wait(&cond_reader, &mutex);
    }
    readers_count++;
    pthread_mutex_unlock(&mutex);

    // Calculate the sum of array elements
    int sum = 0;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        sum += shared_array[i];
    }

    printf("Reader %d calculated the sum of array elements: %d\n", reader_id, sum);
    sleep(1);

    pthread_mutex_lock(&mutex);
    readers_count--;
    if (readers_count == 0) {
        pthread_cond_signal(&cond_writer);
    }
    pthread_mutex_unlock(&mutex);

    printf("Reader %d completed reading, CS is free\n", reader_id);
    return NULL;
}

// Writer function
void *writer(void *arg) {
    int writer_id = *((int *)arg);
    pthread_mutex_lock(&mutex);
    writers_count++;
    while (readers_count > 0 || writers_count > 1) {
        printf("Writer %d is blocked from writing\n", writer_id);
        pthread_cond_wait(&cond_writer, &mutex);
    }
    pthread_mutex_unlock(&mutex);

    // Modify array values
    int factor = 2;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        shared_array[i] *= factor;
    }

    printf("Writer %d multiplied array elements by %d\n", writer_id, factor);
    sleep(1);

    pthread_mutex_lock(&mutex);
    writers_count--;
    pthread_cond_signal(&cond_writer);
    pthread_cond_broadcast(&cond_reader);
    pthread_mutex_unlock(&mutex);

    printf("Writer %d completed writing, CS is free\n", writer_id);
    return NULL;
}

// Run the program in synchronized mode
void runSynchronized(int numReaders, int numWriters) {
    pthread_t readers[numReaders];
    pthread_t writers[numWriters];
    int i, reader_ids[numReaders], writer_ids[numWriters];
    for (i = 0; i < numReaders; i++) {
        reader_ids[i] = i + 1;
    }
    for (i = 0; i < numWriters; i++) {
        writer_ids[i] = i + 1;
    }
    printf("Running in synchronized mode.\n");

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
    
    // Writer-Reader (WR) case
    printf("\nWriter-Reader (WR) case:\n");
    pthread_create(&writers[0], NULL, writer, &writer_ids[0]);
    pthread_create(&readers[0], NULL, reader, &reader_ids[0]);
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
}
