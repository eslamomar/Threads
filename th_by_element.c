#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
void *clc (void* x);
int a[10][10];
int b[10][10];
int r[10][10];
typedef struct v 
{
int jj;
int kk;
int nn;
}m_v;

int  main ()
{

system ("clear");
//label:
m_v el[10];
pthread_t th[50];
printf("\n\t\t\tMatrix Multiblication\n");
printf("\n\t\t\tEntering First Matrix\n");
int i,j,k,m1,n1,m2,n2,y;

  printf("\nNumbers of rows   =");
	scanf("%d",&m1);
  printf("\nNumbers of columns=");
	scanf("%d",&n1);

printf("\n\tEnter matrix elements\n A= \n");
for (i=0;i<m1;i++)
{
	for (j=0;j<n1;j++)
	{
	scanf("%d",&a[i][j]);
	}
}

//Second matrix

printf("\n\tEntering Second Matrix\n");

  printf("\nNumbers of rows   =");
	scanf("%d",&m2);
  printf("\nNumbers of columns=");
	scanf("%d",&n2);

printf("\n\tEnter matrix elements \n B= \n");
for (i=0;i<m2;i++)
{
	for (j=0;j<n2;j++)
	{
	scanf("%d",&b[i][j]);
	}
}
// handle error of dimensional
if (n1 != m2)
{
printf("\ndimensional error\n");
exit(-1);
}
//show first matrix
printf("\n\t First matrix A=\n");
for (i=0;i<m1;i++)
{putchar('\n');
	for (j=0;j<n1;j++)
	{
	printf("%d   ",a[i][j]);
	}
}
//show second matrix
printf("\n\t Second matrix B=\n");
for (i=0;i<m2;i++)
{putchar('\n');
	for (j=0;j<n2;j++)
	{
	printf("%d   ",b[i][j]);
	}
}   
//initializing result matrix

for (j=0;j<m1;j++)
{putchar('\n');
	for (i=0;i<n2;i++)
	{
	r[j][i]=0;
	}
} 

clock_t clk_s,clk_e,time;

//operation of matrix multiplication

printf("\n\t\t The Rusult\n");
int t=0;
clk_s=clock();
for (k=0;k<m1;k++)
{
	for (j=0;j<n2;j++)
	{
 el[t].jj=j;  
el[t].kk=k;
el[t].nn=n1;
int th_c=pthread_create(&th[t], NULL, clc,(void*)&el[t]);
 	if (th_c !=0){
	printf("Error in thread creation");
	exit(-1);
	}	
	t++;	
	}
}
t=0;
for (k=0;k<m1;k++)
{
	for (j=0;j<n2;j++)
	{
	pthread_join(th[t],(void **)&y);
	t++;    // t is threads number
	r[k][j]=y;	

	}
}

clk_e=clock();

time=(clk_e-clk_s);///  CLOCKS_PER_SEC = 1000,000;


//printing results
for (j=0;j<m1;j++)
{putchar('\n');
	for (i=0;i<n2;i++)
	{
	printf("%d   ",r[j][i]);
	}
} 
printf ("\nNumber of threads = %d\n",t);
printf("Execution time s =%ld Micro seconds\n",time);
putchar('\n');


}
void *clc (void* x)
{

int i;
int *p_j=(int*) x; //according to j
int *p_k=p_j+1;   //according to k
int *p_n1=p_j+2; //according to n1
 		for (i=0;i<*p_n1;i++)
		{
 		r[*p_k][*p_j]+=a[*p_k][i]*b[i][*p_j];
		}

i=r[*p_k][*p_j];
pthread_exit((void*)i);
}




