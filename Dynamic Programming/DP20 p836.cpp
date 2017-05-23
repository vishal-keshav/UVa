#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int main(){
	int N;
	cin >> N;
	while(N--){
		string input;
		cin >> input;
		int sz = input.size();
		vector<vector<int> > arr(sz,vector<int>(sz));
		for(int i=0;i<sz;i++){
			arr[0][i] = (input[i]=='1')?1:0;
		}
		for(int i=1;i<sz;i++){
			cin >> input;
			for(int j=0;j<sz;j++){
				arr[i][j] = (input[j]=='1')?1:0;
			}
		}

		vector<vector<int> > DP_sum(sz+1,vector<int>(sz+1));
		for(int i=0;i<=sz;i++){
			DP_sum[i][0] = 0;
			DP_sum[0][i] = 0;
		}
		//Fill DP_sum
		for(int i=0;i<sz;i++){
			for(int j=0;j<sz;j++){
				DP_sum[i+1][j+1] = arr[i][j] + DP_sum[i][j+1] + DP_sum[i+1][j] - DP_sum[i][j];
			}
		}
		int temp,ret=0;
		for(int i=1;i<=sz;i++){
			for(int j=1;j<=sz;j++){
				for(int k=i;k<=sz;k++){
					for(int l=j;l<=sz;l++){
						temp = DP_sum[k][l] - DP_sum[k][j-1] - DP_sum[i-1][l] + DP_sum[i-1][j-1];
						if(temp == (k-i+1)*(l-j+1) && temp>ret){
							ret = temp;
						}
					}
				}
			}
		}
		cout << ret << endl;
		if(N){
            cout << endl;
		}
	}

	return 0;
}
