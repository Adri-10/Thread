#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int arr[20],i=0,j=0;
void *Reader(void *arg)
{
	pthread_mutex_lock(&mutex);
	printf("Enter 5 array integers: \n");
	for(i=0; i<5; i++){
		scanf("%d",&arr[i]);
	}
	pthread_mutex_unlock(&mutex);
}

void *Writter(void *arg )
{
	pthread_mutex_lock(&mutex);
	printf("The numbers are: \n");
	printf("Generating.......\n");
	for(j=0; j<5; j++){
		printf("%d ",arr[j]);
	}
	printf("\n");
	pthread_mutex_unlock(&mutex);
}

int main()
{
	int t1,t2;
	pthread_t thread1, thread2;

	if((t1=pthread_create(&thread1,NULL,&Reader,NULL)))
	{
		printf("Thread 1 couldn't create %d\n", t1);
	}
	pthread_join( thread1, NULL);
	if((t2=pthread_create( &thread2,NULL,&Writter,NULL )))
	{
		printf("Thread 2 couldn't create %d\n", t2);
	}
	pthread_join( thread2, NULL);
	pthread_mutex_destroy(&mutex);
	exit(0);
}
