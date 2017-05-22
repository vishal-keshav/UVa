#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

vector<int> denom(300,0);
vector<vector<int> > DP(301,vector<int>(1005,0));
vector<vector<int> > DP_sum(301,vector<int>(1005,0));

void init(void){
	for(int i=0;i<300;i++){
		denom[i] = i+1;
	}
	DP[0][0] = 1;
	for(int i=0;i<300;i++){
		for(int j=1;j<=300;j++){
			for(int k=1;k<=1001;k++){
				if(j-denom[i]>=0){
					DP[j][k]+=DP[j-denom[i]][k-1];
				}
			}
		}
	}
	for(int i=0;i<=300;i++){
		DP_sum[i][0] = DP[i][0];
		for(int j=1;j<=1001;j++){
			DP_sum[i][j] = DP_sum[i][j-1]+DP[i][j];
		}
	}
}

int main(){
    //freopen("output.txt","w",stdout);
	string input;
	int N,L1,L2;
	init();
	while(getline(cin,input)){
		stringstream ss(input);
		vector<int> input_int(3,-1);
		int index = 0;
		while(ss >> input_int[index]){
			index++;
		}
		vector<int> denom(input_int[0]);
		for(int i=0;i<input_int[0];i++){
			denom[i] = i+1;
		}
		int ret=0;
		//Case 1: Only N
		if(index==1){
			N = input_int[0];
			ret = DP_sum[N][1001];
		}
		//Case 2: N and L1
		else if(index==2){
			N = input_int[0];
			L1 = input_int[1];
			ret = DP_sum[N][L1];
		}
		//Case 3: N, L1, L2
		else if(index==3){
			N = input_int[0];
			L1 = input_int[1];
			L2 = input_int[2];
			ret = DP_sum[N][L2] - DP[N][L1-1];
		}
		else{
            continue;
		}
		cout << ret << endl;
	}

	return 0;
}
