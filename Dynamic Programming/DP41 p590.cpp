#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

#define INT_MAXIMUM 1000000

using namespace std;

int n,k,nr_case;
vector<vector<vector<int> > > cost(10,vector<vector<int> >(10,vector<int>(1001,0)));
vector<vector<int> > DP;

int main(){
    nr_case = 1;
	cin >> n >> k;
	while(n+k>0){
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				if(i!=j){
					cin >> cost[i][j][0];
					for(int k=1;k<=cost[i][j][0];k++){
						cin >> cost[i][j][k];
					}
				}
			}
		}
		DP.clear();
		DP.resize(n,vector<int>(k+1,INT_MAXIMUM));
		DP[0][0] = 0;
		for(int i=1;i<=k;i++){
			for(int j=0;j<n;j++){
				//Check if j on previous day has been reached
				if(DP[j][i-1]!=INT_MAXIMUM){
					for(int k=0;k<n;k++){
						if(j!=k && cost[j][k][(i-1)%cost[j][k][0] + 1]!=0){
							DP[k][i] = min(DP[k][i],cost[j][k][1%cost[j][k][0] + 1]+ DP[j][i-1]);
						}
					}
				}
			}
		}
		cout << "Scenario #" << nr_case << endl;
		if(DP[n-1][k]!=INT_MAXIMUM){
			cout << "The best flight costs " << DP[n-1][k] << "." <<endl;
		}
		else{
			cout << "No flight possible." << endl;
		}
		cin >> n >> k;
		nr_case++;
		if(n+k){
			cout << endl;
		}
	}

	return 0;
}
