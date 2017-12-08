#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>

using namespace std;
vector<vector<int> > memo;
void init(void){
  memo.clear();
  memo.resize(5,vector<int>(26,0));
  for(int i=0;i<26;i++){
    memo[0][i] = 1;
  }
  for(int i=1;i<5;i++){
    for(int j=0;j<26;j++){
      for(int k=j+1;k<26;k++){
        memo[i][j]+=memo[i-1][k];
      }
    }
  }
}

bool valid(string s){
  int len = s.size();
  for(int i=1;i<len;i++){
    if(s[i-1]>=s[i]){
      return false;
    }
  }
  return true;
}
int main(){
  //freopen("output.txt","w",stdout);
  string input;
  int total;
  init();
  while(cin >> input){
    //Special case
    if(!valid(input)){
      cout << "0" << endl;
      continue;
    }
    if(input.size()==1){
      cout << (int)(input[0]-'a' + 1) << endl;
    }
    else{
      total = 0;
      for(int i=0;i<input.size()-1;i++){
        for(int j=0;j<26;j++){
          total+=memo[i][j];
        }
      }
      int last_to_last = (int)(input[input.size()-2]-'a');
      int last = (int)(input[input.size()-1]-'a');
      int level = input.size()-1;
      //cout << last_to_last << " " << last << " " << level << endl;
      for(int i=0;i<last_to_last;i++){
        total+=memo[level][i];
      }
      total+=last-last_to_last;
      cout << total << endl;
    }
  }
  return 0;
}
