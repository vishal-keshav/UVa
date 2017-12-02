#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <stack>

using namespace std;
int N,n,m, time_now, ssc_group_nr;
vector<vector<int> > adj_list;
vector<int> visited;
vector<int> visit_seq;
vector<int> back_seq;
vector<int> ssc_group;
stack<int> node_stack;

vector<int> ssc_indegree;

void tarzan_ssc(int node){
  visited[node] = 1;
  visit_seq[node] = time_now;
  back_seq[node] = time_now;
  node_stack.push(node);
  for(int i=0;i<adj_list[node].size();i++){
    if(adj_list[node][i]!=node){
      if(visited[adj_list[node][i]]==1){
        back_seq[node] = min(back_seq[node], back_seq[adj_list[node][i]]);
      }
      else{
        time_now++;
        tarzan_ssc(adj_list[node][i]);
        back_seq[node] = min(back_seq[node], back_seq[adj_list[node][i]]);
      }
    }
  }
  if(visit_seq[node]==back_seq[node]){
    while(1){
      if(node_stack.top()==node){
        ssc_group[node] = ssc_group_nr;
        back_seq[node] = n+1;
        node_stack.pop();
        break;
      }
      else{
        ssc_group[node_stack.top()] = ssc_group_nr;
        back_seq[node_stack.top()] = n+1;
        node_stack.pop();
      }
    }
    ssc_group_nr++;
  }
}

int ssc_with_zero_indegree(void){
  int ret=0;
  ssc_indegree.clear();
  ssc_indegree.resize(ssc_group_nr,0);
  for(int i=0;i<n;i++){
    for(int j=0;j<adj_list[i].size();j++){
      if(adj_list[i][j]!=i){
        if(ssc_group[i]!=ssc_group[adj_list[i][j]]){
          ssc_indegree[ssc_group[adj_list[i][j]]]++;
        }
      }
    }
  }
  for(int i=0;i<ssc_group_nr;i++){
    if(ssc_indegree[i]==0){
      ret++;
    }
  }
  return ret;
}

int main(){
  //freopen("output.txt","w",stdout);
  int node1, node2;
  cin >> N;
  while(N--){
    cin >> n >> m;
    adj_list.clear();
    adj_list.resize(n);
    visited.clear();
    visited.resize(n,0);

    for(int i=1;i<=m;i++){
      cin >> node1 >> node2;
      //adj_mat[node1-1][node2-1] = 1;
      adj_list[node1-1].push_back(node2-1);
    }
    time_now = 0;
    ssc_group_nr = 0;
    ssc_group.clear();
    ssc_group.resize(n);
    visit_seq.clear();
    visit_seq.resize(n);
    back_seq.clear();
    back_seq.resize(n);

    for(int i=0;i<n;i++){
      if(visited[i]==0){
        tarzan_ssc(i);
      }
    }
    cout << ssc_with_zero_indegree() << endl;
  }
  return 0;
}
