#include <iostream>
#include <queue>
#include <stdio.h>
#include <string>

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
	int T,n,t,m,global_clock,loading,current_direction,arrival_time;
	string direction;
	cin >> T;
	while(T--){
		cin >> n >> t >> m;
		global_clock = 0;
		loading = 0;
		current_direction = 0;
		queue<int> arrival_queue;
		while(m--){
			cin >> arrival_time >> direction;
			/*Load car if
			1. Current direction matches with direction
			2. loading is not exceeding*/
			if(current_direction == side(direction) && loading < n){
				arrival_queue.push(arrival_time);
				if(arrival_time>global_clock){
					global_clock = arrival_time;
				}
				loading++;
			}
			//Asumming fully loading will never happpen, take care after if-else
			else if(current_direction!= side(direction)){
				//the arrival does not matches the side
				global_clock +=t;
				while(!arrival_queue.empty()){
					cout << global_clock << endl;
					arrival_queue.pop();
				}
				current_direction = 1-current_direction;
				//Load the new car
				arrival_queue.push(arrival_time);

				if(arrival_time>global_clock){
					global_clock = arrival_time;
				}
			}
			//Taking care of fully loading
			if(loading == n){
				global_clock +=t;
				while(!arrival_queue.empty()){
					cout << global_clock << endl;
					arrival_queue.pop();
				}
				current_direction = 1-current_direction;
			}
		}
		cout << endl;
	}
	return 0;
}
