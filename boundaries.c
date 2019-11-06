#include<stdio.h>
#include<math.h>
int main()
{
	int n;
	scanf("%d",&n);
	int arr[n],level[n],res[n];
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&arr[i]);
		res[i]=-1;
		level[i]=-1;
	}
	int temp=0;
	level[1]=1;
	for(int i=1;i<=n/2;i++)
	{
		if(2*i <= n)
		{
			level[2*i]=level[i]+1;
		}
		if(2*i+1 <= n)
		{
			level[2*i+1]=level[i]+1;
		}
	}
	int i=1,j,l=0,min,max;
	while(i<n)
	{
		min=-1;
		max=-1;
		for(j=i;j<i+pow(2,l);j++)
		{
			if(j<=n && arr[j] != -1)
			{
				if(min == -1)
				{
					min=j;
				}
				else
				{
					max=j;
				}
				if(2*j <= n && arr[2*j] == -1 && 2*j+1 <= n && arr[2*j+1] == -1 )
				{
					res[j]=1;
				}
			}
		}
		i=j;
		l++;
		res[min]=1;
		res[max]=1;
	}
	for (int i = 1; i <= n ; ++i)
	{
		if(res[i]!=-1)
		{
			printf("%d ",arr[i]);
		}
	}
}