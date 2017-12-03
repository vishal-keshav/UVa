#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

int nr_node;
vector<vector<int> > adj_mat;
vector<int> valid_node;
vector<char> topo_seq;
vector<int> indegree;
vector<string> input;

void topo_sort(void){
  if(nr_node==0){
    return;
  }
  else{
    for(int i=0;i<26;i++){
      if(valid_node[i]==1 && indegree[i]==0){
        valid_node[i] = 0;
        for(int j=0;j<26;j++){
          if(adj_mat[i][j]==1 && valid_node[j]==1){
            indegree[j]--;
          }
        }
        topo_seq.push_back((char)(i+'A'));
        nr_node--;
        topo_sort();
      }
    }
  }
}

void print_topo_order(void){
  for(vector<char>::iterator it = topo_seq.begin(); it!=topo_seq.end(); it++){
    cout << (*it);
  }
  cout << endl;
}

int main(){
  //freopen("output.txt","w",stdout);
  string line;
  input.clear();
  adj_mat.clear();
  adj_mat.resize(26, vector<int>(26,0));
  valid_node.clear();
  valid_node.resize(26,0);
  indegree.clear();
  indegree.resize(26,0);
  topo_seq.clear();
  while(getline(cin, line)){
    if(line[0]!='#'){
      input.push_back(line);
    }
    else{
      for(int i=1;i<input.size();i++){
        int len = min(input[i-1].size(),input[i].size());
        for(int j=0;j<len;j++){
          if(input[i-1][j]==input[i][j]){
            if(valid_node[input[i-1][j]-'A']==0){
              valid_node[input[i-1][j]-'A'] = 1;
              nr_node++;
            }
            if(valid_node[input[i][j]-'A']==0){
              valid_node[input[i][j]-'A'] = 1;
              nr_node++;
            }
            continue;
          }
          else{
            if(adj_mat[input[i-1][j]-'A'][input[i][j]-'A'] == 0){
              adj_mat[input[i-1][j]-'A'][input[i][j]-'A'] = 1;
              indegree[input[i][j]-'A']++;
            }
            if(valid_node[input[i-1][j]-'A']==0){
              valid_node[input[i-1][j]-'A'] = 1;
              nr_node++;
            }
            if(valid_node[input[i][j]-'A']==0){
              valid_node[input[i][j]-'A'] = 1;
              nr_node++;
            }
            break;
          }
        }
      }
      /*for(int i=0;i<26;i++){
        for(int j=0;j<26;j++){
          if(adj_mat[i][j]==1 && valid_node[i]==1 && valid_node[j]==1){
            cout << (char)(i+'A') << " -- " << (char)(j+'A') << endl;
          }
        }
      }
      cout << nr_node << endl;*/
      if(input.size()==1){//Special case, only one input
        cout << input[0][0] << endl;
      }
      else{
        topo_sort();
        print_topo_order();
      }
      input.clear();
      adj_mat.clear();
      adj_mat.resize(26, vector<int>(26,0));
      valid_node.clear();
      valid_node.resize(26,0);
      indegree.clear();
      indegree.resize(26,0);
      topo_seq.clear();
    }
  }
  return 0;
}
