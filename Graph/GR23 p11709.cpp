#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <stack>
#include <map>
#include <string>

using namespace std;

int n,m, time_now, ssc_group_nr;
vector<vector<int> > adj_mat;
vector<int> visited;
vector<int> visit_seq;
vector<int> back_seq;
stack<int> node_stack;
map<string, int> name_map;

void tarzan_ssc(int node){
  visited[node] = 1;
  visit_seq[node] = time_now;
  back_seq[node] = time_now;
  node_stack.push(node);
  for(int i=0;i<n;i++){
    if(adj_mat[node][i] == 1 && i!=node){
      if(visited[i]==1){
        back_seq[node] = min(back_seq[node], back_seq[i]);
      }
      else{
        time_now++;
        tarzan_ssc(i);
        back_seq[node] = min(back_seq[node], back_seq[i]);
      }
    }
  }
  if(visit_seq[node]==back_seq[node]){
    while(1){
      if(node_stack.top()==node){
        back_seq[node] = n+1;
        node_stack.pop();
        break;
      }
      else{
        back_seq[node_stack.top()] = n+1;
        node_stack.pop();
      }
    }
    ssc_group_nr++;
  }
}

int main(){
  //freopen("output.txt","w",stdout);
  string first_name, surname, name1, name2;
  int node_nr;
  cin >> n >> m;
  while(n+m){
    name_map.clear();
    node_nr = 0;
    for(int i=0;i<n;i++){
      cin >> first_name >> surname;
      name1 = first_name + surname;
      name_map[name1] = node_nr;
      node_nr++;
    }
    adj_mat.clear();
    adj_mat.resize(n,vector<int>(n,0));
    visited.clear();
    visited.resize(n,0);

    for(int i=1;i<=m;i++){
      cin >> first_name >> surname;
      name1 = first_name + surname;
      cin >> first_name >> surname;
      name2 = first_name + surname;
      adj_mat[name_map[name1]][name_map[name2]] = 1;
      //adj_list[node1-1].push_back(node2-1);
    }
    time_now = 0;
    ssc_group_nr = 0;
    visit_seq.clear();
    visit_seq.resize(n);
    back_seq.clear();
    back_seq.resize(n);

    for(int i=0;i<n;i++){
      if(visited[i]==0){
        tarzan_ssc(i);
      }
    }
    cout << ssc_group_nr << endl;
    cin >> n >> m;
  }
  return 0;
}
