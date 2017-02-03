#include <iostream>
#include <stdio.h>
using namespace std;
 
int main(){
	int T,n,m,x,y;
	cin >> T;
	while(T--){
		cin >> n >> m;
		n=n-2;
		m = m-2;
		if(n%3==0){
			x = n/3;
		}
		else{
			x = n/3 + 1;
		}
		if(m%3==0){
			y = m/3;
		}
		else{
			y = m/3 + 1;
		}
		cout << x*y << endl;
	}
	return 0;
}