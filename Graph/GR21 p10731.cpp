#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

#define INT_MAXIMUM 100000

int N, time_now, scc_nr;
vector<vector<int> > adj_mat;
vector<int> visited;
vector<int> visit_seq;
vector<int> back_seq;
vector<int> valid_vertex;
vector<vector<char> > ssc_meta;
stack<int> node_stack;

void tarzan_scc(int node){
  visited[node] = 1;
  visit_seq[node] = time_now;
  back_seq[node] = time_now;
  node_stack.push(node);
  for(int i=0;i<26;i++){
    if(adj_mat[node][i]==1 && node!=i){
      if(visited[i]==1){
        back_seq[node] = min(back_seq[node], back_seq[i]);//But why
      }
      else{
        time_now++;
        tarzan_scc(i);
        back_seq[node] = min(back_seq[node], back_seq[i]);
      }
    }
  }
  if(visit_seq[node]==back_seq[node]){
    vector<char> ssc_vec;
    while(1){
      if(node_stack.top()==node){
        ssc_vec.push_back((char)(node+'A'));
        node_stack.pop();
        back_seq[node] = INT_MAXIMUM;
        break;
      }
      else{
        ssc_vec.push_back((char)(node_stack.top()+'A'));
        back_seq[node_stack.top()] = INT_MAXIMUM;
        node_stack.pop();
      }
    }
    ssc_meta.push_back(ssc_vec);
  }
}

bool sort_func(vector<char> a, vector<char> b){
  if(a[0]<b[0]){
    return true;
  }
  return false;
}

void sort_function(){
  for(vector<vector<char> >::iterator it=ssc_meta.begin();it!=ssc_meta.end();it++){
    sort((*it).begin(), (*it).end());
  }
  sort(ssc_meta.begin(), ssc_meta.end(), sort_func);
}

void print_ssc_meta(){
  sort_function();
  for(vector<vector<char> >::iterator it=ssc_meta.begin();it!=ssc_meta.end();it++){
    for(vector<char>::iterator iit = (*it).begin(); iit!=(*it).end(); iit++){
      cout << (*iit);
      if((iit+1)!=(*it).end()){
        cout << " ";
      }
    }
    cout << endl;
  }
}

int main(){
  //freopen("output.txt","w",stdout);
  char input[6];
  cin >> N;
  while(N){
    adj_mat.clear();
    adj_mat.resize(26, vector<int>(26,0));
    valid_vertex.clear();
    valid_vertex.resize(26,0);
    visited.clear();
    visited.resize(26, 0);
    for(int i=0;i<N;i++){
      for(int j=0;j<6;j++){
        cin >> input[j];
        valid_vertex[input[j]-'A'] = 1;
      }
      //Build edges
      for(int j=0;j<5;j++){
        adj_mat[input[5]-'A'][input[j]-'A'] = 1;
      }
    }
    visit_seq.clear();
    visit_seq.resize(26);
    back_seq.clear();
    back_seq.resize(26);
    time_now = 0;
    scc_nr = 0;
    ssc_meta.clear();
    //node_stack.clear();
    for(int i=0;i<26;i++){
      if(valid_vertex[i]==1 && visited[i]==0){
        tarzan_scc(i);
      }
    }
    print_ssc_meta();

    cin >> N;
    if(N){
      cout << endl;
    }
  }
  return 0;
}
