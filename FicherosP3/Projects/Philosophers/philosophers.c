#include <stdio.h> 
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define NR_PHILOSOPHERS 5

pthread_t philosophers[NR_PHILOSOPHERS];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond[NR_PHILOSOPHERS];
static int turn = 0;
//variable estática que determina el turno de cada filósofo


void init()
{
    int i;
    pthread_mutex_init(&mutex, NULL);

	for (i = 0; i < NR_PHILOSOPHERS; i++)
		pthread_cond_init(&cond[i], NULL);

    
}

void think(int i) {
    printf("Philosopher %d thinking... \n" , i);
    sleep(random() % 10);
    printf("Philosopher %d stopped thinking!!! \n" , i);

}

void eat(int i) {
    printf("Philosopher %d eating... \n" , i);
    sleep(random() % 5);
    printf("Philosopher %d is not eating anymore!!! \n" , i);

}

void toSleep(int i) {
    printf("Philosopher %d sleeping... \n" , i);
    sleep(random() % 10);
    printf("Philosopher %d is awake!!! \n" , i);
}

void* philosopher(void* i)
{
    int nPhilosopher = (int)i;
    int right = nPhilosopher;
    int left = (nPhilosopher - 1 == -1) ? NR_PHILOSOPHERS - 1 : (nPhilosopher - 1);
	int waitingTime = 0;
    while(1)
    {
        
        think(nPhilosopher);

		pthread_mutex_lock(&mutex);
        
		while (turn != nPhilosopher)
		{
			pthread_cond_wait(&cond[right], &mutex);
		}

		pthread_mutex_unlock(&mutex);

        eat(nPhilosopher);
        
		pthread_mutex_lock(&mutex);

		pthread_cond_signal(&cond[right]);
		pthread_cond_signal(&cond[left]);

		pthread_mutex_unlock(&mutex);

		turn = (turn == 0) ? NR_PHILOSOPHERS - 1 : (turn - 1);	//se avanza el turno
        
        toSleep(nPhilosopher);
   }

}

int main()
{
    init();
    unsigned long i;
    for(i=0; i < NR_PHILOSOPHERS; i++)
        pthread_create(&philosophers[i], NULL, philosopher, (void*)i);
    
    for(i=0; i<NR_PHILOSOPHERS; i++)
        pthread_join(philosophers[i],NULL);
    
    return 0;
} 
