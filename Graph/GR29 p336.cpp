#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>

using namespace std;

int E, nr_node;
vector<vector<int> > adj_list;
map<int, int> node_map;
map<int, int> dist_map;
queue<int> bfs_queue;

int bfs(int node, int ttl){
    dist_map.clear();
	int ret = 1;
	bfs_queue.push(node);
	dist_map[node] = 0;
	while(!bfs_queue.empty()){
		int v = bfs_queue.front();
		bfs_queue.pop();
		if(dist_map[v]==ttl){
			while(!bfs_queue.empty()){
				bfs_queue.pop();
			}
			break;
		}
		for(int i=0;i<adj_list[v].size();i++){
			if(dist_map.find(adj_list[v][i])==dist_map.end()){
				dist_map[adj_list[v][i]] = dist_map[v] + 1;
				bfs_queue.push(adj_list[v][i]);
				ret++;
			}
		}
	}
	return (nr_node - ret);
}

int main(){
  //freopen("output.txt","w",stdout);
  int node1, node2;
  int node, ttl;
  int nr_case=1;
  cin >> E;
  while(E){
    adj_list.clear();
    node_map.clear();
    nr_node = 0;
    for(int i=0;i<E;i++){
      cin >> node1 >> node2;
      if(node_map.find(node1) == node_map.end()){
        vector<int> temp;
        adj_list.push_back(temp);
        node_map[node1] = nr_node;
        nr_node++;
      }
      if(node_map.find(node2) == node_map.end()){
        vector<int> temp;
        adj_list.push_back(temp);
        node_map[node2] = nr_node;
        nr_node++;
      }
      adj_list[node_map[node1]].push_back(node_map[node2]);
      adj_list[node_map[node2]].push_back(node_map[node1]);
    }
    cin >> node >> ttl;
    while(node+ttl){
      cout << "Case " << nr_case << ": " << bfs(node_map[node], ttl) <<\
      " nodes not reachable from node " << node << " with TTL = " << ttl << "." << endl;
      cin >> node >> ttl;
      nr_case++;
    }
    cin >> E;
  }

  return 0;
}
