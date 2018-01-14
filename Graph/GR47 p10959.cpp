#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

#define INF 10000000

int P,C;
vector<vector<int> > graph;
vector<int> dist;

void compute_distance(void){
  int distance = 1;
  dist[0] = 0;
  queue<int> bfs_queue;
  bfs_queue.push(0);
  bfs_queue.push(-1);
  while(!bfs_queue.empty()){
    int temp = bfs_queue.front();
    bfs_queue.pop();
    if(temp == -1){
      if(bfs_queue.empty()){
        break;
      }
      bfs_queue.push(-1);
      distance++;
    }
    else{
      for(int i=0;i<P;i++){
        if(graph[temp][i] == 1 && dist[i]==INF){
          bfs_queue.push(i);
          dist[i] = min(dist[i], distance);
        }
      }
    }
  }
}

int main(){
  //freopen("output.txt","w",stdout);
  int T,c1,c2;
  cin >> T;
  while(T--){
    cin >> P >> C;
    graph.clear();
    graph.resize(P, vector<int>(P,0));
    dist.clear();
    dist.resize(P);
    for(int i=1;i<P;i++){
      dist[i] = INF;
    }
    for(int i=0;i<C;i++){
      cin >> c1 >> c2;
      graph[c1][c2] = 1;
      graph[c2][c1] = 1;
    }
    compute_distance();
    for(int i=1;i<P;i++){
      cout << dist[i] << endl;
    }
    if(T){
      cout << endl;
    }

  }

  return 0;
}
