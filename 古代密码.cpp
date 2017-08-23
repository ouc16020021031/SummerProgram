#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

int main() {
	char sa[101], sb[101];
	int a[26] = {0}, b[26] = {0};
	bool flag = true;
	cin >> sa >> sb;
	for(int i = 0; i < strlen(sa); i++) {
		a[sa[i] - 'A']++;
		b[sb[i] - 'A']++;
	}
	sort(a, a + 26);
	sort(b, b + 26);
	for(int i = 0; i < 26; i++) {
		if(a[i] != b[i])flag = false;
	}
	if(flag)cout << "YES" << endl;
	else cout << "NO" << endl;
	return 0;
}