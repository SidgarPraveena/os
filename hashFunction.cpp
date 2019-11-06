#include<iostream>
#include <bits/stdc++.h>
using namespace std;


unsigned int cal_hash(string str)
{
    unsigned int ha = 5381;

    for(char c:str)
        ha = ((ha << 5) + ha) + c; /* hash * 33 + c */

    return ha;
}
int main()
{
	string arr;
	cout<<"Enter string: ";
	cin>>arr;
	cout<<cal_hash(arr)<<endl;
	
	int a=10;
	float b=3.5;
	stringstream ss;
	ss<<a;
	string str = ss.str();
	
	cout<<str<<endl;
	
	stringstream ss1;
	ss1<<b;
	string str1 = ss1.str();
	cout<<str1<<endl;
	return 0;
}
