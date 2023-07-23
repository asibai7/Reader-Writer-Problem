#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

typedef struct _rwlock_t {
    sem_t readlock; // semaphore to update reader value
    sem_t writelock; // allows only 1 writer to access at once, but multiple readers
    sem_t wait; //universal lock for readers and writers
    int readers; // count for readers accessing
} rwlock_t;

void rwlock_init(rwlock_t *rw); //initalizes lock
void rwlock_acquire_readlock(rwlock_t *rw); //readers aquire there lock
void rwlock_release_readlock(rwlock_t *rw); //readers release there lock
void rwlock_acquire_writelock(rwlock_t *rw); //writers aquire there lock
void rwlock_release_writelock(rwlock_t *rw); //writers release there lock

void* readThread(rwlock_t *lock); //reader threads begins here
void* writeThread(rwlock_t *lock); //writer threads begins here
void reading_writing(); //Aaccessing data section