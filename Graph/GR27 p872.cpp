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
        string_stack.push_back((char)(i+'A'));
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
  if(topo_orders.size()==0){
    cout << "NO" << endl;
    return;
  }
  for(vector<string>::iterator it=topo_orders.begin(); it!=topo_orders.end();it++){
    int len = (*it).size();
    for(int i=0;i<len-1;i++){
      cout << (*it)[i] << " ";
    }
    cout << (*it)[len-1] << endl;
  }
}

int main(){
  //freopen("output.txt","w",stdout);
  int T;
  cin >> T;
  string line, depends;
  char node1, node2;
  bool temp = false;
  cin.ignore();
  while(T--){
    if(temp){
      cout << endl;
    }
    else{
      temp = true;
    }
    cin.ignore();
    getline(cin, line);
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
      valid_node[node1-'A'] = 1;
      nr_nodes++;
    }
    for(int i=0;i<depends.size();i+=4){
      if(adj_mat[depends[i]-'A'][depends[i+2]-'A'] == 0){
        adj_mat[depends[i]-'A'][depends[i+2]-'A'] = 1;
        indegree[depends[i+2]-'A']++;
      }

    }

    /*for(int i=0;i<26;i++){
      for(int j=0;j<26;j++){
        if(adj_mat[i][j]==1){
          cout << (char)(i+'A') << " -- " << (char)(j+'A') << endl;
        }
      }
    }*/

    topo_recursive_order();
    print_topo_order();
  }
  return 0;
}
