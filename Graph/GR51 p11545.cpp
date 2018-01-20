#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

#define INF 10000000
string path;

int compute_time(int loc, int time_cost, int time, int walked){
	if(path[loc]=='D'){
		return time_cost;
	}
	else{
		
	}
}

int main(){
	int T,nr_case=1;
	cin >> T;
	while(T--){
		cin >> path;
		cout << "Case #" << nr_case << ": " << compute_time(1, 1, 6, 1) << endl;
	}
	
	return 0;
}