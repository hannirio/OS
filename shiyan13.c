#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int arr[500];
int s1=0;
int s2=0;
pthread_mutex_t lock;

void *myfunc1(void *args)
{
    int i;
    char *name=(char *)args;
    for(i=1;i<250;i++)
    s1+=arr[i];
    
    return NULL;
}

void *myfunc2(void *args)
{
    int i;
    char *name=(char *)args;
    for(i=250;i<500;i++){
    pthread_mutex_lock(&lock);
    s2+=arr[i];
    pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main()
{
    int i;
    for(i=0;i<500;i++)
    arr[i]=i;

    pthread_t th1,th2,th3;
    pthread_mutex_init(&lock,NULL);

    pthread_create(&th1,NULL,myfunc1,NULL);
    pthread_create(&th2,NULL,myfunc2,NULL);
    pthread_create(&th3,NULL,myfunc2,NULL);

    pthread_join(th1,NULL);
    pthread_join(th2,NULL);
    pthread_join(th3,NULL);

    printf("s1=%d,s2=%d\ns1+s2=%d\n",s1,s2,s1+s2);
    return 0;
}
