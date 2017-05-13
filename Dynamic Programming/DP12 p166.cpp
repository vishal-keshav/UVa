#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

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
		
		
	}
	return 0;
}