#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;
int N;
vector<vector<int> > graph;
vector<int> visited;

int find_nr_dependancy(int node){
  if(visited[node]==1){
    return 0;
  }
  visited[node] = 1;
  int nr_depends = 0;
  for(int i=0;i<N;i++){
    if(i!=node && graph[node][i]==1 && visited[i]==0){
      nr_depends+=1 + find_nr_dependancy(i);
    }
  }
  return nr_depends;
}

void unvisit(int node){
  if(visited[node]==1){
    visited[node] = 0;
    for(int i=0;i<N;i++){
      if(graph[node][i]==1){
        unvisit(i);
      }
    }
  }
}
int main(){
  //freopen("output.txt","w",stdout);
  int nr_depend, depend;
  int max_depend, depend_node, nr_depends;
  cin >> N;
  while(N){
    graph.clear();
    graph.resize(N, vector<int>(N,0));
    visited.clear();
    visited.resize(N,0);
    for(int i=0; i<N; i++){
      cin >> nr_depend;
      for(int j=0;j<nr_depend;j++){
        cin >> depend;
        graph[i][depend-1] = 1;
      }
    }
    max_depend = -1;
    for(int i=N-1;i>=0;i--){
      nr_depends = find_nr_dependancy(i);
      unvisit(i);
      if(max_depend <= nr_depends){
        max_depend = nr_depends;
        depend_node = i+1;
      }
    }
    cout << depend_node << endl;
    cin >> N;
  }
  return 0;
}
