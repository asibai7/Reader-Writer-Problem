#include "readerwriter.h"

void rwlock_init(rwlock_t *rw) { //Initializes the reader-writer lock struct
    rw->readers = 0;
    sem_init(&rw->wait, 0, 1); //access the lock
    sem_init(&rw->readlock, 0, 1);
    sem_init(&rw->writelock, 0, 1);
}
void rwlock_acquire_readlock(rwlock_t *rw) { //reader threads go here to get writelock
    sem_wait(&rw->readlock);
    rw->readers++;  //counts amount of readers acccessing critical section
    if (rw->readers == 1) // first reader obtains writelock
        sem_wait(&rw->writelock);
    sem_post(&rw->readlock);
} 
void rwlock_release_readlock(rwlock_t *rw) { //reader threads go here to release writelock
    sem_wait(&rw->readlock);
    rw->readers--; //subtracts number of readers in critical section
    if (rw->readers == 0) // last reader releases
        sem_post(&rw->writelock);
    sem_post(&rw->readlock);
}
void rwlock_acquire_writelock(rwlock_t *rw) { //writer threads go here to obtain writelock
    sem_wait(&rw->writelock);  
}
void rwlock_release_writelock(rwlock_t *rw) { //writer threads go here to release lock
    sem_post(&rw->writelock);
}
void* readThread(rwlock_t *lock){
    sem_wait(&lock->wait); //universal lock for both readers and writers
    rwlock_acquire_readlock(lock);
    printf("Create Reader\n");
    sem_post(&lock->wait);
    printf("Reader is Reading\n");
    reading_writing(); //accessing critical section
    printf("Finished reading\n");
    rwlock_release_readlock(lock);
}
void* writeThread(rwlock_t *lock){
    sem_wait(&lock->wait); //universal lock for both readers and writers
    rwlock_acquire_writelock(lock);
    printf("Create Writer\n");
    printf("Writer Is Writing\n");
    reading_writing(); //accessing critical section
    printf("Finished writing\n");
    rwlock_release_writelock(lock);
    sem_post(&lock->wait);
}
void reading_writing(){ //function is used to waste time, to act like threads are accessing data
    int x = 0, T, i, j; 
    T = rand() % 20000; 
    for(i = 0; i < T; i++) 
        for(j = 0; j < T; j++) 
            x=i*j; 
}