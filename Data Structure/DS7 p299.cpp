#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int bubble_sort(vector<int> vec){
	int inversions = 0,len = vec.size();
	int temp;
	for(int i=0;i<len;i++){
		for(int j=0;j<len-1;j++){
			if(vec[j] > vec[j+1]){
				temp = vec[j];
				vec[j] = vec[j+1];
				vec[j+1] = temp;
				inversions++;
			}
		}
	}
	return inversions;
}

int main(){
	int T,N,t;
	cin >> T;
	while(T--){
		cin >> N;
		vector<int> vec;
		for(int i=0;i<N;i++){
			cin >> t;
			vec.push_back(t);
		}
		cout << "Optimal train swapping takes " << bubble_sort(vec) << " swaps."<<endl;
	}
	return 0;
}
