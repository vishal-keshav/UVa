#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

int N;
vector<int> input;

bool square(int l1, int l2, int l3, int l4){
    if(l1+l2+l3+l4==0){
		return false;
	}
	if(l1==l2 && l3==l4 && l2==l3){
		return true;
	}
	return false;
}

bool can_make_square(int l1, int l2, int l3, int l4, int index){
	if(square(l1,l2,l3,l4)){
		return true;
	}
    else if(index>=N){
		return false;
	}
	//Main
	else{
		bool ret = false;
		//Case 1: dont take in any side
		ret = ret || can_make_square(l1,l2,l3,l4,index+1);
		//Case 2: take in first
		ret = ret || can_make_square(l1+input[index],l2,l3,l4,index+1);
		//Case 3: take in second
		ret = ret || can_make_square(l1,l2+input[index],l3,l4,index+1);
		//Case 4: take in third
		ret = ret || can_make_square(l1,l2,l3+input[index],l4,index+1);
		//Case 5: take in fourth
		ret = ret || can_make_square(l1,l2,l3,l4+input[index],index+1);
		return ret;
	}
}

int main(){
	int T;
	cin >> T;
	while(T--){
		cin >> N;
		input.clear();
		input.resize(N);
		for(int i=0;i<N;i++){
			cin >> input[i];
		}
		if(can_make_square(0,0,0,0,0)){
			cout << "yes" << endl;
		}
		else{
			cout << "no" << endl;
		}
	}

	return 0;
}
