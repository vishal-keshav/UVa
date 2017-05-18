#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

int main(){
	string input;
	int N,L1,L2;
	while(getline(cin,input)){
		stringstream ss(input);
		vector<int> input_int(3,-1);
		int index = 0;
		while(ss >> input_int[index]){
			index++;
		}
		//Case 1: Only N
		if(index==1){
			N = input_int[0];
		}
		//Case 2: N and L1
		else if(index==2){
			N = input_int[0];
			L1 = input_int[1];
		}
		//Case 3: N, L1, L2
		else{
			N = input_int[0];
			L1 = input_int[1];
			L2 = input_int[2];
		}
	}

	return 0;
}
