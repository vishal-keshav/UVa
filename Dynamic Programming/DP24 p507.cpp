#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

int main(){
    //freopen("output.txt","w",stdout);
	int T,N,nr_case=1;
	cin >> T;
	while(T--){
		cin >> N;
		vector<int> nice(N-1);
		for(int i=0;i<N-1;i++){
			cin >> nice[i];
		}
		//Apply kadane's algorithm
		vector<int> DP(N,0);
		for(int i=0;i<N-1;i++){
			DP[i+1] = DP[i] + nice[i];
		}
		int start_idx = -1, end_idx = -1;
		int length = 0, sum_nice = 0;
		for(int i=1;i<N;i++){
			for(int j=1;j<=i;j++){
				if(sum_nice < DP[i]-DP[j-1]){
					sum_nice = DP[i] - DP[j-1];
					start_idx = j;
					end_idx = i+1;
					length = i-j+1;
				}
				else if(sum_nice == DP[i] - DP[j-1]){
					if(length < i-j+1){
						start_idx = j;
						end_idx = i+1;
						length = i-j+1;
					}
				}
			}
		}
		if(length==0){
			cout << "Route " << nr_case << " has no nice parts" << endl;
		}
		else{
			cout << "The nicest part of route " << nr_case <<  " is between stops " << start_idx << " and " << end_idx << endl;
		}
		nr_case++;
	}
	return 0;
}
