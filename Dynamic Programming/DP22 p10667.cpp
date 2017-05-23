#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

int main(){
	int T,N,B,x0,y0,x1,y1;
	cin >> T;
	while(T--){
		cin >> N >> B;
		vector<vector<int> > arr(N,vector<int>(N,1));
		for(int i=0;i<B;i++){
			cin >> x0 >> y0 >> x1 >> y1;
			for(int i=x0-1;i<x1;i++){
				for(int j=y0-1;j<y1;j++){
					arr[i][j] = 0;
				}
			}
		}
		vector<vector<int> > DP_sum(N+1,vector<int>(N+1));
		for(int i=0;i<=N;i++){
			DP_sum[i][0] = 0;
			DP_sum[0][i] = 0;
		}
		//Fill DP_sum
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				DP_sum[i+1][j+1] = arr[i][j] + DP_sum[i][j+1] + DP_sum[i+1][j] - DP_sum[i][j];
			}
		}
		int temp,ret=0;
		for(int i=1;i<=N;i++){
			for(int j=1;j<=N;j++){
				for(int k=i;k<=N;k++){
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
	}
	
	
	return 0;
}