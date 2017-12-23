#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <queue>

using namespace std;

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
  while(cin >> input){
    //Special case
    if(!valid(input)){
      cout << "0" << endl;
      continue;
    }
    int nr_rank = 0;
    string temp = "";
    queue<string> bfs_queue;
    bfs_queue.push(temp);
    while(1){
        temp = bfs_queue.front();
        bfs_queue.pop();
        nr_rank++;
        if(temp == input){
            break;
        }
        if(temp == ""){
            for(char in = 'a'; in <='z'; in++){
                string input_temp;
                input_temp = string(1, in);
                bfs_queue.push(input_temp);
            }
        }
        else{
            char last = temp[temp.size()-1];
            for(char in = last+1; in<='z'; in++){
                string input_temp;
                input_temp = temp + string(1,in);
                bfs_queue.push(input_temp);
            }
        }
    }
    cout << nr_rank-1 << endl;
  }
  return 0;
}
