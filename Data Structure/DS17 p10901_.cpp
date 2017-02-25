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
    //freopen("output.txt","w",stdout);
	int T,n,t,m;
	int global_clock,loading,my_side,arrival_time,loading_nr;
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
				loading_nr=n;
				while(!loading[1-my_side].empty() && loading_nr>0){
					cout << global_clock << endl;
					loading[1-my_side].pop();
					loading_nr--;
				}
				my_side = 1-my_side;
				global_clock+=t;
				loading_nr=n;
				while(!loading[1-my_side].empty() && loading_nr>0){
					cout << global_clock << endl;
					loading[1-my_side].pop();
					loading_nr--;
				}
				//global_clock+=t;
				if(global_clock >arrival_time){
					loading[side(direction)].push(arrival_time);
				}
				else{
					loading[side(direction)].push(arrival_time);
					global_clock = arrival_time;
					if(my_side!=side(direction)){
						global_clock+=t;
						my_side = 1-my_side;
					}
				}
			}
		}

		//Uloading rest of the cars in turn
		while(!loading[0].empty() || !loading[1].empty()){
			loading_nr = n;
			while(!loading[1-my_side].empty() && loading_nr>0){
				cout << global_clock << endl;
				loading[1-my_side].pop();
				loading_nr--;
			}
			my_side = 1-my_side;
			global_clock+=t;
		}
		if(T!=0){
            cout << endl;
		}
	}
	return 0;
}
