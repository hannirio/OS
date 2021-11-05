# OS
# 操作系统实验任务 #
## 物联网91 王轩 2196113382 ##

##一、基本要求：多次运行程序，观察输出顺序，解释现象：##
 
    #include< sys/types.h>   
    #include< sys/wait.h>  
    #include< stdio.h> 
    #include< unistd.h> 
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
    }
    else{
    pid1=getpid();
    printf("parent:pid=%d\n",pid);
    printf("parent:pid1=%d\n",pid1);
    wait(NULL);
    }
    return 0;
    }

实验结果：<img width="570" alt="1" src="https://user-images.githubusercontent.com/93147596/140454154-f1ebbe8a-0db5-4666-b503-78746fed1472.png">



现象解释：p>0时进入父进程，fork返回新创建子进程的进程ID；而在子进程中，fork返回0。

##去除wait后##
结果不变，



##二、定义全局变量，在父子进程中分别操作，观察实验结果并解释现象。##


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
    printf("mun=%d\n,&num=%d\n",num,&num);
    }
    else{
    pid1=getpid();
    printf("parent:pid=%d\n",pid);
    printf("parent:pid1=%d\n",pid1);
    num=13;
    num++;
    printf("mun=%d\n,&num=%d\n",num,&num);
    wait(NULL);
    }
    return 0;
  
实验结果：<img width="570" alt="11" src="https://user-images.githubusercontent.com/93147596/140454173-64ab3d95-d96c-4bcb-89fb-e1002d85c312.png">


实验解释：
全局变量在父子进程中内容不同，说明其各自存有一份变量，但是其地址相同，说明是虚拟地址。
父进程和子进程数据独自占有，不共享

##三、父子进程中运行不同的程序##
   
    //shiyan12.c
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
       execlp("./hello","hello",NULL);
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

    //Hello.c:
    #include <unistd.h>
    #include <stdio.h>
    extern char** environ;
    
    int main(void)
    {
    printf("hello pid=%d\n", getpid());
    return 0;
    }


实验结果：<img width="570" alt="12" src="https://user-images.githubusercontent.com/93147596/140454183-f63fb149-22c3-453a-8a2c-dc0ff693e254.png">

实验解释：exec函数可以把当前进程替换为一个新进程，且新进程与原进程有相同的PID。

##四、使用pthread实现多线程##
   
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

实验结果：<img width="570" alt="13" src="https://user-images.githubusercontent.com/93147596/140454194-50d51870-2404-4414-b041-2e57ee206b5b.png">







