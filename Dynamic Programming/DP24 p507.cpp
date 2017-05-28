#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

int main(){
	int T,N,nr_case=1;
	cin >> T;
	while(T--){
		cin >> N;
		vector<int> nice(N-1);
		for(int i=0;i<N-1;i++){
			cin >> nice[i];
		}

		int idx_start = -1, idx_end = 0;
		int idx_latest = 0;
		int running_max = 0, last_max = 0;

		for(int i=0;i<N-1;i++){
			running_max+=nice[i];
			if(running_max < 0){
				running_max = 0;
				if(idx_start==-1){
                    idx_start = i;
				}
				idx_latest = i+1;
			}
			if(last_max < running_max){
				last_max = running_max;
                idx_start = idx_latest;
                idx_end = i;
			}
			if(last_max == running_max){
                if(idx_end-idx_start < i-idx_latest){
                    idx_start = idx_latest;
                    idx_end = i;
                }
			}
		}

		if(last_max==0){
			cout << "Route " << nr_case << " has no nice parts" << endl;
		}
		else{
			cout << "The nicest part of route " << nr_case <<  " is between stops " << idx_start+1 << " and " << idx_end+2 << endl;
		}
		nr_case++;
	}
	return 0;
}
