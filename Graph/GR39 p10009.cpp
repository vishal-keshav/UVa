#include <iostream>
#include <stdio.h>
#include <vector>
#include <map>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

int nr_city;
vector<string> city_name;
vector<vector<int> > graph;

vector<int> compute_path(int s, int e){
	vector<int> ret;
	bool found = false;
	vector<int> visited(nr_city,0);
	vector<int> parent(nr_city);
	for(int i=0;i<nr_city;i++){
		parent[i] = i;
	}
	queue<int> bfs_queue;
	bfs_queue.push(s);
	visited[s] = 1;
	while(!bfs_queue.empty()){
		int temp = bfs_queue.front();
		bfs_queue.pop();
		if(temp == e){
			found = true;
			break;
		}
		else{
			for(int i=0;i<graph[temp].size();i++){
				if(visited[graph[temp][i]]==0){
					bfs_queue.push(graph[temp][i]);
					visited[graph[temp][i]] = 1;
					parent[graph[temp][i]] = temp;
				}
			}
		}
	}
	if(found){
		int node = e;
		ret.clear();
		while(node!=s){
			ret.push_back(node);
			node = parent[node];
		}
		ret.push_back(s);
		reverse(ret.begin(), ret.end());
	}
	return ret;
}

int main(){
    //freopen("output.txt","w",stdout);
	int T,E,Q;
	string start_city, end_city;
	cin >> T;
	while(T--){
		cin >> E >> Q;
        nr_city = 0;
        city_name.clear();
        graph.clear();
        map<string, int> city_map;
        for(int i=0;i<E;i++){
            cin >> start_city >> end_city;
            if(city_map.find(start_city) == city_map.end()){
                city_map[start_city] = nr_city;
                nr_city++;
                city_name.push_back(start_city);
                vector<int> city_vector;
                graph.push_back(city_vector);
            }
            if(city_map.find(end_city) == city_map.end()){
                city_map[end_city] = nr_city;
                nr_city++;
                city_name.push_back(end_city);
                vector<int> city_vector;
                graph.push_back(city_vector);
            }
            graph[city_map[start_city]].push_back(city_map[end_city]);
            graph[city_map[end_city]].push_back(city_map[start_city]);
        }
        for(int i=0;i<Q;i++){
            cin >> start_city >> end_city;
            vector<int> path;
            path = compute_path(city_map[start_city], city_map[end_city]);
            for(int i=0;i<path.size();i++){
                cout << city_name[path[i]][0];
            }
            cout << endl;
        }
        if(T!=0){
            cout << endl;
        }
	}
	return 0;
}
