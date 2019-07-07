#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
int a[30], *a1[30], *a2[30], a3[30], *b[30], *c[30], i, j, k, n, t;
void *sortthread1(void *p);
void *sortthread2(void *p);
void *mergethread(void *p);
int main(int argc,char *argv[])
{
	pthread_t tid1,tid2,tid3;
	printf("Enter the no. of integers: ");
	scanf("%d",&n);
	printf("Enter the list of integers: ");
	for(i=0;i<n;i++)
	scanf("%d",&a[i]);
	int *p=a;
	pthread_create(&tid1, NULL, sortthread1, (void *)p);
	pthread_create(&tid2, NULL, sortthread2, (void *)p);
	pthread_create(&tid3, NULL, mergethread, (void *)p);
	printf("\nsorting thread 1 & 2 processed");
	pthread_join(mergethread, NULL);
	printf("\nSorted Sub List1: ");
	for(i=0;i<n/2;i++)
	printf("%d ",b[i]);
	printf("\nSorted Sub List2: ");
	for(i=0;i<(n-n/2);i++)
	printf("%d ",c[i]);
	printf("\nMerged Sorted List: ");
	for(i=0;i<n;i++)
	printf("%d ",a3[i]);
	printf("\nmerge thread processed");
	return 0;
}
void *sortthread1(void *p)
{
	int *a1=(int *)p;
	for(i=0;i<n/2;i++)
	b[i]=a1[i];
	for(i=0;i<n/2;i++)
	{
		for(j=0;j<(n/2-i-1);j++)
		if(b[j]>b[j+1])
		{
			t=b[j];
			b[j]=b[j+1];
			b[j+1]=t;
		}
	}
	pthread_exit(0);
}
void *sortthread2(void *p)
{
	int *a2=(int *)p;
	for(i=0;i<(n-n/2);i++)
	c[i]=a2[i+n/2];
	for(i=0;i<(n-n/2);i++)
	{
		for(j=0;j<(n-n/2-i-1);j++)
		if(c[j]>c[j+1])
		{
			t=c[j];
			c[j]=c[j+1];
			c[j+1]=t;
		}
	}
	pthread_exit(0);
}
void *mergethread(void *p)
{
	i=0;
	j=0;
	k=0;
	while(i<n/2 && j<(n-n/2))
	{
		if(b[i]<=c[j])
		{
			a3[k]=b[i];
			i++;
		}
		else
		{
			a3[k]=c[j];
			j++;
		}
		k++;
	}
	while(i<n/2)
	{
		a3[k]=b[i];
		i++;
		k++;
	}
	while(j<(n-n/2))
	{
		a3[k]=c[j];
		j++;
		k++;
	}
	pthread_exit(0);
}
/*
Enter the no. of integers: 10
Enter the list of integers: 58 1 42 31 4 2 97 35 64 5

sorting thread 1 & 2 processed
Sorted Sub List1: 1 4 31 42 58
Sorted Sub List2: 2 5 35 64 97
Merged Sorted List: 1 2 4 5 31 35 42 58 64 97
merge thread processed
*/
