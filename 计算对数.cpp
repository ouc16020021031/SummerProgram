#include<iostream>
#include<cmath>
using namespace std;

int main() {
	double a,b;
	int x=0;
	cin>>a>>b;
	while(!(pow(a,x)<=b&&b<pow(a,x+1))){
		x++;
	}cout<<x;
	return 0;
}