#include<iostream>
#include<cstring>

using namespace std;

int main() {
	int i = -1;
	int number = 0;
	char num[1000];
	cin >> num;
	while(++i < strlen(num)) {
		number += num[i] - '0';
	}
	while(number / 10 != 0) {
		int index = 10000;
		int temp = 0;
		while(index != 1) {
			temp += number / index;
			number %= index;
			index /= 10;
		}
		number += temp;
	}
	cout << number << endl;
	return 0;
}