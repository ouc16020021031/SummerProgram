#include<iostream>
#include<map>
#define y 5.5554
using namespace std;

int main() {
	int a=10;
	while(a){
		if(a--<-1)break;
		cout<<a;
	}
	return 0;
}