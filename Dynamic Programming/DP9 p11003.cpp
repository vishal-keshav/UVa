#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

#define INT_MAXIMUM 100000000

int main(){
	int N;
	cin >> N;
	while(N){
		vector<int> weight(N);
		vector<int> load(N);
		for(int i=0;i<N;i++){
			cin >> weight[i] >> load[i];
		}
		vector<vector<int> > DP(N+1,vector<int>(N+1,INT_MAXIMUM));
		//Fill the initial arrays
		for(int i=0;i<=N;i++){
			DP[0][i] = INT_MAXIMUM;
			DP[i][0] = 0;
		}
		//Fill the DP, retaining max_len
		int max_len = 1;
		for(int i=1,index=N-1;i<=N,index>=0;i++,index--){
            //cout << "Processing for " << weight[index] << endl;
			for(int j=1;j<=N;j++){
				for(int k=i-1;k>=0;k--){
					if(weight[index]+DP[k][j-1]<DP[i][j]){
						if(DP[k][j-1]<=load[index]){
							DP[i][j] = weight[index]+DP[k][j-1];
							if(max_len<j){
								max_len = j;
							}
						}
					}
				}
			}
		}

		/*for(int i=0;i<=N;i++){
			for(int j=0;j<=N;j++){
				cout << DP[i][j] << "  ";
			}
			cout << endl;
		}*/
		cout << max_len << endl;

		cin >> N;
	}

	return 0;
}
