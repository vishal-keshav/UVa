#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

//#define DEBUG

using namespace std;

int main(){
	int T,N;
	cin >> T;
	while(T--){
		cin >> N;
		vector<vector<int> > arr(N,vector<int>(N));
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				cin >> arr[i][j];
			}
		}
		//For horizontal mapping
		vector<vector<int> > arr_tourus(2*N,vector<int>(2*N));
		for(int i=0;i<2;i++){
			for(int j=0;j<2;j++){
				for(int k=0;k<N;k++){
					for(int l=0;l<N;l++){
						arr_tourus[k+i*N][l+j*N] = arr[k][l];
					}
				}
			}
		}
#ifdef DEBUG
		for(int i=0;i<2*N;i++){
			for(int j=0;j<2*N;j++){
				cout << arr_tourus[i][j] << " ";
			}
			cout << endl;
		}
#endif
		vector<vector<int> > DP_sum(2*N+1,vector<int>(2*N+1,0));

		for(int i=0;i<=2*N;i++){
			DP_sum[i][0] = 0;
			DP_sum[0][i] = 0;
		}

		for(int i=0;i<2*N;i++){
			for(int j=0;j<2*N;j++){
				DP_sum[i+1][j+1] = arr_tourus[i][j] + DP_sum[i][j+1] + DP_sum[i+1][j] - DP_sum[i][j];
			}
		}
		int temp,ret=-10000;
		for(int i=1;i<=N;i++){
			for(int j=1;j<=N;j++){
				for(int k=i;k<i+N;k++){
					for(int l=j;l<j+N;l++){
						temp = DP_sum[k][l] - DP_sum[k][j-1] - DP_sum[i-1][l] + DP_sum[i-1][j-1];
						if(temp > ret){
							ret = temp;
						}
					}
				}
			}
		}
		cout << ret << endl;
	}


	return 0;
}
