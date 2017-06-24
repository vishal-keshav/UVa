#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

#define INT_MINIMUM -10000000

using namespace std;

vector<int> arr;
vector<int> seq_sum;

vector<vector<int> > DP;
vector<vector<int> > DP_opponent;

int sum(int i, int j){
	return (seq_sum[j+1] - seq_sum[i]);
}

int max_score(int s_index, int e_index){
	if(s_index<=e_index && DP[s_index][e_index]!=-1){
		return DP[s_index][e_index];
	}
	if(s_index>e_index){
		return 0;
	}
	else if(s_index==e_index){
		DP[s_index][e_index] = arr[s_index];
		return arr[s_index];
	}
	else{
		int ret = INT_MINIMUM;
		//Left part
		for(int i=s_index;i<=e_index;i++){
			//ret = max(ret, sum(s_index,i)+sum(i+1,e_index)-max_score(i+1,e_index));
			if(ret<sum(s_index,i)+sum(i+1,e_index)-max_score(i+1,e_index)){
                ret = sum(s_index,i)+sum(i+1,e_index)-max_score(i+1,e_index);
                DP_opponent[s_index][e_index] = max_score(i+1,e_index);
			}
		}
		//Right part
		for(int i=e_index;i>=s_index;i--){
			//ret = max(ret, sum(i,e_index)+sum(s_index,i-1)-max_score(s_index,i-1));
			if(ret<sum(i,e_index)+sum(s_index,i-1)-max_score(s_index,i-1)){
                ret = sum(i,e_index)+sum(s_index,i-1)-max_score(s_index,i-1);
                DP_opponent[s_index][e_index] = max_score(s_index,i-1);
			}
		}
		DP[s_index][e_index] = ret;
		return ret;
	}
}

int main(){
	int N;
	cin >> N;
	while(N){

		arr.clear();
		arr.resize(N);
		seq_sum.clear();
		seq_sum.resize(N+1);
		seq_sum[0] = 0;

		for(int i=0;i<N;i++){
			cin >> arr[i];
			seq_sum[i+1] = seq_sum[i]+arr[i];
		}
		DP.clear();
		DP.resize(N, vector<int>(N,-1));
        DP_opponent.clear();
		DP_opponent.resize(N, vector<int>(N,-1));
		int temp = max_score(0,N-1);

		cout << (DP[0][N-1] - DP_opponent[0][N-1]) << endl;

		cin >> N;
	}

	return 0;
}
