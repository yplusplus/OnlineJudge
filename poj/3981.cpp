#include<iostream>
#include<string>
using namespace std;
int main()
{
	string str;
	int pos;
	while(getline(cin,str))
	{
		while( (pos=str.find("you")) != -1 )
			str.replace(pos,3,"we");
		cout<<str<<endl;
	}
	return 0;
}
