#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

#define INT_MAXIMUM 10000000

using namespace std;

int main(){
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

		vector<int> DP(W+1,-1);
		DP[0] = 0;
		int ret = 0;
		for(int i=0;i<m;i++){
			for(int j=W;j>=0;j--){
				if(j-value[i]>=0){
					DP[j] = max(DP[j],DP[j-value[i]]+value[i]);
					if(DP[j] > ret){
						ret = DP[j];
					}
				}
			}
		}
		cout << (sum - 2*ret) << endl;
	}

	return 0;
}
