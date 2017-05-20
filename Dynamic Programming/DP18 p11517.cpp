#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

#define INT_MAXIMUM 10000000

using namespace std;

int main(){
    //freopen("output.txt","w",stdout);
	int T;
	cin >> T;
	while(T--){
		int to_pay;
		int nr_denom,max_denom = 0;
		cin >> to_pay >> nr_denom;
		vector<int> denom(nr_denom);
		for(int i=0;i<nr_denom;i++){
			cin >> denom[i];
			if(max_denom<denom[i]){
                max_denom = denom[i];
			}
		}
		//sort(denom.begin(),denom.end());
		int max_pay = (to_pay/max_denom +1)*max_denom;
		vector<int> DP(max_pay+1,INT_MAXIMUM);
		DP[0] = 0;
		for(int i=0;i<nr_denom;i++){
			for(int j=max_pay;j>=1;j--){
				if(j-denom[i]>=0){
                    if(DP[j-denom[i]]!=INT_MAXIMUM){
                        DP[j] = min(DP[j],1+DP[j-denom[i]]);
                    }
				}
			}
		}
		int paid_amount, paid_coins;
		for(int i=to_pay;i<=max_pay;i++){
			if(DP[i]!=INT_MAXIMUM){
				paid_amount = i;
				paid_coins = DP[i];
				break;
			}
		}
		cout << paid_amount << " " << paid_coins << endl;
	}
	return 0;
}
