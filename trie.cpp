#include<iostream>
#include<unordered_map>
#include<vector>
#include <bits/stdc++.h>
#include<curses.h>
using namespace std;
vector<char> store;
struct Trie
{
	bool isEndOfWord;
	unordered_map<char, Trie *>map;
};


Trie* getNewTrieNode() 
{ 
    Trie* node = new Trie; 
    node->isEndOfWord = false; 
    return node; 
} 
void insert(Trie**  root, const string& str) 
{ 
    if (*root == nullptr) 
        *root = getNewTrieNode(); 
  
    Trie* temp = *root; 
    for (int i = 0; i < str.length(); i++) { 
        char x = str[i]; 
        if (temp->map.find(x) == temp->map.end()) 
            temp->map[x] = getNewTrieNode(); 
  
        temp = temp->map[x]; 
    } 
  
    temp->isEndOfWord = true; 
} 


void display(vector<char> store,char arr[5])
{
	cout<<arr;
	for(auto i=store.begin(); i!=store.end();i++)
	{
		cout<<*i;
	}
	cout<<endl;
}

void traverse(Trie** root,char arr[5])
{
	Trie * temp,*temp1;
	temp=(*root);
	
	
	if(temp == nullptr)
	{
		return;
	}
	else
	{
		if((temp->map.size())!=0)
		{
			for (auto it = temp->map.cbegin(); it != temp->map.cend(); ++it) 
			{
				char z=(*it).first;
				store.push_back(z);
				temp1=temp->map[z];
				if(temp1->isEndOfWord == true)
				{
					//cout<<endl;
					//cout<<"z value "<<z<<endl;
					display(store,arr);
				}
				traverse(&(temp->map[z]),arr);
				store.pop_back();
			}
		}
	}
}

struct Trie * search(char *arr,Trie *root)
{
	Trie * temp=root;
	for(int i=0;i<strlen(arr);i++)
	{
		if(temp->map.find(arr[i])==temp->map.end())
		{
			return nullptr;
		}
		else
		{
			temp=temp->map[arr[i]];
		}
	}
	if(temp->isEndOfWord==true)
	{
		cout<<arr<<endl;
	}
	return temp;
}
int main()
{
	char ch='a';
	char arr[10]="abc";
	Trie* root = nullptr,*pt=nullptr;
	insert(&root, "abc"); 
    	insert(&root, "abcd"); 
	insert(&root, "abgl"); 
	insert(&root, "cdf"); 
    	insert(&root,"lmn");
    	insert(&root, "abcde"); 
    	
    	pt=search(arr,root);
    	
    	traverse(&pt,arr);
    	
    	
}
