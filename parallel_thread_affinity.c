
#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include<errno.h>
#define NTHREADS 5
double area,area1,area2,area3,area4,pi;
unsigned long long  int n=1000000;

void *thread_f1(void *null) 
{
	unsigned long long i;
	double	x=0;
        for(i=0; i<250000; i++)
	{
		x = (i+0.5)/n;
		area1 += 4.0/(1.0 + x*x);
	}	
	pthread_exit(NULL);
}                      
void *thread_f2(void *null) 
{
	unsigned long long i;
       double  x=0.0;
	for(i=250000; i<500000; i++)
	{
		x = (i+0.5)/n;
		area2 += 4.0/(1.0 + x*x);
	}
	pthread_exit(NULL);
}                      
void *thread_f3(void *null) 
{
	unsigned long long i;
	double	 x=0.0;
	for(i=500000; i<750000; i++)
	{
		x = (i+0.5)/n;
		area3 += 4.0/(1.0 + x*x);
	}
	pthread_exit(NULL);
}                      
void *thread_f4(void *null) 
{
	unsigned long long  i;
	double	x=0.0;
	for(i=750000; i<n; i++)
	{
		x = (i+0.5)/n;
		area4 += 4.0/(1.0 + x*x);
	}
	pthread_exit(NULL);
}                      

int main(int argc, char *argv[]) {
	int rc, i, j, detachstate;

	long int a,b,ret;
	unsigned long long int diff,t1,t2;
	pthread_t tid,tid1,tid2,tid3;
	pthread_attr_t attr1,attr2,attr3,attr4;
	struct timeval tval;
        struct timezone tzone;
	cpu_set_t cpuset1;


	pthread_attr_init(&attr1);
	pthread_attr_setdetachstate(&attr1, PTHREAD_CREATE_JOINABLE);
	pthread_attr_init(&attr2);
	pthread_attr_setdetachstate(&attr2, PTHREAD_CREATE_JOINABLE);
	pthread_attr_init(&attr3);
	pthread_attr_setdetachstate(&attr3, PTHREAD_CREATE_JOINABLE);
	pthread_attr_init(&attr4);
	pthread_attr_setdetachstate(&attr4, PTHREAD_CREATE_JOINABLE);
	
	CPU_ZERO(&cpuset1);
	CPU_SET(0,&cpuset1);
        ret=pthread_attr_setaffinity_np(&attr1,sizeof(cpu_set_t),&cpuset1);
	if(ret!=0)
	{
            perror("error in set_affinity 1\n");
	    exit(1);
	}
	
	CPU_ZERO(&cpuset1);
	CPU_SET(1,&cpuset1);
        ret=pthread_attr_setaffinity_np(&attr2,sizeof(cpu_set_t),&cpuset1);
	if(ret!=0)
	{
            perror("error in set_affinity 2\n");
	    exit(2);
	}
	
	CPU_ZERO(&cpuset1);
	CPU_SET(2,&cpuset1);
        ret=pthread_attr_setaffinity_np(&attr3,sizeof(cpu_set_t),&cpuset1);
	if(ret!=0)
	{
            perror("error in set_affinity 3\n");
	    exit(3);
	}
	
	CPU_ZERO(&cpuset1);
	CPU_SET(3,&cpuset1);
        ret=pthread_attr_setaffinity_np(&attr4,sizeof(cpu_set_t),&cpuset1);
	if(ret!=0)
	{
            perror("error in set_affinity 4\n");
	    exit(4);
	}
        
	gettimeofday(&tval,&tzone);
	t1=tval.tv_sec*1000000+tval.tv_usec;
	printf(" %d  %d \n",tval.tv_sec,a=tval.tv_usec);

	  rc = pthread_create(&tid, &attr1, thread_f1, NULL);
	  if (rc) 
	  {              
	         printf("ERROR; return code from pthread_create() is %d\n", rc);
		 exit(5);
	  }
          rc = pthread_create(&tid1, &attr2, thread_f2, NULL);
          if (rc) 
	  {              
		printf("ERROR; return code from pthread_create() is %d\n", rc);
		exit(6);
	  }
	  rc = pthread_create(&tid2, &attr3, thread_f3, NULL);
	  if (rc) 
	  {              
	         printf("ERROR; return code from pthread_create() is %d\n", rc);
		 exit(7);
	  }
	  rc = pthread_create(&tid3, &attr4, thread_f4, NULL);
	  if (rc) 
	  {              
	         printf("ERROR; return code from pthread_create() is %d\n", rc);
		 exit(8);
	  }
          rc = pthread_join(tid, NULL);
          if (rc) 
	  {
	       printf("ERROR; return code from pthread_join() is %d\n", rc);
	       exit(9);
	  }
     //   gettimeofday(&tval,&tzone);
//	printf(" %d  %d \n",tval.tv_sec,tval.tv_usec);
        rc = pthread_join(tid1, NULL);
        if (rc) 
	{
		printf("ERROR; return code from pthread_join() is %d\n", rc);
	        exit(10);
	}
        rc = pthread_join(tid2, NULL);
        if (rc) 
	{
		printf("ERROR; return code from pthread_join() is %d\n", rc);
	        exit(11);
	}
        rc = pthread_join(tid3, NULL);
        if (rc) 
	{
		printf("ERROR; return code from pthread_join() is %d\n", rc);
	        exit(12);
	}
	area=area1+area2+area3+area4;
	pi=area/n;
        gettimeofday(&tval,&tzone);
	t2=tval.tv_sec*1000000+tval.tv_usec;
	printf(" %d  %d \n",tval.tv_sec,b=tval.tv_usec);
	printf("diff=%llu\n",t2-t1);
	printf("pi=%.20lf\n",pi);


	pthread_attr_destroy(&attr1);
	pthread_attr_destroy(&attr2);
	pthread_attr_destroy(&attr3);
	pthread_attr_destroy(&attr4);
	pthread_exit(NULL);

}
