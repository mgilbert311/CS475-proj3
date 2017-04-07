/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>
#include <stdlib.h>
//#include <time.h>

#define N 5	//number of philosophers and forks, should be arbitary
#define RAND_MAX 100
//TODO - locks must be declared and initialized here, locked at the start

mutex_t leftFork[N];
mutex_t rightFork[N];
mutex_t critSec = 0;
//mutex_t *leftFork = (mutex_t*)malloc(sizeof(mutex_t)*N);
//mutex_t *rightFork = (mutex_t*)malloc(sizeof(mutex_t)*N);

/**
 * Delay for a random amount of time
 * @param alpha delay factor
 */
void	holdup(int32 alpha)
{
	long delay = rand() * alpha;
	while (delay-- > 0)
		;	//no op
}

/**
 * Eat for a random amount of time
 */
void	eat()
{
	holdup(10000);
	//Unlock when we are done?
}

/**
 * Think for a random amount of time
 */
void	think()
{
	holdup(1000);
}



/**
 * Philosopher's code
 * @param phil_id philosopher's id
 */
void	philosopher(uint32 phil_id)
{
	//Not sure if this is what he meant
	//uint32 realID = &phil_id;
	uint32 left = phil_id;			//TODO - right fork
	uint32 right = phil_id % N;	//TODO - left fork
	//time_t t;
	while (TRUE)
	{
		srand(phil_id);

		if((rand() % RAND_MAX) > 30 ){	//think 70% of the time

			kprintf("Philosopher %u thinking: zzzzzzz \n", phil_id);
			think();
		}else{		//eat 30% of the time
			//acquire the forks
			mutex_lock(&critSec); //May not need this 
			if(leftFork[left] == FALSE){ //Lock is open
				//kprintf("Acquired left fork\n");
				mutex_lock(&leftFork[left]);
			}
			//Try to acquire other fork
			if(rightFork[right] == TRUE){ //Right is locked
				//Busy, drop forks
				//kprintf("Couldn't acquire other fork\n");
				mutex_unlock(&leftFork[left]);
				//continue; //Make decision again
			}
			if(leftFork[left] == TRUE && rightFork[right] == FALSE){ //Make sure the other is available and that the left Fork is taken
				//kprintf("Acquiring forks\n");
				//Left lock is already taken
				mutex_lock(&rightFork[right]);
				kprintf("Philosopher %u eating: MMMMMMM \n", phil_id); 
				eat();
				mutex_unlock(&leftFork[left]);
				mutex_unlock(&rightFork[right]);
			}
			kprintf("Just unlocked critSec\n");
			mutex_unlock(&critSec); //U
		}
	}
}

int	main(uint32 argc, uint32 *argv)
{
	//do not change
	ready(create((void*) philosopher, INITSTK, 15, "Ph1", 1, 0), FALSE);
	ready(create((void*) philosopher, INITSTK, 15, "Ph2", 1, 1), FALSE);
	ready(create((void*) philosopher, INITSTK, 15, "Ph3", 1, 2), FALSE);
	ready(create((void*) philosopher, INITSTK, 15, "Ph4", 1, 3), FALSE);
	ready(create((void*) philosopher, INITSTK, 15, "Ph5", 1, 4), FALSE);

	return 0;
}