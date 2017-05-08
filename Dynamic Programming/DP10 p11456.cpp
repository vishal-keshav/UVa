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
		if(!N){
            cout << "0" << endl;
            continue;
		}
		vector<int> car_weight(N);
		for(int i=0;i<N;i++){
			cin >> car_weight[i];
		}
		vector<int> reverse_lis(N,1);
		vector<int> reverse_lds(N,1);
		for(int i=N-2;i>=0;i--){
			for(int j=N-1;j>i;j--){
				if(car_weight[i] < car_weight[j]){
					if(reverse_lis[i]<1+reverse_lis[j]){
						reverse_lis[i] = reverse_lis[j] + 1;
					}
				}
			}
		}
		for(int i=N-2;i>=0;i--){
			for(int j=N-1;j>i;j--){
				if(car_weight[i] > car_weight[j]){
					if(reverse_lds[i]<1+reverse_lds[j]){
						reverse_lds[i] = reverse_lds[j] + 1;
					}
				}
			}
		}
		int res = 0;
		for(int i=0;i<N;i++){
			if(res<reverse_lis[i]+reverse_lds[i]-1){
				res = reverse_lis[i] + reverse_lds[i] -1;
			}
		}
		cout << res << endl;
	}
	return 0;
}
