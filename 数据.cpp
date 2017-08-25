#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;
int main() {
	int a, b, c, d, e;
	int n[5], m[5];
	for(int i = 0; i < 100; i++) {
		a = rand() % 10000 + 1;
		b = rand() % 20 + 1;
		c = rand() % 20 + 1;
		d = rand() % 10 + 1;
		e = rand() % 5000;
		for(int j = 0; j < 5; j++) {
			n[j] = rand() % 10000 + 1;
			m[j] = rand() % 10000 + 1;
		}
		printf("%d %d %d %d %d\n",a,b,c,d,e);
		for(int j = 0; j < 5; j++) {
			cout<<n[j]<<' ';
		}cout<<endl;
		for(int j = 0; j < 5; j++) {
			cout<<m[j]<<' ';
		}cout<<endl;
	}
	return 0;
}