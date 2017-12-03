#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

int nr_nodes;
vector<vector<int> > adj_mat;
vector<int> valid_node;
vector<char> string_stack;
vector<string> topo_orders;
vector<int> indegree;

void topo_recursive_order(void){
  if(nr_nodes==0){
    //Dump the characters to string
    string str(string_stack.begin(), string_stack.end());
    topo_orders.push_back(str);
  }
  else{
    for(int i=0;i<26;i++){
      if(valid_node[i]==1 && indegree[i]==0){
        string_stack.push_back((char)(i+'a'));
        valid_node[i] = 0;
        for(int j=0;j<26;j++){
          if(j!=i && adj_mat[i][j]==1){
            indegree[j]--;
          }
        }
        nr_nodes--;
        topo_recursive_order();
        //Revert all the thigs we did for a different sequence
        nr_nodes++;
        for(int j=0;j<26;j++){
          if(j!=i && adj_mat[i][j]==1){
            indegree[j]++;
          }
        }
        valid_node[i] = 1;
        string_stack.pop_back();
      }
    }
  }
}

void print_topo_order(){
  for(vector<string>::iterator it=topo_orders.begin(); it!=topo_orders.end();it++){
    cout << (*it) << endl;
  }
}

int main(){
  //freopen("output.txt","w",stdout);
  string line, depends;
  char node1, node2;
  bool temp = false;
  while(getline(cin, line)){
    if(temp){
      cout << endl;
    }
    else{
      temp = true;
    }
    getline(cin, depends);
    topo_orders.clear();
    adj_mat.clear();
    adj_mat.resize(26,vector<int>(26,0));
    valid_node.clear();
    valid_node.resize(26,0);
    indegree.clear();
    indegree.resize(26,0);
    nr_nodes = 0;
    stringstream ss(line);
    while(ss >> node1){
      valid_node[node1-'a'] = 1;
      nr_nodes++;
    }
    stringstream sss(depends);
    while(sss >> node1){
      sss >> node2;
      adj_mat[node1-'a'][node2-'a'] = 1;
      indegree[node2-'a']++;
    }
/*
#ifdef DEBUG
    for(int i=0;i<26;i++){
      for(int j=0;j<26;j++){
        if(adj_mat[i][j]==1){
          cout << (char)(i+'a') << " -- " << (char)(j+'a') << endl;
        }
      }
    }
#endif
*/
    topo_recursive_order();
    print_topo_order();
  }
  return 0;
}
