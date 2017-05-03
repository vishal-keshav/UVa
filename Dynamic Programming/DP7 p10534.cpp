#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    //freopen("output.txt","w",stdout);
	int N;
	while(cin >> N){
		vector<int> input(N);
		for(int i=0;i<N;i++){
			cin >> input[i];
		}
		vector<int> lis(N,1);
		vector<int> lds(N,1);
		//Process for lis
		for(int i=1;i<N;i++){
			for(int j=0;j<i;j++){
				if(input[j] < input[i]){
					if(lis[i] < 1 + lis[j]){
						lis[i] = 1 + lis[j];
					}
				}
			}
		}
		//Process for lds
        for(int i=N-2;i>=0;i--){
			for(int j=N-1;j>i;j--){
				if(input[j] < input[i]){
					if(lds[i] < 1 + lds[j]){
						lds[i] = 1 + lds[j];
					}
				}
			}
		}
		//Compute maximum wavio sequence
		int max_wavio = 1;
		for(int i=0;i<N;i++){
			if(max_wavio < 2*min(lis[i],lds[i])-1){
				max_wavio = 2*min(lis[i],lds[i]) -1;
			}
		}
		cout << max_wavio << endl;
	}

	return 0;
}
