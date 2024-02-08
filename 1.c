#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;

int arr1[]= {2,4,6,8,1,3,5,7,9,12},arr2[10],pos=0;
int length = sizeof(arr1)/sizeof(arr1[0]);

void *Reader(void *arg)
{
    int i=0;
    pthread_mutex_lock(&mutex);
    while(i<2)
    {
        arr2[i]=arr1[pos];
        i++;
        pos++;
    }
    pthread_mutex_unlock(&mutex);
}

void * Writer(void *arg)
{
    pthread_mutex_lock(&mutex);
    printf("Generating.......\n");
    for(int j=0; j<2; j++)
    {
        printf("%d ",arr2[j]);
    }
    printf("\n");
    pthread_mutex_unlock(&mutex);
}


int main()
{
    int t1,t2;
    pthread_t thread1,thread2;
    printf("After printing numbers are : \n");
    while(pos<length)
    {
        t1=pthread_create(&thread1,NULL,&Reader,NULL);
        t2=pthread_create(&thread2,NULL,&Writer,NULL);
        if((t1!=0))
        {
            printf("Thread 1 couldn't create %d\n", t1);
        }
        pthread_join( thread1, NULL);
        if((t2!=0))
        {
            printf("Thread 2 couldn't create %d\n", t2);
        }
        pthread_join(thread2, NULL);
    }
    pthread_mutex_destroy(&mutex);
}
