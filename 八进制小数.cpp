#include<iostream>
#include<cstring>
#include <iomanip>
using namespace std;

int main() {
	int i=1;
	double num=0;
	double index=1;
	char eight[16]={0};
	cin>>eight;
	while(++i<strlen(eight)){
		index*=0.125;
		num+=index*(eight[i]-'0');
	}cout<<eight<<" [8] = "<<setprecision(50)<<num<<" [10]"<<endl;
	return 0;
}