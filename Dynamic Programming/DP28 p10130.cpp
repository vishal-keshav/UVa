#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
	int T,N;
	cin >> T;
	while(T--){
		cin >> N;
		vector<int> value(N);
		vector<int> weight(N);
		for(int i=0;i<N;i++){
			cin >> value[i] >> weight[i];
		}
		int nr_member, max_cap=0;
		int max_value = 0;
		cin >> nr_member;
		vector<int> cap(nr_member);
		for(int i=0;i<nr_member;i++){
			cin >> cap[i];
			if(max_cap < cap[i]){
				max_cap = cap[i];
			}
		}
		vector<int> DP(max_cap+1,-1);
		/*DP[w] = v => maximum value that a person with weight constraint w can carry is v*/
		DP[0] = 0;
		for(int i=0; i<N; i++){
			for(int j=max_cap;j>=0;j--){
				if(j-weight[i] >=0 && DP[j-weight[i]]!=-1){
					DP[j] = max(DP[j],DP[j-weight[i]]+value[i]);
				}
			}
		}
		for(int i=1;i<=max_cap;i++){
			DP[i] = max(DP[i],DP[i-1]);
		}
		for(int i=0;i<nr_member;i++){
			max_value+=DP[cap[i]];
		}
		cout << max_value << endl;
	}

	return 0;
}
