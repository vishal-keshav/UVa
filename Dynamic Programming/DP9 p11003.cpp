#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

#define INT_MAXIMUM 100000000

int N;
vector<int> weight(1001);
vector<int> load(1001);
vector<vector<int> > DP(1001,vector<int>(6002));

int get_max_len(int block_index, int remaining_capacity){
	if(DP[block_index][remaining_capacity]!=-1){
        return DP[block_index][remaining_capacity];
	}
	//Base case
	if(block_index==N || remaining_capacity<0){
		return 0;
	}
	//Main case
	else{
		if(weight[block_index] > remaining_capacity){
			//Skip this block, stack from next block
			DP[block_index][remaining_capacity] = get_max_len(block_index+1,remaining_capacity);
		}
		else{
			//Two cases:
			//1. take this block, then remaining capacity will decrease by its weight
			//2. dont take this block, remaining capacity to stack will remain same

			/*Caes 1: If current block is putting a cap on remaining capacity, then take that*/
			int case_two = get_max_len(block_index+1, remaining_capacity);
			int case_one = 1 + get_max_len(block_index+1, min(load[block_index],remaining_capacity-weight[block_index]));


			DP[block_index][remaining_capacity] = max(case_one, case_two);
		}
		return DP[block_index][remaining_capacity];
	}
}

int main(){
    //freopen("output.txt","w",stdout);
	cin >> N;
	while(N){
		for(int i=0;i<N;i++){
			cin >> weight[i] >> load[i];
		}
		//Initialize DP
		for(int i=0;i<=N;i++){
			for(int j=0;j<6002;j++){
				DP[i][j] = -1;
			}
		}
		//Apply top-to-bottom approach, easy to understand in recursion
		int max_len = get_max_len(0,6001);

		cout << max_len << endl;

		cin >> N;
	}

	return 0;
}
