#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <utility>
#include <string>
#include <map>
#include <queue>

using namespace std;

/*
Part 1: construct graph
Part 2: Apply MST on graph
*/

//#define DEBUG 1

/*Union find implemented*/
vector<int> union_set;
int nr_sets;
void init_uf(int n){
	union_set.clear();
	union_set.resize(n);
	for(int i=0;i<n;i++){
		union_set[i] = i;
	}
	nr_sets = n;
}

int find_head(int i){
	if(union_set[i]==i){
		return i;
	}
	else{
		union_set[i] = find_head(union_set[i]);
		return union_set[i];
	}
}

bool is_sameset(int i, int j){
	return (find_head(i)==find_head(j));
}

void make_union(int i, int j){
	if(!is_sameset(i,j)){
		nr_sets--;
	}
	union_set[find_head(i)] = find_head(j);
}

int move_x[4] = {0,-1,0,1};
int move_y[4] = {-1,0,1,0};

struct edge{
    pair<int, int> coord;
    int weight;
};
int N,x,y;
vector<string> maze;
vector<pair<int, int> > alien_loc; //This contains start also
pair<int, int> start;

int nr_node;
int nr_edges;
vector<struct edge> edges;

map<pair<int, int>, int> loc_map;

void bfs_graph(int node){
	vector<string> maze_copy = maze;
	queue<pair<int,int> > bfs_queue;
	pair<int,int> null;
	null.first = -1;
	null.second = -1;
	int dist = 1;
	maze_copy[alien_loc[node].first][alien_loc[node].second] = '#';
	bfs_queue.push(alien_loc[node]);
	bfs_queue.push(null);
	while(!bfs_queue.empty()){
		pair<int, int> temp = bfs_queue.front();
		bfs_queue.pop();
		if(temp.first == -1){
			if(bfs_queue.empty()){
				return;
			}
			bfs_queue.push(null);
			dist++;
		}
		else{
            //cout << maze_copy[temp.first][temp.second] << endl;

			pair<int, int> move_cell;
			for(int i=0;i<4;i++){
				move_cell.first = move_x[i] + temp.first;
				move_cell.second = move_y[i] + temp.second;
				if(maze_copy[move_cell.first][move_cell.second]!='#'){
					bfs_queue.push(move_cell);


                    if(maze_copy[move_cell.first][move_cell.second] == 'A' || maze_copy[move_cell.first][move_cell.second] == 'S'){
                        struct edge temp_edge;
                        temp_edge.coord.first = node;
                        temp_edge.coord.second = loc_map[move_cell];
                        temp_edge.weight = dist;
                        edges.push_back(temp_edge);
                    }

                    maze_copy[move_cell.first][move_cell.second] = '#';
				}
			}
		}
	}
}

int mst_weight(void){
	int ret = 0;
	init_uf(alien_loc.size());
	auto sort_func = [](struct edge e1, struct edge e2)->bool {
		return (e1.weight < e2.weight);
	};
	sort(edges.begin(), edges.end(), sort_func);
	for(int i=0;i<edges.size();i++){
		if(!is_sameset(edges[i].coord.first, edges[i].coord.second)){
			make_union(edges[i].coord.first, edges[i].coord.second);
			ret+=edges[i].weight;
		}
	}
	return ret;
}

int main(){
    //freopen("output.txt","w",stdout);
    string line;
    pair<int, int> temp;
	cin >> N;
	while(N--){
		cin >> x >> y;
		maze.clear();
		alien_loc.clear();
		edges.clear();
		cin.ignore();
		loc_map.clear();
		int index = 0;
		for(int i=0;i<y;i++){
			getline(cin, line);
			maze.push_back(line);
			for(int j=0;j<x;j++){
                if(maze[i][j]=='A'){
                    temp.first = i;
                    temp.second = j;
					loc_map[temp] = index;
					index++;
                    alien_loc.push_back(temp);
                }
                if(maze[i][j]=='S'){
                    start.first = i;
                    start.second = j;
					loc_map[start] = index;
					index++;
                    alien_loc.push_back(start);
                }
			}
		}
#ifdef DEBUG
        for(int i=0;i<y;i++){
            cout << maze[i] << endl;
        }
        for(int i=0;i<alien_loc.size();i++){
            cout << alien_loc[i].first << " " << alien_loc[i].second << " " <<loc_map[alien_loc[i]] << endl;
        }

#endif // DEBUG
        //Construct graph
		for(int i=0;i<alien_loc.size();i++){
			bfs_graph(i);
		}
		//bfs_graph(0);
#ifdef DEBUG
		for(int i=0;i<edges.size();i++){
			cout << edges[i].weight << " " << edges[i].coord.first << " " << edges[i].coord.second << endl;
		}
#endif
        //find mst
		cout << mst_weight() << endl;
	}
	return 0;
}
