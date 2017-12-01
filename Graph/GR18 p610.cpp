#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;
int n,m, time_now;
vector<vector<int> > adj_mat;
vector<int> visited;
vector<int> parent;
vector<int> visit_seq;
vector<int> back_seq;

void articulation_bridge(int node){
  visited[node] = 1;
  visit_seq[node] = time_now;
  back_seq[node] = time_now;
  for(int i=1;i<=n;i++){
    if(adj_mat[node][i]==1 && i!=node && parent[node]!=i){
      if(visited[i]==1){
        back_seq[node] = min(back_seq[node], visit_seq[i]);
      }
      else{
        parent[i] = node;
        time_now++;
        articulation_bridge(i);
        back_seq[node] = min(back_seq[node], back_seq[i]);
        if(visit_seq[node] < back_seq[i]){
          adj_mat[node][i] = 2;
          adj_mat[i][node] = 2;
        }
      }
    }
  }
  return;
}

void print_bridge(int node){
  if(visited[node]==1){
    return;
  }
  visited[node] = 1;
  for(int i=1;i<=n;i++){
    if(adj_mat[node][i]==1){
      adj_mat[i][node] = 0;
      cout << node << " " << i << endl;
      print_bridge(i);
    }
    else if(adj_mat[node][i]==2){
      cout << node << " " << i << endl;
      print_bridge(i);
    }
  }
  return;
}

int main(){
  int nr_case, node1, node2;
  cin >> n >> m;
  nr_case = 1;
  while(n+m){
    adj_mat.clear();
    adj_mat.resize(n+1, vector<int>(n+1,0));
    visited.clear();
    visited.resize(n+1,0);
    parent.clear();
    parent.resize(n+1);
    for(int i=1;i<=n;i++){
      parent[i] = i;
    }
    visit_seq.clear();
    visit_seq.resize(n+1);
    back_seq.clear();
    back_seq.resize(n+1);
    time_now = 0;
    for(int i=0;i<m;i++){
      cin >> node1 >> node2;
      adj_mat[node1][node2] = 1;
      adj_mat[node2][node1] = 1;
    }
    articulation_bridge(1);
    for(int i=1;i<=n;i++){
      visited[i] = 0;
    }
    cout << nr_case << endl << endl;
    print_bridge(1);
    cout << "#" << endl;
    cin >> n >> m;
    nr_case++;
  }
  return 0;
}
