#include<iostream>
#include<vector>
#define y 5.5554
using namespace std;

int main() {
	int b=1;
	vector<int> a;
	for(int i=0;i<5;i++)
	a.push_back(i*3);
	if((b-=2)>5)cout<<*(a.begin()+3);
	return 0;
}