#include <iostream>
#include <stdio.h>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

int N, time_now;
vector<vector<int> > adj_mat;
vector<int> visited;
vector<int> parent;
vector<int> visit_seq;
vector<int> back_seq;

int nr_articulation(int node){
  visited[node] = 1;
  visit_seq[node] = time_now;
  back_seq[node] = time_now;
  int nr_child = 0;
  int ret = 0;
  int articulation = 0;
  for(int i=1;i<=N;i++){
    if(adj_mat[node][i]==1 && node!=i){
      if(visited[i]==1){
        if(parent[node]!=i){
          back_seq[node] = min(back_seq[node], visit_seq[i]);
        }
      }
      else{
        parent[i] = node;
        nr_child++;
        time_now++;
        ret+= nr_articulation(i);
        back_seq[node] = min(back_seq[node], back_seq[i]);
        if(visit_seq[node] <= back_seq[i] && parent[node]!=node){
          articulation = 1;
        }
      }
    }
  }
  if(nr_child>1 && !articulation && parent[node]==node){
    articulation = 1;
  }
  if(articulation==1){
    ret++;
  }
  return ret;
}

int main(){
  string line;
  int node1, node2;
  cin >> N;
  while(N){
    cin.ignore();
    adj_mat.clear();
    adj_mat.resize(N+1, vector<int>(N+1, 0));
    visited.clear();
    visited.resize(N+1, 0);
    parent.clear();
    parent.resize(N+1, 0);
    visit_seq.clear();
    visit_seq.resize(N+1,0);
    back_seq.clear();
    back_seq.resize(N+1,0);
    for(int i=1;i<=N;i++){
      parent[i] = i;
    }
    while(1){
      getline(cin, line);
      stringstream ss(line);
      ss >> node1;
      if(node1==0){
        break;
      }
      while(ss >> node2){
        adj_mat[node1][node2] = 1;
        adj_mat[node2][node1] = 1;
      }
    }
    time_now = 0;
    cout << nr_articulation(1) << endl;
    cin >> N;
  }
  return 0;
}
