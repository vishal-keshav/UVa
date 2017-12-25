#include <iostream>
#include <stdio.h>
#include <queue>
#include <vector>

using namespace std;

int N;
int max_bloom, max_bloom_day;
vector<vector<int> > graph;

bool compute_maxbloom(int s){
  if(graph[s].size()==0){
    return false;
  }
  int temp_bloom=0;
  int day=0;
  vector<bool> visited(N,0);
  queue<int> bfs_queue;
  visited[s] = true;
  bfs_queue.push(s);
  bfs_queue.push(-1);
  while(!bfs_queue.empty()){
    int temp = bfs_queue.front();
    bfs_queue.pop();
    if(temp == -1){
      day++;
      if(bfs_queue.empty()){
        break;
      }
      if(temp_bloom>max_bloom){
        max_bloom = temp_bloom;
        max_bloom_day = day;
      }
      temp_bloom = 0;
      bfs_queue.push(-1);
    }
    else{
      for(int i=0;i<graph[temp].size();i++){
        if(!visited[graph[temp][i]]){
          bfs_queue.push(graph[temp][i]);
          visited[graph[temp][i]] = true;
          temp_bloom++;
        }
      }
    }
  }
  return true;
}

int main(){
  //freopen("output.txt","w",stdout);
  int M, f, source;
  cin >> N;
  graph.clear();
  graph.resize(N);
  for(int i=0;i<N;i++){
    cin >> M;
    for(int j=0;j<M;j++){
      cin >> f;
      graph[i].push_back(f);
    }
  }
  cin >> M;
  while(M--){
    max_bloom = -1;
    cin >> source;
    if(!compute_maxbloom(source)){
      cout << 0 << endl;
    }
    else{
      cout << max_bloom << " " << max_bloom_day << endl;
    }
  }
  return 0;
}
