#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

vector<long long int> denom(21);

void init_prog(void){
	for(long long int i=0;i<21;i++){
		denom[i] = (i+1)*(i+1)*(i+1);
	}
	return;
}

int main(){
	init_prog();
	long long int input;
	while(cin >> input){
		long long int nr_denom=0;
		for(int i=0;i<21;i++){
			if(denom[i]>input){
				break;
			}
			nr_denom++;
		}
		vector<long long int> DP(input+1,0);
		DP[0] = 1;
		for(long long int i=0;i<nr_denom;i++){
			for(long long int j=1;j<=input;j++){
				if(j-denom[i]>=0){
					DP[j]+=DP[j-denom[i]];
				}
			}
		}
		cout << DP[input] << endl;
	}
	return 0;
}