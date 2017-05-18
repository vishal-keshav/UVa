#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

#define INT_MAXIMUM 1000000

using namespace std;

int modulo_int(int a, int b){
	int ret = (a*a + b*b);
	//ret = (long long int)sqrt((double)ret+0.05);
	return ret;
}

int main(){
    //freopen("output.txt","w",stdout);
	int T,m,S;
	cin >> T;
	while(T--){
		cin >> m >> S;
		vector<int> conv(m);
		vector<int> info(m);
		for(int i=0;i<m;i++){
			cin >> conv[i] >> info[i];
		}
		int nr_coins = INT_MAXIMUM;
		vector<vector<int> > DP(S+1,vector<int>(S+1,INT_MAXIMUM));
		DP[0][0] = 0;
		for(int i=0;i<m;i++){
			for(int j=0;j<=S;j++){
				for(int k=0;k<=S;k++){
					if(DP[j][k]!=INT_MAXIMUM){
						if(j+conv[i] <=S && k+info[i]<=S){
							DP[j+conv[i]][k+info[i]] = min(DP[j+conv[i]][k+info[i]],1+DP[j][k]);
							if(modulo_int(j+conv[i],k+info[i]) == S*S){
								if(DP[j+conv[i]][k+info[i]] < nr_coins){
									nr_coins = DP[j+conv[i]][k+info[i]];
								}
							}
						}
					}
				}
			}
		}
		if(nr_coins==INT_MAXIMUM){
			cout << "not possible" << endl;
		}
		else{
			cout << nr_coins << endl;
		}
	}

	return 0;
}
