#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

//#define DEBUG 1
#define INF 10000000

int T, N, S;
vector<vector<int> > line;
vector<vector<bool> > adj_mat;
vector<bool> is_important;

void create_graph(void){
	for(int nr_line = 0; nr_line<S; nr_line++){
		for(int i=1;i<line[nr_line].size();i++){
			adj_mat[line[nr_line][i-1]][line[nr_line][i]] = true;
			adj_mat[line[nr_line][i]][line[nr_line][i-1]] = true;
		}
	}
	return;
}

int important_dist(int s){
    int radius = 0;
    int dist = 0;
    vector<bool> visited(N+1, false);
    queue<int> bfs_queue;
    bfs_queue.push(s);
    bfs_queue.push(-1);
    visited[s] = true;
    while(!bfs_queue.empty()){
        int temp = bfs_queue.front();
        bfs_queue.pop();
        if(temp == -1){
            if(bfs_queue.empty()){
                break;
            }
            bfs_queue.push(-1);
            radius++;
        }
        else{
            if(is_important[temp]){
                dist+=radius;
            }
            for(int i=1;i<=N;i++){
                if(!visited[i] && adj_mat[temp][i]){
                    bfs_queue.push(i);
                    visited[i] = true;
                }
            }
        }
    }
    return dist;
}

int find_agent(void){
	int min_dist = INF;
	int min_station;
	for(int i=1;i<=N;i++){
        if(is_important[i]){
            int total_dist = important_dist(i);
            if(total_dist<min_dist){
                min_dist = total_dist;
                min_station = i;
            }
        }
	}
	return min_station;
}

int main(){
	cin >> T;
	while(T--){
		cin >> N >> S;
		is_important.clear();
		is_important.resize(N+1, false);
		adj_mat.clear();
		adj_mat.resize(N+1, vector<bool>(N+1, false));
		line.clear();
		vector<bool> station_seen(N+1, false);
		for(int i=0;i<S;i++){
			vector<int> temp_line;
			int station;
			cin >> station;
			while(station){
				if(station_seen[station]){
					is_important[station] = true;
				}
				else{
					station_seen[station] = true;
				}
				temp_line.push_back(station);
				cin >> station;
			}
			line.push_back(temp_line);
		}
		create_graph();
#ifdef DEBUG
		for(int i=1;i<=N;i++){
			if(is_important[i]){
				cout << i << " ";
			}
		}
		cout << endl;
		for(int i=1;i<=N;i++){
			cout << i << ":";
			for(int j=1;j<=N;j++){
				if(adj_mat[i][j]){
					cout << j << " ";
				}
			}
			cout << endl;
		}
#endif
		cout << "Krochanska is in: " << find_agent() << endl;
	}

	return 0;
}
