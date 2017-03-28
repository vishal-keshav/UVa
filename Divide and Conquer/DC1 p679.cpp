#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

int node_number(int d, int i, int child_id){
	//Base case
	if(d==0){
		return child_id;
	}
	else{
		//Check for left
		if(i%2==1){
			return node_number(d-1, (i+1)/2, 2*child_id);
		}
		else{
			return node_number(d-1, i/2, 2*child_id+1);
		}
	}
}

int main(){
	int T,D,I;
	cin >> T;
	while(T--){
		cin >> D >> I;
		cout << node_number(D-1,I,1) << endl;
	}
	cin >> T;
	return 0;
}
