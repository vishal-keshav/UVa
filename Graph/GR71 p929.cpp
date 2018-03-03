#include <iostream>
#include <stdio.h>
#include <vector>
#include <utility>
#include <algorithm>
#include <queue>

using namespace std;

#define INF 1000000
int T, N, M;
vector<vector<int> > grid;

int move_x[4] = {0, -1, 0, 1};
int move_y[4] = {-1, 0, 1, 0};

bool is_valid(int x, int y){
	if(x>=0 && x<N && y>=0 && y<M){
		return true;
	}
	return false;
}

int compute_dist(void){
	vector<vector<int> > dist(N, vector<int>(M,INF));
	dist[0][0] = grid[0][0];
	pair<int, pair<int, int>> q_elem(grid[0][0], pair<int, int>(0,0));
	priority_queue<pair<int, pair<int, int> >, vector<pair<int,pair<int, int> > >, greater<pair<int, pair<int, int> > > > q;
	q.push(q_elem);
	while(!q.empty()){
		pair<int, pair<int, int> > temp = q.top();
		q.pop();
		if(dist[temp.second.first][temp.second.second] == temp.first){
			for(int i=0;i<4;i++){
				int loc_x = temp.second.first + move_x[i];
				int loc_y = temp.second.second + move_y[i];
				if(is_valid(loc_x, loc_y) && dist[loc_x][loc_y] > temp.first + grid[loc_x][loc_y]){
					dist[loc_x][loc_y] = temp.first + grid[loc_x][loc_y];
					q_elem.second.first = loc_x;
					q_elem.second.second = loc_y;
					q_elem.first = dist[loc_x][loc_y];
					q.push(q_elem);
				}
			}
		}
	}
	return dist[N-1][M-1];
}

int main(){
	cin >> T;
	while(T--){
		cin >> N >> M;
		grid.clear();
		grid.resize(N, vector<int>(M));
		for(int i=0;i<N;i++){
			for(int j=0;j<M;j++){
				cin >> grid[i][j];
			}
		}
		cout << compute_dist() << endl;
	}
	return 0;
}
