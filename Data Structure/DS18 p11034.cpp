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

struct arrival{
	int arrival_len;
	int arrival_side;
	int arrival_order;
};


int main(){
	int T,l,m;
	int len,index;
	string direction;
	cin >> T;
	while(T--){
		cin >> l >> m;
		queue<struct arrival> loading[2];
		struct arrival temp;
		index = 1;
		while(m--){
			cin >> len >> direction;
			temp.arrival_len = len;
			temp.arrival_side = side(direction);
			temp.arrival_order = index;
			loading[side(direction)].push(temp);
			index++;
		}
		//cout << "Done";
		int my_side = 0;
		int nr_movement = 0;
		int load_size;
		while(!loading[0].empty() || !loading[1].empty()){
			load_size = 0;
			while(!loading[my_side].empty() && load_size+loading[my_side].front().arrival_len<=l*100){
				load_size+=loading[my_side].front().arrival_len;
				loading[my_side].pop();
			}
			my_side = 1-my_side;
			nr_movement++;
		}
		cout << nr_movement << endl;
	}

	return 0;
}
