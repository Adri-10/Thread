#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include <semaphore.h>
#include <pthread.h>

int arr[20],i,j;
int sum=0;

sem_t mutex;
void *runner(void *arg)
{
    sem_wait(&mutex);
    sleep(1);
    int n;
    printf("Enter a integer want to sum up: \n");
    scanf("%d",&n);
    sum=0;

    for(int i=1; i<=n; i++)
    {
        sum+=i;
    }
    printf("summation: %d\n",sum);
    sem_post(&mutex);
}

int main()
{
    pthread_t thread[20];
    sem_init(&mutex,0,1);

    for(int i=0;i<5;i++)
    {
        int t=pthread_create(&thread[i],NULL,&runner,NULL);
        if((t!=0))
        {
            printf("Thread couldn't create %d\n",t);
        }
        pthread_join(thread[i], NULL);
    }
    sem_destroy(&mutex);
}
