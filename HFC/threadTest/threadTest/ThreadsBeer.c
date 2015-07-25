#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

void error(char *msg,int i)
{
	fprintf(stderr, "%s %i: %s\n", msg,i, strerror(errno));
	exit(1);
}

int beers = 2000000;
pthread_mutex_t beers_lock = PTHREAD_MUTEX_INITILIZER;

void* drink_lots(void* a)
{
	int i;
	for(i=0; i<100000; i++)
	{
		pthread_mutex_lock(&beers_lock);
		beers = beers-1;
		pthread_mutex_lock(&beers_lock);
	}
	
	return NULL;
}


int main()
{
	pthread_t threads[20];
	int t;
	printf("%i bootles of beers on the wall\n%i bootles of beer\n", beers, beers);
	for(t=0; t<20; t++)
	{
		if(pthread_create(&threads[t],NULL,drink_lots,NULL)==-1)
			error("Cannot make threads", t);
	}
	
	void* result;
	for(t=0;t<20;t++)
	{
		if(pthread_join(threads[t],&result)==-1)
			error("Cannot join thread",t);
	}
	
	printf("There are now %i bottles of beer on the wall\n",beers);
			
	return 0;
}




