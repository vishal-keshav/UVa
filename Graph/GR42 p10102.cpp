#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

int M;
int **grid;
int move_x[4] = {0, 0, -1, 1};
int move_y[4] = {-1, 1, 0, 0};


bool is_null(pair<int, int> p){
	if(p.first==-1 && p.second==-1){
		return true;
	}
	return false;
}

bool is_valid(pair<int, int> p){
	if(p.first >=0 && p.first<M && p.second>=0 && p.second<M){
		return true;
	}
	return false;
}

int compute(pair<int, int> s){
	int ret = 0;
	vector<vector<bool> > visited(M, vector<bool>(M, false));
	queue<pair<int, int> > bfs_queue;
	pair<int, int> null(-1, -1);
	bfs_queue.push(s);
	bfs_queue.push(null);
	visited[s.first][s.second] = true;
	while(!bfs_queue.empty()){
		pair<int, int> temp = bfs_queue.front();
		bfs_queue.pop();
		if(is_null(temp)){
			if(bfs_queue.empty()){
				ret = -1;
				break;
			}
			ret++;
			bfs_queue.push(null);
		}
		else{
			if(grid[temp.first][temp.second] == 3){
				break;
			}
			else{
				for(int i=0;i<4;i++){
					pair<int, int> elem;
					elem.first = temp.first + move_x[i];
					elem.second = temp.second + move_y[i];
					if(is_valid(elem) && !visited[elem.first][elem.second]){
						bfs_queue.push(elem);
						visited[elem.first][elem.second] = true;
					}
				}
			}
		}
	}
	return ret;
}

int main(){
    //freopen("output.txt","w",stdout);
	string line;
	int ans;
	while(cin >> M){
		grid = new int*[M];
		for(int i=0; i<M;i++){
			grid[i] = new int[M];
			cin >> line;
			for(int j=0; j<M; j++){
				grid[i][j] = line[j]-'0';
			}
		}
		ans = -1;
		for(int i=0; i<M;i++){
			for(int j=0; j<M; j++){
				if(grid[i][j] == 1){
					pair<int, int> s(i,j);
					ans = max(ans, compute(s));
				}
			}
		}
		cout << ans << endl;
	}
	return 0;
}
