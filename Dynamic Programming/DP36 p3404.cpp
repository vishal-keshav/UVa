#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

int n,r;
double b,v,e,f;
vector<int> dist;

vector<double> pre_compute;
vector<vector<double> > DP;

double tire(int x){
	if(x>=r){
		return (double)(1/(v-e*(double)(x-r)));
	}
	else{
		return (double)(1/(v-f*(double)(r-x)));
	}
}

double cal_time(int dest_index, int start_index){
	return pre_compute[dist[dest_index]-dist[start_index]-1];
}

void initialize(void){
    pre_compute.clear();
    pre_compute.resize(dist[n]);
    for(int i=0;i<dist[n];i++){
        pre_compute[i] = tire(i);
    }
    for(int i=1;i<dist[n];i++){
        pre_compute[i]+= pre_compute[i-1];
    }
    DP.clear();
    DP.resize(n+1,vector<double>(n+1,-1));
    return;
}

double race_time(int dist_index, int change_index){
    if(dist_index<=n && DP[dist_index][change_index]!=-1){
        return DP[dist_index][change_index];
    }
	//Base
	if(dist_index>=n){
		double ret = cal_time(dist_index,change_index);
		DP[dist_index][change_index] = ret;
		return ret;
	}
	else{
		double time_took = cal_time(dist_index,change_index);
		//Case1: Change tire here
		double time1 = race_time(dist_index+1, dist_index) + b + time_took;
		//Case 2: Do not chnage tire, go ahead
		double time2 = race_time(dist_index+1, change_index);
		DP[dist_index][change_index] = min(time1,time2);
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

		initialize();

        printf("%0.4f\n",race_time(1,0));
		//cout << race_time(1,0) << endl;

		cin >> n;
	}
	return 0;
}
