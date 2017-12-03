#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int n,m;
vector<vector<int> > adj_mat;
vector<int> visited;
vector<int> task_seq;

void topo_sort(int node){
  visited[node] = 1;
  for(int i=0;i<n;i++){
    if(i!=node && adj_mat[node][i]==1 && visited[i]==0){
      topo_sort(i);
    }
  }
  task_seq.push_back(node+1);
}

void print_seq(void){
  reverse(task_seq.begin(), task_seq.end());
  for(vector<int>::iterator it=task_seq.begin(); it!=task_seq.end();it++){
    if((it+1)!=task_seq.end()){
      cout << (*it) << " ";
    }
    else{
      cout << (*it) << endl;
    }
  }
}

int main(){
  //freopen("output.txt","w",stdout);
  int node1, node2;
  cin >> n >> m;
  while(n+m){
    adj_mat.clear();
    adj_mat.resize(n, vector<int>(n,0));
    visited.clear();
    visited.resize(n,0);
    task_seq.clear();
    for(int i=0;i<m;i++){
      cin >> node1 >> node2;
      adj_mat[node1-1][node2-1] = 1;
    }
    for(int i=0;i<n;i++){
      if(visited[i]==0){
        topo_sort(i);
      }
    }
    print_seq();
    cin >> n >> m;
  }
  return 0;
}
