#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
	int t,d,N;
	while(cin >> t){
		cin >> d >> N;
		vector<int> weight(N);
		vector<int> value(N);
		for(int i=0;i<N;i++){
			cin >> weight[i] >> value[i];
			weight[i] = 3*d*weight[i];
		}
		vector<int> DP(t+1,-1);
		DP[0] = 0;
		int ret = 0;
		for(int i=0;i<N;i++){
			for(int j=t;j>=0;j--){
				if(j-weight[i]>=0 && DP[j-weight[i]]!=-1){
					DP[j] = max(DP[j],DP[j-weight[i]]+value[i]);
					if(ret < DP[j]){
						ret = DP[j];
					}
				}
			}
		}
		cout << ret << endl;
	}
	return 0;
}