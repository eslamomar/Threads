#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
void *clc (void* x);
int a[10][10];
int b[10][10];
int r[10][10];
int k[10][10];
typedef struct v 
{
//int jj;
int kk;
int nn_1;
int nn_2;
}m_v;

int  main ()
{

system ("clear");
m_v el[10];
pthread_t th[50];
							printf("\n\t\t\tMatrix Multiblication\n");
							printf("\n\t\t\tEntering First Matrix\n");
int i,j,k,m1,n1,m2,n2,y[10];

  		printf("\nNumbers of rows   =");
			scanf("%d",&m1);
 		 printf("\nNumbers of columns=");
	scanf("%d",&n1);

printf("\n\tEnter matrix elements\n A=\n");
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

printf("\n\tEnter matrix elements\n B= \n");
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
//operation of matrix multiplication    ///////////////////////////////////// //creating threads ///////////////////////////////////
printf("\n\t\t The Rusult\n");
clk_s=clock();
int t=0;
for (k=0;k<m1;k++)
{
	

el[k].kk=k;
el[k].nn_1=n1;
el[k].nn_2=n2;
int th_c=pthread_create(&th[k], NULL, clc,(void*)&el[k]);
if (th_c !=0){
	printf("Error in thread creation");
	exit(-1);
	}
 		
	t++;	
	
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

for (k=0;k<m1;k++)
{
	
	pthread_join(th[k],NULL);
	
}
clk_e=clock();

time=(clk_e-clk_s);///  CLOCKS_PER_SEC = 1000,000;

//printing results
for (j=0;j<m1;j++)
{
	putchar('\n');
	for (i=0;i<n2;i++)
	{
	printf("%d   ",r[j][i]);
	}
} 
putchar('\n');
printf("Number of threads = %d\n",t);   //k
printf("Execution time s =%ld Micro second\n",time);


}

void *clc (void* x)
{

int i,j;
int *p_k=(int*) x; //according to j
int *p_n1=p_k+1;   //according to k
int *p_n2=p_k+2;  //according to n1


	for (j=0;j<*p_n2;j++)
		{
	 		for (i=0;i<*p_n1;i++)
			{
	 		r[*p_k][j]+=a[*p_k][i]*b[i][j];
			}
        }
	putchar('\n');

	pthread_exit(NULL);
}




