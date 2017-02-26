#include <iostream>
#include <stdio.h>
#include <queue>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX_INT 1000000000

int maximum(int a, int b){
    if(a>b){
        return a;
    }
    else{
        return b;
    }
}

struct arrival{
	int arrival_time;
	int arrival_side;
	int index;
};

int side(string direction){
	if(direction == "left"){
		return 0;
	}
	else{
		return 1;
	}
}

bool comp(struct arrival elem1, struct arrival elem2){
	return (elem1.index < elem2.index);
}
int main(){
    freopen("output.txt","w",stdout);
	int T,n,t,m;
	int global_clock,loading,my_side,arrival_time,loading_nr;
	int my_side_top,other_side_top;
	string direction;

	cin >> T;
	while(T--){
		cin >> n >> t >> m;
		queue<struct arrival> loading[2];
		struct arrival temp;
		int index_count = 1;
		while(m--){
			cin >> arrival_time >> direction;
			temp.arrival_time = arrival_time;
			temp.arrival_side = side(direction);
			temp.index = index_count;
			index_count ++;
			loading[side(direction)].push(temp);
			//cout << "Pushing done" << endl;
		}
#ifdef DEBUG

#endif
        //cout << loading.front().arrival_time << endl;
        //cout << loading.back().arrival_time << endl;
		my_side = 0;
		global_clock = 0;
		//Reusing arrival structure
		vector<struct arrival> result;
		struct arrival push_elem;
		while(!loading[0].empty() || !loading[1].empty()){
			if(global_clock >=loading[my_side].front().arrival_time){
				loading_nr = n;
				while(!loading[my_side].empty() && global_clock >= loading[my_side].front().arrival_time && loading_nr>0){
					//cout << global_clock + t << endl;
					push_elem.arrival_time = loading[my_side].front().arrival_time;
					push_elem.arrival_side = global_clock+t;
					push_elem.index = loading[my_side].front().index;
					result.push_back(push_elem);
					loading[my_side].pop();
					loading_nr--;
				}
				global_clock+=t;
				my_side = 1-my_side;
			}
			else{
				//Determine minimum of top element of two side
				if(!loading[my_side].empty()){
					my_side_top = loading[my_side].front().arrival_time;
				}
				else{
					my_side_top = MAX_INT;
				}
				if(!loading[1-my_side].empty()){
					other_side_top = loading[1-my_side].front().arrival_time;
				}
				else{
					other_side_top = MAX_INT;
				}
				if(my_side_top <= other_side_top){
					global_clock = loading[my_side].front().arrival_time;
				}
				else{
					global_clock = maximum(global_clock+t,loading[1-my_side].front().arrival_time + t);
					my_side = 1-my_side;
				}
			}
		}
		sort(result.begin(),result.end(),comp);
		for(vector<struct arrival>::iterator iter = result.begin();iter!=result.end();iter++){
			cout << (*iter).arrival_side << endl;
		}

		if(T!=0){
            cout << endl;
		}
	}
	return 0;
}
