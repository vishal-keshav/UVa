#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

int main(){
	int M,N;
	cin >> M >> N;
	while(M+N){
		vector<vector<int> > arr(M,vector<int>(N));
		for(int i=0;i<M;i++){
			for(int j=0;j<N;j++){
				cin >> arr[i][j];
				arr[i][j] = 1-arr[i][j];
			}
		}
		vector<vector<int> > DP_sum(M+1,vector<int>(N+1));
		for(int i=0;i<=M;i++){
			DP_sum[i][0] = 0;
		}
		for(int i=0;i<=N;i++){
			DP_sum[0][i] = 0;
		}
		//Fill DP_sum
		for(int i=0;i<M;i++){
			for(int j=0;j<N;j++){
				DP_sum[i+1][j+1] = arr[i][j] + DP_sum[i][j+1] + DP_sum[i+1][j] - DP_sum[i][j];
			}
		}
		int temp,ret=0;
		for(int i=1;i<=M;i++){
			for(int j=1;j<=N;j++){
				for(int k=i;k<=M;k++){
					for(int l=j;l<=N;l++){
						temp = DP_sum[k][l] - DP_sum[k][j-1] - DP_sum[i-1][l] + DP_sum[i-1][j-1];
						if(temp == (k-i+1)*(l-j+1) && temp>ret){
							ret = temp;
						}
					}
				}
			}
		}
		cout << ret << endl;

		cin >> M >> N;
	}
	return 0;
}
