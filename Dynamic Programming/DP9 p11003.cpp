#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
	int N;
	cin >> N;
	while(N){
		vector<int> weight(N);
		vector<int> load(N);
		for(int i=0;i<N;i++){
			cin >> weight[i] >> load[i];
		}
		vector<int> lis_load(N);
		vector<int> lis(N,1);
		int max_lis = 1;
		for(int i=0;i<N;i++){
			lis_load[i] = 0;
		}
		for(int i=1;i<N;i++){
			for(int j=0;j<i;j++){
				if(weight[i]+lis_load[j] < load[i]){
					if(lis[i]<1+lis[j]){
						lis[i] = 1 + lis[j];
						lis_load[i] = lis_load[j] + weight[i];
						if(lis[i] > max_lis){
							max_lis = lis[i];
						}
					}
				}
			}
		}
		cout << max_lis << endl;
		cin >> N;
	}

	return 0;
}
