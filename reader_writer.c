#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

sem_t x,y;
pthread_t tid;
pthread_t writerThreads[100],readerThreads[100];
int readercount=0;

void* reader(void* param)
{
	sem_wait(&x);
	readercount++;
	if(readercount==1)
		sem_wait(&y);
	sem_post(&x);
	printf("%d reader is inside\n",readercount);
	usleep(3);
	sem_wait(&x);
	readercount--;
	if(readercount==0)
		sem_post(&y);
	sem_post(&x);
	printf("%d reader is leaving\n",readercount+1);
	pthread_exit(NULL);
}

void* writer(void* param)
{
	printf("Writer is trying to enter\n");
	sem_wait(&y);
	printf("Writer has entered\n");
	sem_post(&y);
	printf("Writer is leaving\n");
	pthread_exit(NULL);
}

int main()
{
	int n2,i;
	printf("Enter the number of readers: ");
	scanf("%d",&n2);
	printf("\n");
	int n1[n2];
	sem_init(&x,0,1);
	sem_init(&y,0,1);
	for(i=0;i<n2;i++)
	{
		pthread_create(&readerThreads[i],NULL,reader,NULL);
		pthread_create(&writerThreads[i],NULL,writer,NULL);
	}
	for(i=0;i<n2;i++)
	{
		pthread_join(writerThreads[i],NULL);
		pthread_join(readerThreads[i],NULL);
	}
	return 0;
}
