#include<iostream>
#include<map>
using namespace std;

int Sum(int M, int N) {  //递归
//前面的数一定不比后面的数大
	if (M < 0) return 0;
	else if (M == 0 || N == 1) return 1;
	else return Sum(M, N - 1) + Sum(M - N, N);
//(M, N-1):第一个plate为0，把M分配到N-1
//(M-N, N):每个plate初始为1，把M-N分配到N
}

int main() {
	int M, N;
	int t;
	cin >> t;
	while(t--) {
		cin >> M >> N;
		cout << Sum(M, N)<<endl;
	}
	return 0;
}