#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;
#define INF 1000000

int T, N, S;
//vector<vector<bool> > adj_mat(10005, vector<bool>(10005));
vector<vector<int> > adj_list(10005);
vector<bool> is_important(10005);
vector<bool> visited(10005);

int important_dist(int s){
    int radius = 0;
    int dist = 0;
    visited.clear();
    visited.resize(N+1, false);
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
            /*for(int i=1;i<=N;i++){
                if(!visited[i] && adj_mat[temp][i]){
                    bfs_queue.push(i);
                    visited[i] = true;
                }
            }*/
			for(int i=0;i<adj_list[temp].size();i++){
				if(!visited[adj_list[temp][i]]){
					bfs_queue.push(adj_list[temp][i]);
					visited[adj_list[temp][i]] = true;
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
		
		/*adj_mat.clear();
		adj_mat.resize(10005, vector<bool>(10005, false));*/
		for(int i=0;i<=N;i++){
			adj_list[i].clear();
		}
		vector<bool> station_seen(N+1, false);
		for(int i=0;i<S;i++){
			//vector<int> temp_line;
			int first_station,station;
			cin >> first_station;
			station = first_station;
			while(station){
				if(station_seen[station]){
					is_important[station] = true;
				}
				else{
					station_seen[station] = true;
				}
				//temp_line.push_back(station);
				cin >> station;
				if(station){
					/*adj_mat[temp_line[temp_line.size()-1]][station] = true;
					adj_mat[station][temp_line[temp_line.size()-1]] = true;*/
					adj_list[first_station].push_back(station);
					adj_list[station].push_back(first_station);
					first_station = station;
				}
			}
		}
		cout << "Krochanska is in: " << find_agent() << endl;
	}

	return 0;
}
