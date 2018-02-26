#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>
#include <functional>

using namespace std;

#define INF 1000000

int N,s,e;
vector<vector<int> > adj_mat;

vector<int> path;
int total_delay;

void compute(void){
	vector<int> parent(N+1);
	vector<int> dist(N+1);
	for(int i=1;i<=N;i++){
		parent[i] = i;
		dist[i] = INF;
	}
	dist[s] = 0;
	pair<int, int> q_elem(0, s);
	priority_queue<pair<int, int>, vector<pair<int,int> >, greater<pair<int, int> > > q;
	q.push(q_elem);
	while(!q.empty()){
		pair<int, int> temp = q.top();
		q.pop();
		if(temp.first == dist[temp.second]){
			for(int i=1;i<=N;i++){
				if(adj_mat[temp.second][i]!=-1){
					if(dist[i]>dist[temp.second]+adj_mat[temp.second][i]){
						dist[i] = dist[temp.second]+adj_mat[temp.second][i];
						q_elem.first = dist[i];
						q_elem.second = i;
						parent[i] = temp.second;
						q.push(q_elem);
					}
				}
			}
		}
	}
	path.clear();
	total_delay = 0;
	int node = e;
	while(parent[node]!=node){
		path.push_back(node);
		total_delay+=adj_mat[parent[node]][node];
		node = parent[node];
	}
	path.push_back(s);
	reverse(path.begin(), path.end());
}

int main(){
	int nr_connections,node,delay,nr_case=1;
	cin >> N;
	while(N){
		adj_mat.clear();
		adj_mat.resize(N+1, vector<int>(N+1, -1));
		for(int i=1;i<=N;i++){
			cin >> nr_connections;
			for(int j=0;j<nr_connections;j++){
				cin >> node >> delay;
				adj_mat[i][node] = delay;
			}
		}
		cin >> s >> e;
		compute();
		cout << "Case " << nr_case << ": Path = ";
		for(int i=0;i<path.size()-1;i++){
			cout << path[i] << " ";
		}
		cout << path[path.size()-1] << "; " << total_delay << " second delay" << endl;
		nr_case++;
		cin >> N;
	}
	return 0;
}
