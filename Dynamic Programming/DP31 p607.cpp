#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

int N,L,C;
vector<int> topic;

int di(int t){
	if(t==0){
		return t;
	}
	if(t>10){
		return ((t-10)*(t-10));
	}
	else{
		return -C;
	}
}

int main(){
	cin >> N;
	while(N){
		cin >> L >> C;
		topic.clear();
		topic.resize(N);
		for(int i=0; i<N; i++){
			cin >> topic[i];
		}
		
		cin >> N;
	}
	return 0;
}