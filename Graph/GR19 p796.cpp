#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;
int N, time_now;
vector<vector<int> > adj_mat;
vector<int> visited;
vector<int> parent;
vector<int> visit_seq;
vector<int> back_seq;

int articulation_bridge(int node){
  int ret = 0;
  visited[node] = 1;
  visit_seq[node] = time_now;
  back_seq[node] = time_now;
  for(int i=0;i<N;i++){
    if(adj_mat[node][i]==1 && i!=node && parent[node]!=i){
      if(visited[i]==1){
        back_seq[node] = min(back_seq[node], visit_seq[i]);
      }
      else{
        parent[i] = node;
        time_now++;
        ret+=articulation_bridge(i);
        back_seq[node] = min(back_seq[node], back_seq[i]);
        if(visit_seq[node] < back_seq[i]){
          adj_mat[node][i] = 2;
          adj_mat[i][node] = 2;
          ret++;
        }
      }
    }
  }
  return ret;
}

void print_bridge(void){
  for(int i=0;i<N;i++){
    for(int j=0;j<N;j++){
      if(adj_mat[i][j] == 2){
        cout << i << " - " << j << endl;
        adj_mat[j][i] = 0;
      }
    }
  }
  return;
}

int main(){
  //freopen("output.txt","w",stdout);
  int node1, node2, nr_connection, nr_critical;
  while(cin >> N){
    adj_mat.clear();
    adj_mat.resize(N,vector<int>(N,0));
    visited.clear();
    visited.resize(N,0);
    parent.clear();
    parent.resize(N);
    for(int i=0;i<N;i++){
      parent[i] = i;
    }
    visit_seq.clear();
    visit_seq.resize(N);
    back_seq.clear();
    back_seq.resize(N);

    for(int i=0;i<N;i++){
      scanf("%d (%d)", &node1, &nr_connection);
      //cout << node1 << " " << nr_connection << " ";
      for(int j=0;j<nr_connection; j++){
        scanf("%d", &node2);
        //cout << node2 << " ";
        adj_mat[node1][node2] = 1;
        adj_mat[node2][node1] = 1;
      }
      //cout << endl;
    }
    time_now = 0;
    nr_critical = 0;
    for(int i=0;i<N;i++){
      if(visited[i]==0){
        nr_critical+= articulation_bridge(i);
      }
    }
    cout << nr_critical << " critical links" << endl;
    print_bridge();
    cout << endl;
  }
  return 0;
}
