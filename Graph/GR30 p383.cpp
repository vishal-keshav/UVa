#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <sstream>

using namespace std;

int T, M, N, P;
vector<vector<int> > adj_list;
map<string, int> node_map;

int bfs_shipment_cost(int src, int dest){
  int leg = -1;
  bool reached = false;
  vector<int> visited(M,0);
  queue<int> bfs_queue;
  bfs_queue.push(-1);
  bfs_queue.push(src);
  visited[src] = 1;
  while(!bfs_queue.empty()){
    int node = bfs_queue.front();
    bfs_queue.pop();
    if(node == -1){
      leg++;
      if(bfs_queue.empty()){
        break;
      }
      bfs_queue.push(-1);
    }
    else if(node == dest){
      reached = true;
      break;
    }
    else{
      for(int i=0;i<adj_list[node].size();i++){
        if(visited[adj_list[node][i]] == 0){
          bfs_queue.push(adj_list[node][i]);
          visited[adj_list[node][i]] = 1;
        }
      }
    }
  }
  if(reached){
    return leg;
  }
  else{
    return -1;
  }
}

int main(){
  //freopen("output.txt","w",stdout);
  int nr_case = 1, size, cost;
  string node1, node2, nodes;
  char c1,c2;
  cin >> T;
  cout << "SHIPPING ROUTES OUTPUT" << endl << endl;
  while(T--){
    cin >> M >> N >> P;
    node_map.clear();
    for(int i=0;i<M;i++){
      cin >> c1 >> c2;
      node1 = string() + c1 + c2;
      node_map[node1] = i;
    }
    adj_list.clear();
    adj_list.resize(M);
    for(int i=0; i<N;i++){
      cin >> c1 >> c2;
      node1 = string() + c1 + c2;
      cin >> c1 >> c2;
      node2 = string() + c1 + c2;
      adj_list[node_map[node1]].push_back(node_map[node2]);
      adj_list[node_map[node2]].push_back(node_map[node1]);
    }
    cout << "DATA SET  " << nr_case << endl << endl;
    for(int i=0;i<P;i++){
      cin >> size >> c1 >> c2;
      node1 = string() + c1 + c2;
      cin >> c1 >> c2;
      node2 = string() + c1 + c2;
      cost = bfs_shipment_cost(node_map[node1], node_map[node2]);
      if(cost == -1){
        cout << "NO SHIPMENT POSSIBLE" << endl;
      }
      else{
        cout << "$" << cost*100*size << endl;
      }
    }
    cout << endl;
    nr_case++;
  }
  cout << "END OF OUTPUT" << endl;
  return 0;
}
