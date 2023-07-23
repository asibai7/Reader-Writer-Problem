#include "readerwriter.h"
int main()
{
    rwlock_t lock;
    char rw;
    FILE *file;
    int error; //Flag to determine if threads fail to get created
    file = fopen("scenarios.txt", "r"); //opening file which contains input
    rwlock_init(&lock); //initialize lock
    pthread_t thread;
    if (file)
    {
        printf("Scenario Starts:\n"); 
        while (fscanf(file, "%c", &rw) != EOF) //scanning file for r and w
        {
            if (rw == 'r')
            {
                error = pthread_create(&thread, NULL, (void *)readThread, (void *)&lock); //if r, create a read thread
                if (error != 0)
                {
                    printf("Can't create thread.\n");
                    return 1;
                }
            }
            else if (rw == 'w') //if w, create a write thread
            {
                error = pthread_create(&thread, NULL, (void *)writeThread, (void *)&lock);
                if (error != 0)
                {
                    printf("Can't create thread.\n");
                    return 1;
                }
            }
        }
    }
    fclose(file); //close file
    pthread_exit(NULL); //exit threads
    return 0;
}