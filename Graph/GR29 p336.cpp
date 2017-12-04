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
queue<int> bfs_queue;

int bfs(int node, int ttl){
  vector<int> visited(nr_node,0);
  int nr_node_reachable = 1;
  bfs_queue.push(-1);
  bfs_queue.push(node);
  visited[node] = 1;
  while(!bfs_queue.empty() && ttl!=0){
    int n = bfs_queue.front();
    bfs_queue.pop();
    if(n==-1){
      ttl--;
      bfs_queue.push(-1);
      continue;
    }
    for(vector<int>::iterator it = adj_list[n].begin(); it!=adj_list[n].end();it++){
      if(visited[(*it)]==0){
        bfs_queue.push((*it));
        nr_node_reachable++;
        visited[(*it)] = 1;
      }

    }
  }
  return nr_node_reachable;
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
      cout << "Case " << nr_case << ": " << (nr_node-bfs(node_map[node], ttl+1)) <<\
      " nodes not reachable from node " << node << " with TTL = " << ttl << "." << endl;
      cin >> node >> ttl;
      nr_case++;
      while(!bfs_queue.empty()){
        bfs_queue.pop();
      }
    }
    cin >> E;
  }

  return 0;
}
