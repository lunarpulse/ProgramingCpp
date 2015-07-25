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

int beers = 200000000;
pthread_mutex_t beers_lock = PTHREAD_MUTEX_INITIALIZER;

void* drink_lots(void* a)
{
	int i;
	pthread_mutex_lock(&beers_lock);
	for(i=0; i<10000000; i++)
	{
		//pthread_mutex_lock(&beers_lock);
		beers--;
		//pthread_mutex_unlock(&beers_lock);
	}
	pthread_mutex_unlock(&beers_lock);
	printf("beers= %i\n",beers);
	return NULL;
}


int main()
{
	pthread_t threads[20];
	int t;
	printf("%i bottles of beers on the wall\n%i bootles of beer\n", beers, beers);
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




