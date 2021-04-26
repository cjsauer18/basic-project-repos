#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

//24 total semaphores
//16 for intersection paths

//straight paths  
sem_t N_str_E_str;
sem_t N_str_S_l;
sem_t N_str_W_l;
sem_t N_str_W_str;
sem_t W_str_E_l;
sem_t W_str_S_l;
sem_t W_str_S_str;
sem_t E_str_W_l;
sem_t E_str_N_l;
sem_t E_str_S_str;
sem_t S_str_N_l;
sem_t S_str_E_l;
sem_t N_str_W_l;

//left path intersecting semaphores
sem_t N_l_W_l;
sem_t N_l_E_l;
sem_t E_l_S_l;
sem_t W_l_S_l;
//four exiting 
//right turns, straight, and left turns intersect at exits
sem_t S_exit;
sem_t N_exit;
sem_t E_exit;
sem_t W_exit;


//four entering
//i feel like this is redudnant if queue strucuture is implemnented 
sem_t S_enter;
sem_t N_enter;
sem_t E_enter;
sem_t W_enter;




typedef struct directions {
	char dir_original;
	char dir_target;
} directions;

typedef struct Car {
    struct directions dir;
    int cid;
    float arrival_time;
    char direction;
}Car;

struct Car cars[] = {
    [0] = {{.dir_original = 'N', .dir_target = 'N'}, .cid = 0, .arrival_time = 1.1, .direction = 'S'},
    [1] = {{.dir_original = 'N', .dir_target = 'N'}, .cid = 1, .arrival_time = 2.0, .direction = 'S'},
    [2] = {{.dir_original = 'N', .dir_target = 'W'}, .cid = 2, .arrival_time = 3.3, .direction = 'L'},
    [3] = {{.dir_original = 'S', .dir_target = 'S'}, .cid = 3, .arrival_time = 3.5, .direction = 'S'},
    [4] = {{.dir_original = 'S', .dir_target = 'E'}, .cid = 4, .arrival_time = 4.2, .direction = 'L'},
    [5] = {{.dir_original = 'N', .dir_target = 'N'}, .cid = 5, .arrival_time = 4.4, .direction = 'S'},
    [6] = {{.dir_original = 'E', .dir_target = 'N'}, .cid = 6, .arrival_time = 5.7, .direction = 'L'},
    [7] = {{.dir_original = 'W', .dir_target = 'N'}, .cid = 7, .arrival_time = 5.9, .direction = 'R'}
};



