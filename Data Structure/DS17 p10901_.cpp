#include <iostream>
#include <stdio.h>
#include <string>
#include <queue>

using namespace std;

int side(string direction){
	if(direction == "left"){
		return 0;
	}
	else{
		return 1;
	}
}

int main(){
	int T,n,t,m;
	int global_clock,loading,my_side,arrival_time;
	string direction;

	cin >> T;
	while(T--){
		cin >> n >> t >> m;
		global_clock = 0;
		my_side = 0;
		queue<int> loading[2];
		while(m--){
			cin >> arrival_time >> direction;
			if(loading[0].empty() && loading[1].empty()){
				loading[side(direction)].push(arrival_time);
				global_clock = arrival_time;
				if(my_side!=side(direction)){
					global_clock+=t;
					my_side = 1-my_side;
				}
				continue;
			}
			if(global_clock >arrival_time){
				loading[side(direction)].push(arrival_time);
			}
			else{
				//Unload opposite side on its current side
				while(!loading[1-my_side].empty()){
					cout << global_clock << endl;
					loading[1-my_side].pop();
				}
				my_side = 1-my_side;
				global_clock+=t;
				if(global_clock >arrival_time){
					loading[side(direction)].push(arrival_time);
				}
				else{
					//Unload this side aswell
					while(!loading[1-my_side].empty()){
						cout << global_clock << endl;
						loading[1-my_side].pop();
					}
					loading[side(direction)].push(arrival_time);
					global_clock = arrival_time;
					if(my_side!=side(direction)){
						global_clock+=t;
						my_side = 1-my_side;
					}
				}
			}
		}
		//Unload opposite side
		while(!loading[1-my_side].empty()){
			cout << global_clock << endl;
			loading[1-my_side].pop();
		}
		my_side = 1-my_side;
		global_clock+=t;
		//Unload opposite side
		while(!loading[1-my_side].empty()){
			cout << global_clock << endl;
			loading[1-my_side].pop();
		}
	}
	return 0;
}
