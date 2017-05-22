#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
	int N;
	cin >> N;
	vector<vector<int> > array(N,vector<int>(N));
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			cin >> array[i][j];
		}
	}
	vector<vector<int> > DP_sum(N,vector<int>(N));
	DP_sum[0][0] = array[0][0];
	for(int i=1;i<N;i++){
		DP_sum[0][i] = DP_sum[0][i-1]+array[0][i];
		DP_sum[i][0] = DP_sum[i][0]+array[i][0];
	}
	for(int i=1;i<N;i++){
		for(int j=1;j<N;j++){
			DP_sum[i][j] = DP_sum[i-1][j] + DP[i][j-1] + array[i][j] - DP_sum[i-1][j-1];
		}
	}
	//O(n^4) algo here
	
	return 0;
}