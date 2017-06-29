#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <math.h>

//#define DEBUG 1

using namespace std;

int T,N;
vector<int> input;
vector<int> length;

void fill_length(int index, int bitmask){
	if(index>=N){
		return;
	}
	else{
		//Dont take this
		fill_length(index+1, bitmask);
		//Take this
		length[bitmask | 1<<index] = length[bitmask]+input[index];
		fill_length(index+1,bitmask | 1<<index);
	}
}

int main(){
	cin >> T;
	while(T--){
		cin >> N;
		input.clear();
		input.resize(N);
		for(int i=0;i<N;i++){
			cin >> input[i];
		}
		length.clear();
		length.resize(pow(2,N),0);
		fill_length(0,0);
#ifdef DEBUG
        for(int i=0;i<pow(2,N);i++){
            cout << i << " " << length[i] << endl;
        }
#endif // DEBUG
	}

	return 0;
}
