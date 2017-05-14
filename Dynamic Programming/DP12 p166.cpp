#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

#define MAXIMUM_INT 10000000

int deno[6] = {1,2,4,10,20,40};

int main(){
	int nr_coin[6] = {0,0,0,0,0,0};
	double pay;
	int pay_int;
	int max_amount=0;
	//Initial input
	for(int i=0;i<6;i++){
		cin >> nr_coin[i];
		max_amount+=deno[i]*nr_coin[i];
	}
	while(max_amount){
		cin >> pay;
		pay_int = (int)(100*(pay+0.0005))/5;
		vector<int> value_exchange(max_amount+1,MAXIMUM_INT);
		value_exchange[0] = 0;
		//Set for each denomination as one
		/*for(int i=0;i<6;i++){
			value_exchange[deno[i]] = 1;
		}*/
		//Populate min coins required for each value
		for(int i=1;i<=max_amount;i++){
			for(int j=0;j<6;j++){
				if(i-deno[j]>=0){
					if(value_exchange[i-deno[j]]+1 < value_exchange[i]){
						value_exchange[i] = 1+ value_exchange[i-deno[j]];
					}
				}
			}
		}
		//Find the possibility of all exchanges, select with min coin exchange
		vector<int> payable(max_amount+1,MAXIMUM_INT);
		payable[0] = 0;
		for(int i=0;i<6;i++){
			for(int j=0;j<nr_coin[i];j++){
				for(int k=1;k<=max_amount;k++){
					if(k-deno[i]>=0 && payable[k-deno[i]]!=MAXIMUM_INT){
						if(payable[k]>1+payable[k-deno[i]]){
							payable[k] = 1+payable[k-deno[i]];
						}
					}
				}
			}
		}
		//Iterate to get the minimum exchange
		int res = MAXIMUM_INT;
		for(int i=1;i<=max_amount;i++){
			if(payable[i]==1){
				if(i-pay_int >=0){
					if(res>payable[i]+value_exchange[i-pay_int]){
						res = payable[i]+value_exchange[i-pay_int];
					}
				}
			}
		}
		cout << res << endl;
		max_amount = 0;
		for(int i=0;i<6;i++){
			cin >> nr_coin[i];
			max_amount+=deno[i]*nr_coin[i];
		}
	}
	return 0;
}