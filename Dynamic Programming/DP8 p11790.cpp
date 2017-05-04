#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
	int T,N,nr_case=1;
	cin >> T;
	while(T--){
		cin >> N;
		vector<int> height(N);
		vector<int> width(N);
		for(int i=0;i<N;i++){
			cin >> height[i];
		}
		for(int i=0;i<N;i++){
			cin >> width[i];
		}
		//Processing for lis
		vector<int> lis(N);
		int max_lis = 0;
		for(int i=0;i<N;i++){
			lis[i] = width[i];
			if(lis[i]>max_lis){
				max_lis = lis[i];
			}
		}
		for(int i=1;i<N;i++){
			for(int j=0;j<i;j++){
				if(height[i]>height[j]){
					if(lis[i]<lis[j]+width[i]){
						lis[i] = lis[j] + width[i];
						if(lis[i]>max_lis){
							max_lis = lis[i];
						}
					}
				}
			}
		}
		//Processing for lds
		vector<int> lds(N);
		int max_lds = 0;
		for(int i=0;i<N;i++){
			lds[i] = width[i];
			if(lds[i]>max_lds){
				max_lds = lds[i];
			}
		}
		for(int i=1;i<N;i++){
			for(int j=0;j<i;j++){
				if(height[i]<height[j]){
					if(lds[i]<lds[j]+width[i]){
						lds[i] = lds[j] + width[i];
						if(lds[i]>max_lds){
							max_lds = lds[i];
						}
					}
				}
			}
		}
		cout << "Case " << nr_case << ". ";
		if(max_lis>=max_lds){
			cout << "Increasing (" << max_lis << "). Decreasing (" << max_lds << ")." << endl;
		}
		else{
			cout << "Decreasing (" << max_lds << "). Increasing (" << max_lis << ")." << endl;
		}
		nr_case++;
	}

	return 0;
}
