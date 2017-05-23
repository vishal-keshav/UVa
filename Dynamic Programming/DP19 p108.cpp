#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

#define INT_MAXIMUM 10000000

int main(){
	int N;
	cin >> N;
	vector<vector<int> > arr(N,vector<int>(N));
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			cin >> arr[i][j];
		}
	}

	vector<vector<int> > DP_sum(N+1,vector<int>(N+1));
	for(int i=0;i<=N;i++){
		DP_sum[0][i] = 0;
		DP_sum[i][0] = 0;
	}

	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			DP_sum[i+1][j+1] = DP_sum[i+1][j] + DP_sum[i][j+1] + arr[i][j] - DP_sum[i][j];
		}
	}
	int temp_sum,ret=-INT_MAXIMUM;
	//O(n^4) algo here
	for(int i=1;i<=N;i++){
		for(int j=1;j<=N;j++){
			for(int k=i;k<=N;k++){
				for(int l=j;l<=N;l++){
					temp_sum = DP_sum[k][l] - DP_sum[k][j-1] - DP_sum[i-1][l] + DP_sum[i-1][j-1];
					if(temp_sum>ret){
						ret = temp_sum;
					}
				}
			}
		}
	}
	cout << ret << endl;

	return 0;
}
