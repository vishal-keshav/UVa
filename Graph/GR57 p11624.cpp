#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int N,M;
struct coord{
	int x,y;
};
struct coord null;
int move_x[4] = {-1, 0, 1, 0};
int move_y[4] = {0, 1, 0, -1};
vector<vector<char> > maze;
queue<struct coord> fire_queue;
queue<struct coord> joe_queue;

void clear_queue(void){
	while(!fire_queue.empty()){
		fire_queue.pop();
	}
	while(!joe_queue.empty()){
		joe_queue.pop();
	}
	return;
}

bool in_bound(struct coord l){
	if(l.x>=0 && l.x<N && l.y>=0 && l.y<M){
		return true;
	}
	return false;
}

int get_path(void){
	int ret = 0;
	while(1){

		//Fire spreads
		while(!fire_queue.empty()){
			struct coord t = fire_queue.front();
			fire_queue.pop();
			if(t.x==-1){
				fire_queue.push(null);
				break;
			}
			else{
				struct coord new_coord;
				for(int i=0;i<4;i++){
					new_coord.x = t.x+move_x[i];
					new_coord.y = t.y+move_y[i];
					if(in_bound(new_coord) && maze[new_coord.x][new_coord.y]=='.'){
						fire_queue.push(new_coord);
						maze[new_coord.x][new_coord.y] = 'F';
					}
				}
			}
		}

        //Joe takes step
		bool could_move = false;
		while(!joe_queue.empty()){
			struct coord t = joe_queue.front();
			joe_queue.pop();
			if(t.x == -1){
				joe_queue.push(null);
				ret++;
				break;
			}
			else{
				struct coord new_coord;
				for(int i=0;i<4;i++){
					new_coord.x = t.x+move_x[i];
					new_coord.y = t.y+move_y[i];
					if(!in_bound(new_coord)){
						return ret;
					}
					else{
						if(maze[new_coord.x][new_coord.y]=='.'){
							could_move = true;
							joe_queue.push(new_coord);
							maze[new_coord.x][new_coord.y] = 'J';
						}
					}
				}
			}
		}
		if(!could_move){
			return -1;
		}
	}
}

int main(){
    //freopen("output.txt","w",stdout);
	int T;
	struct coord temp_loc;
	cin >> T;
	null.x = -1;
	null.y = -1;
	while(T--){
		cin >> N >> M;
		maze.clear();
		maze.resize(N,vector<char>(M));
		clear_queue();
		for(int i=0;i<N;i++){
			for(int j=0;j<M;j++){
				cin >> maze[i][j];
				if(maze[i][j]=='J'){
					temp_loc.x = i;
					temp_loc.y = j;
					joe_queue.push(temp_loc);
				}
				if(maze[i][j]=='F'){
					temp_loc.x = i;
					temp_loc.y = j;
					fire_queue.push(temp_loc);
				}
			}
		}
		joe_queue.push(null);
		fire_queue.push(null);
		int path = get_path();
		if(path==-1){
			cout << "IMPOSSIBLE" << endl;
		}
		else{
			cout << path+1 << endl;
		}
	}

	return 0;
}
