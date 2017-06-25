#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

int n,r;
double b,v,e,f;
vector<int> dist;

double tire(int x){
	if(x>=r){
		return (double)(1/(v-e*(double)(x-r)));
	}
	else{
		return (double)(1/(v-f*(double)(r-x)));
	}
}

double cal_time(int dest_index, int start_index){
	double ret = 0;
	for(int i=0;i<dist[dest_index]-dist[start_index];i++){
		ret+=tire(i);
	}
	return ret;
}

double race_time(int dist_index, int change_index){
	//Base
	if(dist_index>=n){
		double ret = cal_time(dist_index,change_index);
		return ret;
	}
	else{
		double time_took = cal_time(dist_index,change_index);
		//Case1: Change tire here
		double time1 = race_time(dist_index+1, dist_index) + b + time_took;
		//Case 2: Do not chnage tire, go ahead
		double time2 = race_time(dist_index+1, change_index);
		return min(time1,time2);
	}
}

int main(){
	cin >> n;
	while(n){
		dist.clear();
		dist.resize(n+1);
		dist[0] = 0;
		for(int i=0;i<n;i++){
			cin >> dist[i+1];
		}
		cin >> b >> r >> v >> e >> f;
		cout << race_time(1,0) << endl;

		cin >> n;
	}
	return 0;
}
