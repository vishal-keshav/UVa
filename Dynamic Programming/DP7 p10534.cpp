#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
	int N;
	while(cin >> N){
		vector<int> input(N);
		for(int i=0;i<N;i++){
			cin >> input[i];
		}
		//vector<int> lis(N,1);
		//vector<int> lds(N,1);
		//Process for lis
		/*for(int i=1;i<N;i++){
			for(int j=0;j<i;j++){
				if(input[j] < input[i]){
					if(lis[i] < 1 + lis[j]){
						lis[i] = 1 + lis[j];
					}
				}
			}
		}*/
		vector<int> lis_efficient(N,1);
		vector<int> active_list_lis;

		active_list_lis.push_back(input[0]);
		int nr_active = 1;
		for(int i=1;i<N;i++){
			if(input[i] > active_list_lis[nr_active-1]){
				active_list_lis.push_back(input[i]);
				nr_active++;
				lis_efficient[i] = nr_active;
			}
			else{
				if(input[i] <= active_list_lis[0]){
					active_list_lis[0] = input[i];
					lis_efficient[i] = 1;
				}
				else{
					//Binary search the element at right position
					vector<int>::iterator iter = lower_bound(active_list_lis.begin(),active_list_lis.end(), input[i]);
					int index = iter-active_list_lis.begin();
					active_list_lis[index] = input[i];
					lis_efficient[i] = index+1;
				}
			}
		}

		//Process for lds
        /*for(int i=N-2;i>=0;i--){
			for(int j=N-1;j>i;j--){
				if(input[j] < input[i]){
					if(lds[i] < 1 + lds[j]){
						lds[i] = 1 + lds[j];
					}
				}
			}
		}*/

		vector<int> lds_efficient(N,1);
		vector<int> active_list_lds;

		active_list_lds.push_back(input[N-1]);
		nr_active = 1;
		for(int i=N-2;i>=0;i--){
			if(input[i] > active_list_lds[nr_active-1]){
				active_list_lds.push_back(input[i]);
				nr_active++;
				lds_efficient[i] = nr_active;
			}
			else{
				if(input[i] <= active_list_lds[0]){
					active_list_lds[0] = input[i];
					lds_efficient[i] = 1;
				}
				else{
					//Binary search the element at right position
					vector<int>::iterator iter = lower_bound(active_list_lds.begin(),active_list_lds.end(), input[i]);
					int index = iter-active_list_lds.begin();
					active_list_lds[index] = input[i];
					lds_efficient[i] = index+1;
				}
			}
		}

		//Compute maximum wavio sequence
		int max_wavio = 1;
		for(int i=0;i<N;i++){
			if(max_wavio < 2*min(lis_efficient[i],lds_efficient[i])-1){
				max_wavio = 2*min(lis_efficient[i],lds_efficient[i]) -1;
			}
		}
		cout << max_wavio << endl;
	}

	return 0;
}
