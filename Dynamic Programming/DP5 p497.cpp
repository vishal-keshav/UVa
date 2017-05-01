#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <stack>

using namespace std;

int main(){
	int T;
	cin >> T;
	cin.ignore();
	cin.ignore();
	for(int i=0;i<T;i++){
		string input;
		vector<int> missiles;
		int temp_missile;
		while(getline(cin,input) && input!=""){
			stringstream ss(input);
			ss >> temp_missile;
			missiles.push_back(temp_missile);
		}
		vector<int> lis(missiles.size(),1);
		vector<int> parent(missiles.size(),-1);
		int best_result=1;
		int best_index=0;

		for(int i=1;i<missiles.size();i++){
			for(int j=0;j<i;j++){
				if(missiles[j] < missiles[i]){
					if(lis[i]<1+lis[j]){
						lis[i] = 1+lis[j];
						parent[i] = j;
						if(lis[i]>best_result){
							best_result = lis[i];
							best_index = i;
						}
					}
				}
			}
		}
		cout << "Max hits: " << best_result << endl;
		stack<int> result;
		int iter_index = best_index;
		while(iter_index!=-1){
			result.push(missiles[iter_index]);
			iter_index = parent[iter_index];
		}
		while(!result.empty()){
			cout << result.top() << endl;
			result.pop();
		}
		cout << endl;
	}

	return 0;
}
