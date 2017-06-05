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
		vector<int> item_used(t+1,-1);
		vector<int> parent(t+1,0);
		DP[0] = 0;
		int ret = 0;
		int nr_items=0;
		int last_item= -1;
		for(int i=0;i<N;i++){
			for(int j=t;j>=0;j--){
				if(j-weight[i]>=0 && DP[j-weight[i]]!=-1){
					//DP[j] = max(DP[j],DP[j-weight[i]]+value[i]);
					if(DP[j] < DP[j-weight[i]]+value[i]){
						DP[j] = DP[j-weight[i]]+value[i];
						nr_dp[j] = nr_dp[j-weight[i]] + 1;
						item_used[j] = i;
						parent[j] = j-weight[i];
					}
					if(ret < DP[j]){
						ret = DP[j];
						nr_items = nr_dp[j];
						last_item = j;
					}
				}
			}
		}
		cout << ret << endl;
		cout << nr_items << endl;
		stack<int> item_stack;
		while(item_used[last_item]!=-1){
            item_stack.push(item_used[last_item]);
            //cout << value[item_used[last_item]] << endl;
            last_item = parent[last_item];
		}
		while(!item_stack.empty()){
            cout << weight[item_stack.top()]/(3*d) << " " << value[item_stack.top()] << endl;
            item_stack.pop();
		}
	}
	return 0;
}
