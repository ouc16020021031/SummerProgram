#include<iostream>
#include<map>
using namespace std;

int Sum(int M, int N) {  //�ݹ�
//ǰ�����һ�����Ⱥ��������
	if (M < 0) return 0;
	else if (M == 0 || N == 1) return 1;
	else return Sum(M, N - 1) + Sum(M - N, N);
//(M, N-1):��һ��plateΪ0����M���䵽N-1
//(M-N, N):ÿ��plate��ʼΪ1����M-N���䵽N
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