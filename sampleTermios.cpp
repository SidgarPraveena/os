#include<stdio.h>
#include<termios.h>
#include<sys/types.h>
#include<unistd.h>
#include<iostream>
#include<unordered_map>
#include<vector>
#include <bits/stdc++.h>
#include<sys/wait.h>
#include <fcntl.h>
#include <dirent.h>
#include "trie.h"
#include"check.h"
using namespace std;


int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( 0, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON );
    tcsetattr( 0, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( 0, TCSANOW, &oldattr );
    return ch;
}	
void parse(char *arr, char ** argv)
{
	int i=0;
	char * tok;
	char *array[500];
	tok=strtok(arr," ");
	while(tok!=NULL)
	{
		array[i++]=strdup(tok);
		tok=strtok(NULL," ");
	}
	for(int j=0;j<i;j++)
	{
		argv[j]=array[j];
		argv[i]=NULL;
	}
}

void sinRed(char * arr, char ** argv)
{
	int i=0;
	char * tok;
	char *array[500];
	tok=strtok(arr,">");
	while(tok!=NULL)
	{
		array[i++]=strdup(tok);
		tok=strtok(NULL,">");
	}
	for(int j=0;j<i;j++)
	{
		argv[j]=array[j];
		argv[i]=NULL;
	}
}
void dobRed(char * arr,char ** argv)
{
	int i=0;
	char * tok;
	char *array[500];
	tok=strtok(arr,">>");
	while(tok!=NULL)
	{
		array[i++]=strdup(tok);
		tok=strtok(NULL,">>");
	}
	for(int j=0;j<i;j++)
	{
		argv[j]=array[j];
		argv[i]=NULL;
	}
}
void pipTok(char * arr, char **argv)
{
	int i=0;
	char * tok;
	char *array[500];
	tok=strtok(arr,"|");
	while(tok!=NULL)
	{
		array[i++]=strdup(tok);
		tok=strtok(NULL,"|");
	}
	for(int j=0;j<i;j++)
	{
		argv[j]=array[j];
		argv[i]=NULL;
	}
}

void trim(char arr[500])
{
	int k,temp=0;
	
	for(int i=0;i<strlen(arr);i++)
	{
		if(arr[i]==' ' && arr[i+1]!='\0')
		{
			k=i+1;
			temp=1;
		}
	}
	if(temp==1)
	{
		int j=0;
		for(k;k<strlen(arr);k++)
		{
			arr[j]=arr[k];
			j++;
		}
		arr[j]='\0';
	}
}
int main()
{

	int c,res,res1;
	char temp;
	char arr[500],b[500];
	char *argv[500],*argv1[500],*argv2[500],*argv3[500],*argv4[500],*argv5[500],*argv6[500];
	pid_t pid;
	Trie* root = nullptr,*pt=nullptr;
	
	while(1)
	{
		int i=0;
		while(1)
		{
			c=getch();
			//cout<<c;
			if(c==9)
				break;
			else if(c==10)
				break;
			else if(c==127)
			{
				//cout<<"arr "<<arr<<endl;
				cout<<"\b";
				cout<<" ";
				cout<<"\b";
				cout<<"\b";
				cout<<" ";
				cout<<"\b";
				cout<<"\b";
				cout<<" ";
				cout<<"\b";
				i=i-1;
				arr[i]='\0';
				
			}
			else if(c=='A')
			{
				//cout<<"up arrow";
				cout<<"\b";
				cout<<" ";
				cout<<"\b";
				cout<<"\b";
				cout<<" ";
				cout<<"\b";
				cout<<"\b";
				cout<<" ";
				cout<<"\b";
				cout<<"\b";
				cout<<" ";
				cout<<"\b";
			}
			else
			{
				temp=(char)c;
				arr[i]=temp;
				i++;
			}
		}
		arr[i]='\0';
		cout<<"arr "<<arr<<endl;
		
		if(c==9)
		{
			root=nullptr;
			init(&root);
			
			char buff[FILENAME_MAX],*temp1;
  			getcwd(buff,FILENAME_MAX);
  			int len = strlen(buff);
			if(buff[len] != '/' && (opendir(buff) != NULL))
				strcat(buff, "/");
  			//cout<<buff<<endl;
  			
  			struct dirent *ptr;
    			DIR *main;
    			main = opendir(buff);
    			if(main)
    			{
    				while (ptr = readdir(main))
    				{
    					insert(&root,ptr->d_name);
    				}
    			}
  			trim(arr);
			pt=search(arr,root);
			cout<<endl;
    			traverse(&pt,arr);
		}
		else if(c==10)
		{
			res=checkPipe(arr);
			if(res==0)
			{
				res1=check(arr);
				if(res1==1)
				{
					sinRed(arr,argv2);
					parse(argv2[0],argv3);
					int fp;
					
					
					if(fork()==0)
					{
						
						fp=open(argv2[1],O_RDONLY | O_WRONLY | O_TRUNC );
						dup2(fp,1);
						int pos=execvp(argv3[0],argv3); //1
						close(fp);
						if(pos==-1)
							cout<<argv2[0]<<endl;  
						
						exit(0);
					}
					else
					{
						wait(NULL);
					}
				}
				else if(res1==2)
				{
					dobRed(arr,argv);
					parse(argv[0],argv1);
					int fp;
					
					if(fork()==0)
					{
						
						fp=open(argv[1],O_WRONLY | O_APPEND );
						if(fp==-1)
						{
							cout<<"Enter correct file name";
						}
						else
						{
							dup2(fp,1);
							int pos=execvp(argv1[0],argv1);  //2
							close(fp);
							if(pos==-1)
								cout<<argv[0]<<endl;
						}
						
						
						exit(0);
					}
					else
					{
						wait(NULL);
					}
				}
				else if(res1==3)
				{
					trim(arr);
					chdir(arr);
					//cout<<arr;
				}
				else
				{
					strcpy(b,arr);
					//cout<<b<<endl;
					parse(b, argv);
					if(fork()==0)
					{
						if((execvp(argv[0],argv))==-1)  //3
						{
							cout<<"Enter correct command";
						}
						
						exit(0);
					}
					else
					{
						wait(NULL);
					}
				}
			}
			else
			{
				
				/*pipTok(arr,argv4);
				int pipFd[2];
				pipe(pipFd);
				
				if(fork()==0)
				{
					
					close(pipFd[0]);
					dup2(pipFd[1],STDOUT_FILENO);
					close(pipFd[1]);
					parse(argv4[0],argv5);
					//cout<<argv4[0]<<" "<<argv4[1];
					execvp(argv5[0],argv5);  //4
					//exit(0);
				}
				else
				{
					
					//cout<<"parent";
					if(fork()==0)
					{
						close(pipFd[1]);
						dup2(pipFd[0],STDIN_FILENO);
						close(pipFd[0]);
						//cout<<argv4[1];
						parse(argv4[1],argv6);
						execvp(argv6[0],argv6);  //4
						//exit(0);
					}
					else
					{
						wait(NULL);
						wait(NULL);
					}
					
				}*/
				
			}
			
		}
		
	}
	
	return 0;
}
