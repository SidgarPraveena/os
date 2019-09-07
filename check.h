#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<iostream>
#include <bits/stdc++.h>
#include<sys/wait.h>

int checkPipe(char * arr)
{
	int count=0;
	for(int i=0;i<strlen(arr);i++)
	{
		if(arr[i]=='|')
			count++;
	}
	return count;
}
int check(char *arr)
{
	//cout<<"Hello"<<arr;
	if(arr[0]=='c' && arr[1]=='d')
		return 3;
	for(int i=0;i<strlen(arr);i++)
	{
		if(arr[i]=='>')
		{
			if(arr[i+1]=='>')
			{
				return 2;
			}
			else 
			{
				return 1;
			}
		}
	}
	return 0;
}
