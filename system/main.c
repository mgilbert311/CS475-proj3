/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>
#include <stdlib.h>
//#include <time.h>

#define N 5	//number of philosophers and forks, should be arbitary
#define RAND_MAX 100
//TODO - locks must be declared and initialized here, locked at the start

mutex_t forks[N] = {};
//mutex_t rightFork[N];	
mutex_t critSec = FALSE;
mutex_t talk = FALSE;
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
	//uint32 realID = phil_id;
	/*int i;
	for (i = 0; i < N; ++i)
	{
	kprintf("fork [%d] = %u\n", i, forks[i]);
	}
	*/
	//kprintf("phil_id = %u\n", phil_id);
	//kprintf("value of critsec= %u\n", critSec);
	//kprintf("value of talk= %u\n", talk);


	uint32 left = phil_id;			//TODO - right fork
	//uint32 right = phil_id % N;	//TODO - left fork

	uint32 right = phil_id + 1;	//TODO - left fork
	//time_t t;
	srand(phil_id);

	while (TRUE)
	{

		//kprintf("begin while\n");
		//mutex_lock(&critSec); //May not need this 
		//kprintf("value of critsec= %u\n", critSec);
		if((rand() % RAND_MAX) > 30 ){	//think 70% of the time
			mutex_lock(&talk); //May not need this 
			kprintf("Philosopher %u thinking: zzzzzzz \n", phil_id);
			mutex_unlock(&talk);
			think();

		}else{		//eat 30% of the time
			//acquire the forks
			//kprintf("value of right fork = %u\n", forks[right]);
			if(forks[left] == 0){ //Lock is open
				mutex_lock(&forks[left]);
				//kprintf("Acquired left fork\n");

			}
			//Try to acquire other fork
			if(forks[right] == 1){ //Right is locked
				//Busy, drop forks
				mutex_unlock(&forks[left]);
				//kprintf("Couldn't acquire other fork\n");

				//continue; //Make decision again
			}
			if(forks[left] == 1 && forks[right] == 0){ 
			//Make sure the other is available and that the left Fork is taken
				//kprintf("Acquiring forks\n");
				//Left lock is already taken
				mutex_lock(&forks[right]);
				mutex_lock(&talk); //May not need this 

				kprintf("Philosopher %u eating: MMMMMMM \n", phil_id); 
				mutex_unlock(&talk); //U

				eat();
				mutex_unlock(&forks[left]);
				mutex_unlock(&forks[right]);
			}
			//kprintf("Just unlocked critSec\n");
		}

			//mutex_unlock(&critSec); //May not need this 
			//kprintf("value of critsec after= %u\n", critSec);


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