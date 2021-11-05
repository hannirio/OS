#include<sys/types.h>   
#include<sys/wait.h>  
#include<stdio.h> 
#include<unistd.h> 

int num;
int main()  
{
    pid_t pid,pid1;  
    pid=fork();    
    if(pid<0){
    fprintf(stderr,"Fork Failed");
    return 1;
    }

    else if(pid==0){
        pid=getpid();
        printf("child:pid=%d\n",pid);
        printf("child:pid1=%d\n",pid1);
        num++;
        printf("mun=%d\n&num=%d\n",num,&num);
    }
    else{
        pid1=getpid();
        printf("parent:pid=%d\n",pid);
        printf("parent:pid1=%d\n",pid1);
        num=13;
        num++;
        printf("mun=%d\n&num=%d\n",num,&num);
        wait(NULL);
    }
    return 0;
}
