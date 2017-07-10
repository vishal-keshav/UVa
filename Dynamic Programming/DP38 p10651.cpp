#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <string>
#include <math.h>

#define INT_MAXIMUM 1000000

using namespace std;

int T,min_pebble;
string input;
vector<int> DP;

int nr_bits(int num){
	int ret = 0;
	for(int i=0;i<12;i++){
		if(num & (1<<i)){
			ret++;
		}
	}
	return ret;
}

void move(int state){
	if(DP[state]==0){
		//Update min_pebble and DP
		DP[state] = 1;
		min_pebble = min(min_pebble,nr_bits(state));
		//Try possible moves
		for(int i=1;i<11;i++){
			if(state & (1<<i)){
				//Try left to right
				if((state & (1<<(i-1))) && (~state & (1<<(i+1)))){
					move(((state & ~(1<<i)) & ~(1<<(i-1))) | (1<<(i+1)));
				}
				//Try right to left
				if((state & (1<<(i+1))) && (~state & (1<<(i-1)))){
					move(((state & ~(1<<i)) & ~(1<<(i+1))) | (1<<(i-1)));
				}
			}
		}
	}
	return;
}

int main(){
	cin >> T;
	while(T--){
		cin >> input;
		int state = 0;
		for(int i=0;i<12;i++){
			if(input[i]=='o'){
				state = state | (1<<i);
			}
		}
		//cout << state << endl;
		min_pebble = INT_MAXIMUM;
		DP.clear();
		DP.resize(pow(2,12),0);
		//DP[state] = 1;
		move(state);
		cout << min_pebble << endl;
	}

	return 0;
}
