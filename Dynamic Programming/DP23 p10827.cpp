#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

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
		vector<vector<int> > horiz(N,vector<int>(2*N));
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				horiz[i][j] = arr[i][j];
				horiz[i][j+N] = arr[i][j];
			}
		}
		vector<vector<int> > DP_sum_horiz(N+1,vector<int>(2*N+1,0));
		for(int i=0;i<=N;i++){
			DP_sum_horiz[i][0] = 0;
		}
		for(int i=0;i<=2*N;i++){
			DP_sum_horiz[0][i] = 0;
		}
		for(int i=0;i<N;i++){
			for(int j=0;j<2*N;j++){
				DP_sum_horiz[i+1][j+1] = horiz[i][j] + DP_sum_horiz[i][j+1] + DP_sum_horiz[i+1][j] - DP_sum_horiz[i][j];
			}
		}
		int temp,ret=-10000;
		for(int i=1;i<=N;i++){
			for(int j=1;j<=N;j++){
				for(int k=i;k<=N;k++){
					for(int l=j;l<j+N;l++){
						temp = DP_sum_horiz[k][l] - DP_sum_horiz[k][j-1] - DP_sum_horiz[i-1][l] + DP_sum_horiz[i-1][j-1];
						if(temp > ret){
							ret = temp;
						}
					}
				}
			}
		}
		//For vertical mapping
		vector<vector<int> > vert(2*N,vector<int>(N));
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				vert[i][j] = arr[i][j];
				vert[i+N][j] = arr[i][j];
			}
		}
		vector<vector<int> > DP_sum_vert(2*N+1,vector<int>(N+1,0));
		for(int i=0;i<=N;i++){
			DP_sum_vert[0][i] = 0;
		}
		for(int i=0;i<=2*N;i++){
			DP_sum_vert[i][0] = 0;
		}
		for(int i=0;i<2*N;i++){
			for(int j=0;j<N;j++){
				DP_sum_vert[i+1][j+1] = vert[i][j] + DP_sum_vert[i][j+1] + DP_sum_vert[i+1][j] - DP_sum_vert[i][j];
			}
		}
		for(int i=1;i<=N;i++){
			for(int j=1;j<=N;j++){
				for(int k=i;k<i+N;k++){
					for(int l=j;l<=N;l++){
						temp = DP_sum_vert[k][l] - DP_sum_vert[k][j-1] - DP_sum_vert[i-1][l] + DP_sum_vert[i-1][j-1];
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
