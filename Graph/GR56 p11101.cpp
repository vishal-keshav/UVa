#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

#define INT_MAXIMUM 1000000

struct loc{
	int x,y;
};

int m1,m2;
vector<vector<int> > city(2001, vector<int>(2001));
queue<struct loc> bfs_queue;

struct loc null;
int move_x[4] = {-1, 0, 1, 0};
int move_y[4] = {0, 1, 0, -1};

bool valid(struct loc l){
	if(l.x>=0 && l.x<=2000 && l.y>=0 && l.y<=2000){
		if(city[l.x][l.y]==INT_MAXIMUM){
			return true;
		}
		else if(city[l.x][l.y]==0){
            city[l.x][l.y] = 1;
            return true;
		}
	}
	return false;
}

int calculate_dist(void){
	int ret = 0;
	while(!bfs_queue.empty()){
		struct loc temp = bfs_queue.front();
		bfs_queue.pop();
		if(temp.x == -1){
			bfs_queue.push(null);
			ret++;
		}
		else{
			if(city[temp.x][temp.y]==INT_MAXIMUM){
				return ret;
			}
			else{
				struct loc new_loc;
				for(int i=0;i<4;i++){
					new_loc.x = temp.x+move_x[i];
					new_loc.y = temp.y+move_y[i];
					if(valid(new_loc)){
						bfs_queue.push(new_loc);
					}
				}
			}
		}
	}
	return ret;
}

int main(){
	struct loc temp_loc;
	int x,y;
	null.x = -1;
	null.y = -1;
	cin >> m1;
	while(m1){
		//Clear out city map
		for(int i=0;i<=2000;i++){
			for(int j=0;j<=2000;j++){
				city[i][j] = 0;
			}
		}
		//Clear queue
		while(!bfs_queue.empty()){
			bfs_queue.pop();
		}
		for(int i=0;i<m1;i++){
			cin >> x >> y;
			city[x][y] = 0;
			temp_loc.x = x;
			temp_loc.y = y;
			bfs_queue.push(temp_loc);
			city[x][y] = 1;
		}
		temp_loc.x = -1;
		temp_loc.y = -1;
		bfs_queue.push(null);
		cin >> m2;
		for(int i=0;i<m2;i++){
			cin >> x >> y;
			city[x][y] = INT_MAXIMUM;
		}

		cout << calculate_dist() << endl;
		cin >> m1;
	}

	return 0;
}
