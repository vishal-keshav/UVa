#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

#define INT_MINIMUM -1000000

using namespace std;

vector<int> arr;

int sum(int i, int j){
	int ret = 0;
	for(int k=i;k<=j;k++){
		ret+=arr[k];
	}
	return ret;
}

int max_score(int s_index, int e_index){
	if(s_index>e_index){
		return 0;
	}
	else if(s_index==e_index){
		return arr[s_index];
	}
	else{
		int ret = INT_MINIMUM;
		//Left part
		for(int i=s_index;i<=e_index;i++){
			ret = max(ret, sum(s_index,i)+sum(i+1,e_index)-max_score(i+1,e_index));
		}
		//Right part
		for(int i=e_index;i>=s_index;i--){
			ret = max(ret, sum(i,e_index)+sum(s_index,i-1)-max_score(s_index,i-1));
		}
		return ret;
	}
}

int main(){
	int N;
	cin >> N;
	while(N){
		arr.clear();
		arr.resize(N);
		for(int i=0;i<N;i++){
			cin >> arr[i];
		}
		cout << max_score(0,N-1) << endl;
		
		cin >> N;
	}
	
	return 0;
}