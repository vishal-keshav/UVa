#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

#define INT_MAXIMUM 10000000

using namespace std;

vector<int> input;
vector<vector<int> > DP;

int min_cost(int start_index, int end_index){
    if(DP[start_index][end_index]!=-1){
        return DP[start_index][end_index];
    }
	if(start_index+1==end_index){
        DP[start_index][end_index] = 0;
		return 0;
	}
	else{
		int ret = INT_MAXIMUM;
		for(int i=start_index+1;i<end_index;i++){
			ret = min(ret,min_cost(start_index,i)+min_cost(i,end_index)+(input[end_index]-input[start_index]));
		}
        DP[start_index][end_index] = ret;
		return ret;
	}
}

int main(){
	int L,N;
	cin >> L;
	while(L){
		cin >> N;
		input.clear();
		input.resize(N+2);
		input[0] = 0;
		for(int i=1;i<=N;i++){
			cin >> input[i];
		}
		input[N+1] = L;
		DP.clear();
		DP.resize(N+2,vector<int>(N+2,-1));
        cout << "The minimum cutting is " << min_cost(0,N+1) << "."<< endl;
		cin >> L;
	}


	return 0;
}
