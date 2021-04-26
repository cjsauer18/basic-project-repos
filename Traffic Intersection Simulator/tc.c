#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include "tc.h"
#include "common.h"


int start = 0;

typedef struct queue {
    int front;
    int back;
    int size;
    int maxsize;
    int *items;
} queue;

static int STRAIGHT_CROSS_TIME = 2;
static int LEFT_TURN_TIME = 3;
static int RIGHT_TURN_TIME = 1;

//Queue related
int top(struct queue *Q) {
    if (Q->size == 0) {
        printf("Queue is empty, cannot retrieve top");
        return -1;
    }
    return Q->items[0];
}
void enqueue(struct queue *Q, int item) {
    if (Q->size < Q->maxsize) {
        Q->items[Q->front++] = item;
        Q->size++;
    }
    else {
        printf("Queue is full");
    }

}
void dequeue(struct queue *Q) {
    if (Q->size != 0) {
        for (int i = 0; i < Q->size ; ++i) {
            Q->items[i] = Q->items[i + 1];
        }
        Q->items[Q->front] = 0;
        Q->front--;
        Q->size--;
    }
    else {
        printf("Queue is empty, cannot dequeue");
    }
}


//checks the second element of the queue. Used for determining if two cars traveling in the same direction can
//pass without car 2 waiting on car 1 to free its locks. 
int isSecond(struct queue* Q, int cid) {
    if (cid == Q->items[0 + 1]) 
        return 1;
    else
        return 0;
}

struct queue cross_queue;
struct queue line_queue_N; 
struct queue line_queue_S; 
struct queue line_queue_E; 
struct queue line_queue_W;

//Helper for debugging queues
void printQueues(int id, int mode) {
    if(mode == 0)
        printf("Exiting \n");
    if (mode == 1)
        printf("entering \n");


    printf("thread calling queue: %d \n", id);
    printf("Queue N: ");

    for (int i = 0; i < 5; ++i) {
        printf(" %d ", line_queue_N.items[i]);
    }
    printf("\n");
    printf("Queue S: ");

    for (int i = 0; i < 5; ++i) {
        printf(" %d ", line_queue_S.items[i]);
    }
    printf("\n");
    printf("Queue E: ");

    for (int i = 0; i < 5; ++i) {
        printf(" %d ", line_queue_E.items[i]);
    }
    printf("\n");
    printf("Queue W: ");

    for (int i = 0; i < 5; ++i) {
        printf(" %d ", line_queue_W.items[i]);
    }
    printf("\n");

    printf("CROSS Q: ");

    for (int i = 0; i < 5; ++i) {
        printf(" %d ", cross_queue.items[i]);
    }
    printf("\n");
}


struct queue* newQueue(int size)
{
    struct queue* pt = NULL;
    pt = (struct queue*)malloc(sizeof(struct queue));

    pt->items = (int*)malloc(size * sizeof(int));
    pt->maxsize = size;
    pt->front = 0;
    pt->back = -1;
    pt->size = 0;

    return pt;
}


//Utility function. Searches for the semaphores that are in the path of travel for the car and points to their address. 
//Sets direction and number of lock pointers.
void retrieveCorrespondingLocks(char original, char target, sem_t ** locks, char* direction, int *numOfLocks) {

    *numOfLocks = 0;
    //SEARCH FOR LOCKS

    //straight
    if (original == 'N' && target == 'N') {
        locks[*numOfLocks] = &N_str_E_str;
        (*numOfLocks)++;
        locks[*numOfLocks] = &N_str_W_str;
        (*numOfLocks)++;
        locks[*numOfLocks] = &N_str_S_l;
        (*numOfLocks)++;
        locks[*numOfLocks] = &N_str_W_l;
        (*numOfLocks)++;
        //locks[*numOfLocks] = &S_enter;
       // (*numOfLocks)++;
        locks[*numOfLocks] = &N_exit;
        *direction = 'S';
    }
    //right
    else if (original == 'N' && target == 'E') {
        //locks[*numOfLocks] = &S_enter;
       // (*numOfLocks)++;
        locks[*numOfLocks] = &E_exit;
        *direction = 'R';
    }
    //left
    else if (original == 'N' && target == 'W') {
        locks[*numOfLocks] = &E_str_N_l;
        (*numOfLocks)++;
        locks[*numOfLocks] = &S_str_N_l;
        (*numOfLocks)++;
        locks[*numOfLocks] = &N_l_W_l;
        (*numOfLocks)++;
        locks[*numOfLocks] = &N_l_E_l;
        (*numOfLocks)++;
       // locks[*numOfLocks] = &S_enter;
       // (*numOfLocks)++;
        locks[*numOfLocks] = &W_exit;
        *direction = 'L';
    }

    //straight
    else if (original == 'S' && target == 'S') {
        locks[*numOfLocks] = &W_str_S_str;
        (*numOfLocks)++;
        locks[*numOfLocks] = &E_str_S_str;
        (*numOfLocks)++;
        locks[*numOfLocks] = &S_str_N_l;
        (*numOfLocks)++;
        locks[*numOfLocks] = &S_str_E_l;
        (*numOfLocks)++;
       // locks[*numOfLocks] = &N_enter;
       // (*numOfLocks)++;
        locks[*numOfLocks] = &S_exit;
        *direction = 'S';
    }
    //left
    else if (original == 'S' && target == 'E') {
        locks[*numOfLocks] = &N_str_S_l;
        (*numOfLocks)++;
        locks[*numOfLocks] = &W_str_S_l;
        (*numOfLocks)++;
        locks[*numOfLocks] = &E_l_S_l;
        (*numOfLocks)++;
        locks[*numOfLocks] = &W_l_S_l;
        (*numOfLocks)++;
        //locks[*numOfLocks] = &N_enter;
        //(*numOfLocks)++;
        locks[*numOfLocks] = &E_exit;
        *direction = 'L';
    }
    //right
    else if (original == 'S' && target == 'W') {
        //(*numOfLocks)++;
        //locks[*numOfLocks] = &N_enter;
       // (*numOfLocks)++;
        locks[*numOfLocks] = &W_exit;
        *direction = 'S';
    }

    //left
    if (original == 'E' && target == 'N') {
        locks[*numOfLocks] = &W_str_E_l;
        (*numOfLocks)++;
        locks[*numOfLocks] = &S_str_E_l;
        (*numOfLocks)++;
        locks[*numOfLocks] = &N_l_E_l;
        (*numOfLocks)++;
        locks[*numOfLocks] = &E_l_S_l;
        (*numOfLocks)++;
       // locks[*numOfLocks] = &W_enter;
        //(*numOfLocks)++;
        locks[*numOfLocks] = &N_exit;
        *direction = 'L';
    }
    //right
    else if (original == 'E' && target == 'S') {
       // (*numOfLocks)++;
        //locks[*numOfLocks] = &W_enter;
        //(*numOfLocks)++;
        locks[*numOfLocks] = &S_exit;
        *direction = 'R';
    }
    //straight
    else if (original == 'E' && target == 'E') {
        locks[*numOfLocks] = &N_str_E_str;
        (*numOfLocks)++;
        locks[*numOfLocks] = &E_str_W_l;
        (*numOfLocks)++;
        locks[*numOfLocks] = &E_str_N_l;
        (*numOfLocks)++;
        locks[*numOfLocks] = &E_str_S_str;
        (*numOfLocks)++;
       // locks[*numOfLocks] = &W_enter;
       // (*numOfLocks)++;
        locks[*numOfLocks] = &E_exit;
        *direction = 'S';
    }


    //right
    if (original == 'W' && target == 'N') {
       // (*numOfLocks)++;
       // locks[*numOfLocks] = &E_enter;
       // (*numOfLocks)++;
        locks[*numOfLocks] = &N_exit;
        *direction = 'R';
    }
    //left
    else if (original == 'W' && target == 'S') {
        locks[*numOfLocks] = &N_str_W_l;
        (*numOfLocks)++;
        locks[*numOfLocks] = &E_str_W_l;
        (*numOfLocks)++;
        locks[*numOfLocks] = &N_l_W_l;
        (*numOfLocks)++;
        locks[*numOfLocks] = &W_l_S_l;
        (*numOfLocks)++;
       // locks[*numOfLocks] = &E_enter;
       // (*numOfLocks)++;
        locks[*numOfLocks] = &S_exit;
        *direction = 'L';
    }
    //straight
    else if (original == 'W' && target == 'W') {
        locks[*numOfLocks] = &N_str_W_str;
        (*numOfLocks)++;
        locks[*numOfLocks] = &W_str_E_l;
        (*numOfLocks)++;
        locks[*numOfLocks] = &W_str_S_l;
        (*numOfLocks)++;
        locks[*numOfLocks] = &W_str_S_str;
        (*numOfLocks)++;
      //  locks[*numOfLocks] = &E_enter;
       // (*numOfLocks)++;
        locks[*numOfLocks] = &S_exit;
         *direction = 'S';
    }

 

}

//Utility function for setting the right travel time for each direction of travel.
void acquireTime(char *direction, int *time) {
    if (*direction == 'L') {
        *time = LEFT_TURN_TIME;
    }
    else if (*direction == 'S') {
        *time = STRAIGHT_CROSS_TIME;
    }
    else if (*direction == 'R') {
        *time = RIGHT_TURN_TIME;
    }
}


//This function handles all the necessary conditions for a car once it has arrived at the intersection. Abiding by the rules of 
//stop sign intersections, all cars present follow a queue order. Once a car has arrived, it will spin wait until it is first in line in the cross queue to 
//begin searching for the needed semaphore locks to cross.
void arriveIntersection(struct Car* car, sem_t** locks, int* time, char* direction, int *numOfLocks) {

    //DEARLOCK AVOIDANCE
    //A car should not serach for semaphores until it is the first in line to do so, otherwise order of requesting semaphores is no longer FIFO due to random nature of sem_wait
    while (car->cid != top(&cross_queue)) {

        //In that period of time where the code from the thread ahead of a current thread is inside the crossing function where it is (spinning), there is a chance for a current thread to
        //leave earlier for the car behind it if a condition holds.
        //1. There are no other cars at the intersection.
        //2. This is the second car in the queue.

        //(The lag in dequeueing the crossing element allows for a window of time to have this statement be valid for a car)

        if ((isSecond(&cross_queue, car->cid) && top(&cross_queue) != car->cid) && (car->dir.dir_original == cars[top(&cross_queue)].dir.dir_original)){// && car->dir.dir_target == cars[top(&cross_queue)].dir.dir_target)){
            *direction = car->direction;//direciton of first car (hard code into array)
        //Aquire appropriate time for crossing time.  

            *numOfLocks = -1;
            acquireTime(direction, time);
            return; //Car does not need to proceed any further. 

        }

    }

    retrieveCorrespondingLocks(car->dir.dir_original, car->dir.dir_target, locks, direction, numOfLocks);//Helper finds and points to the correpsonding locks needed.
    acquireTime(direction, time);


    //call sem wait to hold the semaphores needed to cross the intersection
    int i = 0;
    while (i <= *numOfLocks) {
        sem_wait(&(*locks[i]));
        i++;
    }
}
//This function spins for the designated amount of time depending on the direction that the car turns.
void crossIntersection(int time, Car *car) {

    printf("Time: %f : Car %d (-> %c -> %c) crossing \n", GetTime()-start, car->cid, car->dir.dir_original, car->dir.dir_target);
    Spin(time);
 
}//only for the beginning semaphore, the head of line lock should be released when entering intersection



 //Releases the locks. If a car is following the other car in the line, then the number of locks is set to -1 and returns without releasing any locks. 
void exitIntersection(sem_t** locks, int numOfLocks, Car* car, int *time){
    printf("Time: %f : Car %d (->%c -> %c) exiting \n", GetTime()-start, car->cid, car->dir.dir_original, car->dir.dir_target);

    int i = 0;
    if(numOfLocks == -1)
        return;
    while (i <= numOfLocks) {
        sem_post(&(*locks[i]));//lock is a pointer to a pointer. So I need to dereference the pointer, and get the address of that 
        i++;
    }
}
    

//takeCar is called by thread and the multithreading begins here. 
//A queue pointer is initlaized for the correpsonding direction of entry from the intersection, an enter semaphore pointer for the direction of entry
//A semaphore lock pointer array is initialzied as well as other metrics needed for setting the approriate direction.
void takeCar(void *carFromThread) {
    Car *car = (struct Car*) carFromThread;//casting void ptr (address pass to thread) to a car pointer
    int* numOfLocks = malloc(sizeof(int));
    sem_t* beginSemPtr;
    queue* queuePtr;
    sem_t* locks[10];
    char *direction = malloc(sizeof(char));
    int *time = malloc(sizeof(int));

    //Put car into lane queue

    //Designate which lane the thread/car is coming from and point to corresponding sempahore and enqueue in lane queue.
    char arrivingDirection = car->dir.dir_original;
    if (arrivingDirection == 'N') {
        enqueue(&line_queue_S, car->cid);
        queuePtr = &line_queue_S;
        beginSemPtr = &S_enter;
    }
    else if (arrivingDirection == 'S') {
        enqueue(&line_queue_N, car->cid);
        queuePtr = &line_queue_N;
        beginSemPtr = &N_enter;
    }
    else if (arrivingDirection == 'E') {
        enqueue(&line_queue_W, car->cid);
        queuePtr = &line_queue_W;
        beginSemPtr = &W_enter;
    }
    else if (arrivingDirection == 'W') {
        enqueue(&line_queue_E, car->cid);
        queuePtr = &line_queue_E;
        beginSemPtr = &E_enter;
    }

    //while car is waiting to be up next in line (for lane, not intersection), spin.
    //this designates us some time to not request a semaphore, thereby mititating chance of car that is not in front of queue from obtaining front lock 

    while (top(queuePtr) != car->cid){} //any car that is in a lane must wait to acquire the front of line lock


    //Hold the front of line lock which enables the car to enter the cross queue.
    sem_wait(&(*beginSemPtr)); 
    enqueue(&cross_queue, car->cid);//enter cross queue
    printf("Time: %f : Car %d (->%c -> %c) arriving \n", GetTime()-start, car->cid, car->dir.dir_original, car->dir.dir_target);

    dequeue(queuePtr);//the second we dequeue, the next-up thread/car within the same lane will wake up and try to acquire lock
    sem_post(&(*beginSemPtr));//return lock
    arriveIntersection(car, locks, time, direction, numOfLocks);//begin acquiring locks
    crossIntersection(*time, car);
    dequeue(&cross_queue);

    exitIntersection(locks, *numOfLocks, car, time); //post locks
    //dequeue(&cross_queue);

}



int main(void) {

    //initialize semaphores
    sem_init(&N_str_E_str, 0, 1);
    sem_init(&N_str_S_l, 0, 1);
    sem_init(&N_str_W_l, 0, 1);
    sem_init(&N_str_W_str, 0, 1);
    sem_init(&W_str_E_l, 0, 1);
    sem_init(&W_str_S_l, 0, 1);
    sem_init(&W_str_S_str, 0, 1);
    sem_init(&E_str_W_l, 0, 1);
    sem_init(&E_str_N_l, 0, 1);
    sem_init(&E_str_S_str, 0, 1);
    sem_init(&S_str_N_l, 0, 1);
    sem_init(&S_str_E_l, 0, 1);
    sem_init(&S_exit, 0, 1);
    sem_init(&N_exit, 0, 1);
    sem_init(&E_exit, 0, 1);
    sem_init(&W_exit, 0, 1);
    sem_init(&N_enter, 0, 1);
    sem_init(&S_enter, 0, 1);
    sem_init(&E_enter, 0, 1);
    sem_init(&W_enter, 0, 1);
    sem_init(&N_l_W_l, 0, 1);
    sem_init(&N_l_E_l, 0, 1);
    sem_init(&E_l_S_l, 0, 1);
    sem_init(&W_l_S_l, 0, 1);

    //car array
    struct Car* carptr = cars;
    float previous_time = 0;
    int counter = 0;


    int startingTime = GetTime();
    start = startingTime;
    //initialize queues
    struct queue* Q1 = newQueue(10);
    struct queue* Q2= newQueue(10);
    struct queue* Q3 = newQueue(10);
    struct queue* Q4 = newQueue(10);
    struct queue* Q5 = newQueue(10);

    line_queue_E = *Q1;
    line_queue_N = *Q2;
    line_queue_W = *Q3;
    line_queue_S = *Q4;
    cross_queue = *Q5;

    pthread_t threads[8];
    pthread_t* threadptr;
    threadptr = threads;
    while (counter < 8) {
        //arrival time
        Spin(carptr->arrival_time - previous_time);
        previous_time = carptr->arrival_time;
  
        pthread_create(threadptr, NULL, (void*)takeCar, carptr);
        threadptr++;
        carptr++;
        counter++;
    }
    for (int i = 0; i < 8; ++i) {
        pthread_join(threads[i], NULL);//wait until threads are finished
    }
    return 0;
}

