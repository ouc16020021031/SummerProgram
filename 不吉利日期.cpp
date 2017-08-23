#include<iostream>
#include<map>
using namespace std;
int main() {
	int day[12]={31,28,31,30,31,30,31,31,30,31,30,31};
	int weekday;
	int month=0;
	int week=7;
	int total;
	cin>>weekday;
	while(month++<12){
		total=0;
		for(int i=0;i<month-1;i++){
			total+=day[i];
		}total+=13;
		if((total-1+weekday)%7==5)cout<<month<<endl;
	}
	return 0;
}