#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

#define INF 10000000
string path;

vector<vector<vector<int> > > memo;

int compute_time(int loc, int time, int walked){
    if(memo[loc][time][walked]!=-1){
        return memo[loc][time][walked];
    }
	if(path[loc]=='D'){
        memo[loc][time][walked] = 0;
		return 0;
	}
    if (((time <= 6 || time >= 18) && path[loc] == '*')||(walked > 16)){
        memo[loc][time][walked] = INF;
        return INF;
	}
    int time_cost = 1 + compute_time(loc+1, (time+1)%24, walked+1);
	int sleep_cost = 9 + compute_time(loc+1, (time+9)%24, 1);
	time_cost = min(time_cost, sleep_cost);
	memo[loc][time][walked] = time_cost;
	return time_cost;
}

int main(){
    //freopen("output.txt","w",stdout);
	int T,nr_case=1;
	cin >> T;
	while(T--){
		cin >> path;
		memo.clear();
		memo.resize(path.size()+1, vector<vector<int> >(25, vector<int>(25,-1)));
		int res = compute_time(0, 6, 0);
		if(res >= INF){
            cout << "Case #" << nr_case << ": " << -1 << endl;
		}
		else{
            cout << "Case #" << nr_case << ": " << res << endl;
		}
		nr_case++;
	}

	return 0;
}
