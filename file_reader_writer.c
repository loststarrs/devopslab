#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

sem_t x,y;
pthread_t tid;
pthread_t writerThreads[100],readerThreads[100];
int readercount=0;

void* reader(void* param)
{
	FILE *f1;
	f1=(FILE *)param;
	char s;
	sem_wait(&x);
	readercount++;
	if(readercount==1)
		sem_wait(&y);
	
	printf("reader %d is inside\n",readercount);
	f1=fopen("textfile.txt","r");
   	while((fscanf(f1,"%c",&s))!=EOF){
   	printf("%c",s);
   	}
   	printf("\n");
   	fclose(f1);
	
	
	readercount--;
	if(readercount==0)
		sem_post(&y);
	sem_post(&x);
	printf("%d reader is leaving\n",readercount+1);
	return NULL;
}

void* writer(void* param)
{
	FILE *f2;
	f2=(FILE *)param;
	char s[25];
	int i;
	printf("Writer is trying to enter\n");
	sem_wait(&y);
	printf("Writer has entered\n");
	f2=fopen("textfile.txt","a");
   	printf("Enter the text to add to the file :");
   	fgets(s, sizeof(s), stdin);
   	fprintf(f2, "%s", s);
           
   	fclose(f2);
	sem_post(&y);
	printf("Writer is leaving\n");
	return NULL;
}

int main()
{
	int n2,i;
	char s[25];
        FILE *fp;
        fp=fopen("textfile.txt","w+");
        if(fp==NULL){
        	printf("Error in opening file\n");
        	fclose(fp);
        }
        fprintf(fp,"Hello World!!!");
        fclose(fp);
	

	printf("\n");
	
	sem_init(&x,0,1);
	sem_init(&y,0,1);
	
		pthread_create(&readerThreads[0],NULL,reader,(void *)fp);
		pthread_create(&writerThreads[0],NULL,writer,(void *)fp);
		pthread_create(&readerThreads[1],NULL,reader,(void *)fp);
	

		pthread_join(readerThreads[0],NULL);
		pthread_join(writerThreads[0],NULL);
		
		pthread_join(readerThreads[1],NULL);
	printf("Contenets of the file after writer updated it ..\n");
	fp=fopen("textfile.txt","r");
	if (fgets(s, sizeof(s), fp) != NULL) 
        printf("%s", s);
	
	return 0;
}
