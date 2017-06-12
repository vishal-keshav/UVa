#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

#define INT_MAXIMUM 10000000

int main(){
    //freopen("output.txt","w",stdout);
	int N,M;
	while(cin >> N >> M){
		vector<vector<int> > input(N,vector<int>(M));
		vector<vector<int> > DP(N,vector<int>(M,INT_MAXIMUM));
		vector<vector<int> > path(N,vector<int>(M,-1));
		for(int i=0;i<N;i++){
			for(int j=0;j<M;j++){
				cin >> input[i][j];
			}
		}
		//Initialize DP
		for(int i=0;i<N;i++){
			DP[i][M-1] = input[i][M-1];
		}
		//Start filling DP bottom up manner
		for(int i=M-2;i>=0;i--){
			for(int j=0;j<N;j++){
				if(j==0){
					if(DP[j][i]>=DP[N-1][i+1]+input[j][i]){
						DP[j][i] = DP[N-1][i+1]+input[j][i];
						path[j][i] = N-1;
					}
					if(N>1 && DP[j][i]>=DP[j+1][i+1]+input[j][i]){
						DP[j][i] = DP[j+1][i+1]+input[j][i];
						path[j][i] = j+1;
					}
					if(DP[j][i]>=DP[j][i+1]+input[j][i]){
						DP[j][i] = DP[j][i+1]+input[j][i];
						path[j][i] = j;
					}
				}
				else if(j==N-1){
					if(DP[j][i]>=DP[j][i+1]+input[j][i]){
						DP[j][i] = DP[j][i+1]+input[j][i];
						path[j][i] = j;
					}
					if(N>1 && DP[j][i]>=DP[j-1][i+1]+input[j][i]){
						DP[j][i] = DP[j-1][i+1]+input[j][i];
						path[j][i] = j-1;
					}
					if(DP[j][i]>=DP[0][i+1]+input[j][i]){
						DP[j][i] = DP[0][i+1]+input[j][i];
						path[j][i] = 0;
					}
				}
				else{
					if(N>1 && DP[j][i]>=DP[j+1][i+1]+input[j][i]){
						DP[j][i] = DP[j+1][i+1]+input[j][i];
						path[j][i] = j+1;
					}
					if(N>1 && DP[j][i]>=DP[j][i+1]+input[j][i]){
						DP[j][i] = DP[j][i+1]+input[j][i];
						path[j][i] = j;
					}
					if(DP[j][i]>=DP[j-1][i+1]+input[j][i]){
						DP[j][i] = DP[j-1][i+1]+input[j][i];
						path[j][i] = j-1;
					}
				}
			}
		}
		//Finding minimal path
		int min_path = INT_MAXIMUM, start_point;
		for(int i=0;i<N;i++){
			if(min_path>DP[i][0]){
				min_path = DP[i][0];
				start_point = i;
			}
		}
		for(int i=0;i<M-1;i++){
            cout << start_point + 1 << " ";
            start_point = path[start_point][i];
		}
		//start_point = path[start_point][M-1];
		cout << start_point + 1 << endl;
		cout << min_path << endl;
	}
	return 0;
}
