#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int T, M, N;
vector<vector<char> > chess;
//vector<vector<bool> > visited;
struct loc{
  int x,y;
};
struct loc start_loc, end_loc;

int move_x[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int move_y[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
int hmove_x[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
int hmove_y[8] = {1, 2, 2, 1, -1, -2, -2, -1};


bool valid(struct loc l){
  if(l.x>=0 && l.x<M && l.y>=0 && l.y<N){
    return true;
  }
  return false;
}

bool no_enemy(struct loc l){
  if(chess[l.x][l.y]!='Z'){
    return true;
  }
  return false;
}

bool reached(struct loc l){
  if(l.x == end_loc.x && l.y == end_loc.y){
    return true;
  }
  return false;
}

int compute_length(void){
  int ret = 0;
  struct loc null;
  null.x = -1;
  queue<struct loc> bfs_queue;
  bfs_queue.push(start_loc);
  bfs_queue.push(null);
  chess[start_loc.x][start_loc.y] = 'Z';
  while(!bfs_queue.empty()){
    struct loc temp = bfs_queue.front();
    bfs_queue.pop();
    if(temp.x == -1){
      if(bfs_queue.empty()){
        ret = -1;
        break;
      }
      ret++;
      bfs_queue.push(null);
    }
    else{
      if(reached(temp)){
        break;
      }
      else{
        struct loc new_loc;
        for(int i=0;i<8;i++){
          new_loc.x = temp.x + move_x[i];
          new_loc.y = temp.y + move_y[i];
          if(valid(new_loc) && no_enemy(new_loc)){
            bfs_queue.push(new_loc);
            chess[new_loc.x][new_loc.y] = 'Z';
          }
        }
      }
    }
  }
  return ret;
}

int main(){
  //freopen("output.txt","w",stdout);
  cin >> T;
  while(T--){
    cin >> M >> N;
    chess.clear();
    chess.resize(M, vector<char>(N));
    //visited.clear();
    //visited.resize(M, vector<bool>(N,false));
    char temp;
    for(int i=0;i<M;i++){
      for(int j=0;j<N;j++){
        cin >> temp;
        if(temp=='A'){
          chess[i][j] = temp;
          start_loc.x = i;
          start_loc.y = j;
        }
        if(temp=='B'){
          chess[i][j] = temp;
          end_loc.x = i;
          end_loc.y = j;
        }
        if(temp=='Z'){
          chess[i][j] = 'Z';
          for(int k=0;k<8;k++){
            struct loc horse;
            horse.x = i + hmove_x[k];
            horse.y = j + hmove_y[k];
            if(valid(horse)){
              if(chess[horse.x][horse.y] == 'A' || chess[horse.x][horse.y] == 'B'){
                continue;
              }
              else{
                chess[horse.x][horse.y] = 'Z';
              }
            }
          }
        }
        if(temp == '.' && chess[i][j]!='Z'){
          chess[i][j] = temp;
        }
      }
    }
    /*for(int i=0;i<M;i++){
      for(int j=0;j<N;j++){
        cout << chess[i][j];
      }
      cout << endl;
    }*/
    int L = compute_length();
    if(L>=0){
      cout << "Minimal possible length of a trip is " << L << endl;
    }
    else{
      cout << "King Peter, you can't go now!" << endl;
    }
  }

  return 0;
}
