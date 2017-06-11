#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

int main(){
    //freopen("output.txt","w",stdout);
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
		vector<int> nr_dp(t+1,0);
		vector<vector<bool> > pickup(N, vector<bool>(t+1,false));
		DP[0] = 0;
		int ret = 0;
		int nr_items=0;
		int pickup_weight;
		for(int i=0;i<N;i++){
			for(int j=t;j>=0;j--){
				if(j-weight[i]>=0 && DP[j-weight[i]]!=-1){
					//DP[j] = max(DP[j],DP[j-weight[i]]+value[i]);
					if(DP[j] < DP[j-weight[i]]+value[i]){
						DP[j] = DP[j-weight[i]]+value[i];
						nr_dp[j] = nr_dp[j-weight[i]] + 1;
						pickup[i][j] = true;
					}
					if(ret < DP[j]){
						ret = DP[j];
						nr_items = nr_dp[j];
						pickup_weight = j;
					}
				}
			}
		}
		cout << ret << endl;
		cout << nr_items << endl;
		/*nr_items = 0;
		vector<bool> taken(N, false);
		for(int i=0;i<N;i++){
			if(pickup[i][pickup_weight]){
				taken[i] = true;
				nr_items++;
				pickup_weight = pickup_weight - weight[i];
			}
			
		}
		cout << nr_items << endl;
		for(int i=0;i<N;i++){
			if(taken[i]){
				cout << weight[i]/(3*d) << " " << value[i] << endl;
			}
		}*/
		int start = N-1;
		stack<int> pickup_stack;
		while(start>=0){
			if(pickup[start][pickup_weight]){
				//cout << weight[start]/(3*d) << " " << value[start] << endl;
				pickup_weight = pickup_weight - weight[start];
				pickup_stack.push(start);
				start--;
			}
			else{
				start--;
			}
		}
		while(!pickup_stack.empty()){
			cout << weight[pickup_stack.top()]/(3*d) << " " << value[pickup_stack.top()] << endl;
			pickup_stack.pop();
		}
		cout << endl;
	}
	return 0;
}
