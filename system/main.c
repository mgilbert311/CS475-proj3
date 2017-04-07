/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>
#include <stdlib.h>

#define N 5	//number of philosophers and forks, should be arbitary

//TODO - locks must be declared and initialized here
mutex_t *leftFork;
mutex_t *rightFork;

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
	uint32 right = ??;				//TODO - right fork
	uint32 left = ??;	//TODO - left fork

	while (TRUE)
	{
		//TODO
		//think 70% of the time
		//eat 30% of the time
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




/*  main.c  - main */
/*
//Do we erase this?
#include <xinu.h>
#include <stdio.h>

mutex_t lock = FALSE;

void    printchar(char c)
{
    mutex_lock(&lock);
    int i;
    for (i=0; i<10; i++)
        kprintf("%c", c);
    mutex_unlock(&lock);
}

int main(uint32 argc, uint32 *argv)
{
    //priority of process is input as the 3rd argument of create()
    ready(create((void*) printchar, INITSTK, 15, "P1", 1, 'A'), FALSE);
    ready(create((void*) printchar, INITSTK, 15, "P2", 1, 'B'), FALSE);

    return 0;
}
*/
