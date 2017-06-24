#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

#define INT_MAXIMUM 10000000

using namespace std;

int step[3] = {-1,0,1};
int cost[3] = {60,30,20};

int main(){
	int T,N,n;
	cin >> T;
	while(T--){
		cin >> N;
		n = N/100;
		vector<vector<int> > input(10,vector<int>(n));
		for(int i=0;i<10;i++){
			for(int j=0;j<n;j++){
				cin >> input[i][j];
			}
		}
		vector<vector<int> > DP(10,vector<int>(n+1,INT_MAXIMUM));
		DP[9][0] = 0;
		for(int j=1; j<=n; j++){
			for(int i=9;i>=0;i--){
				for(int k=0;k<3;k++){
					if(i+step[k]>=0 && i+step[k]<10){
						DP[i][j] = min(DP[i][j],DP[i+step[k]][j-1]+cost[k]-input[i+step[k]][j-1]);
					}
				}
			}
		}
		cout << DP[9][n] << endl;
        cout << endl;
	}

	return 0;
}
