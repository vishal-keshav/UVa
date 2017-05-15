#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <math.h>

#define INT_MAXIMUM 10000000

using namespace std;

long long int modulo_int(long long int a, long long int b){
	long long int ret = (a*a + b*b);
	//ret = (long long int)sqrt((double)ret+0.05);
	return ret;
}

int main(){
	long long int T,m,S;
	cin >> T;
	while(T--){
		cin >> m >> S;
		vector<long long int> conv(m);
		vector<long long int> info(m);
		for(long long int i=0;i<m;i++){
			cin >> conv[i] >> info[i];
		}

		S=S*S;

		vector<long long int> DP_coin(S+1,INT_MAXIMUM);
		vector<long long int> conv_DP(S+1,INT_MAXIMUM);
		vector<long long int> info_DP(S+1,INT_MAXIMUM);

		DP_coin[0] = 0;
		conv_DP[0] = 0;
		info_DP[0] = 0;
		for(long long int i=0;i<m;i++){
			for(long long int j=0;j<=S;j++){
				if(DP_coin[j]!=INT_MAXIMUM){
					long long int next_sum = modulo_int(conv_DP[j]+conv[i], info_DP[j]+info[i]);
					/*if(next_sum==-1){
                        break;
					}*/
					if(next_sum<=S){
						if(DP_coin[next_sum] > DP_coin[j]+1){
							DP_coin[next_sum] = DP_coin[j]+1;
							conv_DP[next_sum] = conv_DP[j]+conv[i];
							info_DP[next_sum] = info_DP[j]+info[i];
						}
					}
				}
			}
		}
		if(DP_coin[S]==INT_MAXIMUM){
			cout << "not possible" << endl;
		}
		else{
			cout << DP_coin[S] << endl;
		}
	}

	return 0;
}
