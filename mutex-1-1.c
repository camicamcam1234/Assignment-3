// Cairo Crawford PantherID: 6389250
// Cedric Cherestal PantherID: 5512167
// Camila Castaneda PantherID: 6059028

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_UPDATES 4444

/* Struct a shared variable to store result */
struct shared_data {
    int value;  
};

/* Global shared variable */
struct shared_data *counter;
/* Mutex lock */
pthread_mutex_t mutex;

/* Thread1 function */
void *thread1() {
    int i = 0;
    int bonusCount = 0;
    while (i < MAX_UPDATES) {
        if (pthread_mutex_trylock(&mutex) == 0) { // entry section
            /* Do your Job!*/
           if (counter->value % 100 == 0) {
               counter->value += 100;
               bonusCount++;
           } else {
               counter->value++;
           }
            pthread_mutex_unlock(&mutex);
            i++;
        }
    }
    
    printf("thread1, got %d bonuses. \n"); // remainder section
    return NULL;
}

void *thread2() {
    int i = 0;
    while (i < MAX_UPDATES) {
        pthread_mutex_trylock(&mutex);
        
        counter->value++;
        pthread_mutex_trylock(&mutex);
        i++;
                   
    }

    printf("thread2 \n"); // remainder section
    return NULL;
}


int main() {
    pthread_t tid[2];
    int rc;

    /* Allocate memory for shared data */
    counter = (struct shared_data *) malloc(sizeof(struct shared_data));
    counter->value = 0;

    /* Initialize mutex lock */
    if ((pthread_mutex_init(&mutex, NULL))) {
        printf("Error occured when initialize mutex lock.");
        exit(0);
    }

    pthread_attr_t attr;
    if ((pthread_attr_init(&attr))) {
        printf("Error occured when initialize pthread_attr_t.");
        exit(0);
    }

    /* Create thread1 */
    if ((rc = pthread_create(&tid[0], &attr, thread1, NULL))) {
        fprintf(stderr, "ERROR: pthread_create, rc: %d\n", rc);
        exit(0);
    }

    /* Wait for threads to finish */
    pthread_join(tid[0], NULL);

 
    /* Clean up */
    pthread_mutex_destroy(&mutex);
    free(counter);
    pthread_exit(NULL);

    return 0;
}
