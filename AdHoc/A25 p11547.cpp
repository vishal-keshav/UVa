#include <iostream>
using namespace std;
long long int absolute(long long int n){
	if(n<0)
		return (-1*n);
	else
		return n;}
int main(){
	long long int T,N;
	cin >> T;
	while(T--){
		cin >> N;
		cout << absolute(((N*63*5 + 36962)%100)/10) << endl;}
	return 0;}