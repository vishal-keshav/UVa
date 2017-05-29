#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

int main(){
    //freopen("output.txt","w",stdout);
	int n,m;
	cin >> n;
	while(n--){
		cin >> m;
		vector<int> value(m);
		int sum=0,W=0;
		for(int i=0;i<m;i++){
			cin >> value[i];
			sum+=value[i];
		}
		W=sum/2;
		vector<vector<int> > DP(m+1,vector<int>(W+1,0));
		for(int i=1;i<=m;i++){
			for(int j=0;j<=W;j++){
				if(j+value[i-1]<=W){
					DP[i][j+value[i-1]] = max(DP[i][j+value[i-1]],DP[i-1][j]+value[i-1]);
				}
				DP[i][j] = max(DP[i][j],DP[i-1][j]);
			}
		}
		int ret=0;
		for(int i=0;i<=W;i++){
			if(DP[m][i]!=0){
                ret = i;
			}
		}
		cout << (sum - 2*ret) << endl;
	}

	return 0;
}
