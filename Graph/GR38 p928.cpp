#include <iostream>
#include <stdio.h>
#include <queue>
#include <algorithm>

using namespace std;

int R, C;
int move_x[3][4] = {{0, -1, 0, 1}, {0, -2, 0, 2}, {0, -3, 0, 3}};
int move_y[3][4] = {{-1, 0, 1, 0}, {-2, 0, 2, 0}, {-3, 0, 3, 0}};

struct loc{
  int x,y;
};
struct loc start_loc;
struct loc end_loc;
char** mapp;
bool **visited[3];

bool loc_is_null(struct loc location){
  if(location.x == -1 && location.y == -1){
    return true;
  }
  return false;
}

bool loc_is_valid(struct loc old_loc, struct loc new_loc){
  if(new_loc.x >=0 && new_loc.x < R && new_loc.y>=0 && new_loc.y< C){
    if(old_loc.y == new_loc.y){
      int min_x = min(old_loc.x, new_loc.x);
      int max_x = max(old_loc.x, new_loc.x);
      for(int i=min_x;i<=max_x;i++){
        if(mapp[i][old_loc.y] == '#' && i!=old_loc.x){
          return false;
        }
      }
    }
    else{
      int min_y = min(old_loc.y, new_loc.y);
      int max_y = max(old_loc.y, new_loc.y);
      for(int i=min_y;i<=max_y;i++){
        if(mapp[old_loc.x][i] == '#' && i!=old_loc.y){
          return false;
        }
      }
    }
  }
  else{
    return false;
  }
  return true;
}

bool loc_is_end(struct loc l, struct loc e){
  if(l.x == e.x && l.y == e.y){
    return true;
  }
  return false;
}

int compute_steps(void){
  int nr_moves = 0;
  int move_index = 0;
  queue<struct loc> bfs_queue;
  struct loc null_loc;
  null_loc.x = -1;
  null_loc.y = -1;
  bfs_queue.push(start_loc);
  bfs_queue.push(null_loc);
  while(!bfs_queue.empty()){
    struct loc temp = bfs_queue.front();
    bfs_queue.pop();
    if(loc_is_null(temp)){
      if(bfs_queue.empty()){
        nr_moves = -1;
        break;
      }
      move_index = (move_index+1)%3;
      nr_moves++;
      bfs_queue.push(null_loc);
    }
    else{
      if(loc_is_end(temp, end_loc)){
        break;
      }
      else{
        for(int i=0;i<4;i++){
          struct loc new_loc;
          new_loc.x = temp.x + move_x[move_index][i];
          new_loc.y = temp.y + move_y[move_index][i];
          if(loc_is_valid(temp, new_loc) && !visited[move_index][new_loc.x][new_loc.y]){
            bfs_queue.push(new_loc);
            visited[move_index][new_loc.x][new_loc.y] = true;
          }
        }
      }
    }
  }
  return nr_moves;
}

int main(){
  //freopen("output.txt","w",stdout);
  char status;
  int T;
  cin >> T;
  while(T--){
    cin >> R >> C;
    mapp = new char*[R];
    for(int v = 0; v<3;v++){
        visited[v] = new bool*[R];
    }
    for(int i=0;i<R;i++){
        mapp[i] = new char[C];
        for(int v = 0; v<3; v++){
           visited[v][i] = new bool[C];
        }
        for(int j=0;j<C;j++){
          for(int u = 0; u<3;u++){
            visited[u][i][j] = false;
          }
          cin >> status;
          mapp[i][j] = status;
          if(status == 'S'){
              start_loc.x = i;
              start_loc.y = j;
              visited[2][i][j] = true;
          }
          if(status == 'E'){
              end_loc.x = i;
              end_loc.y = j;
          }
        }
    }
    /*for(int i=0; i<R;i++){
      for(int j=0;j<C;j++){
        cout << mapp[i][j] << " ";
      }
      cout << endl;
    }
    cout << start_loc.x << " " << start_loc.y << " " << end_loc.x << " " << end_loc.y << endl;*/

    int steps = compute_steps();
    if(steps == -1){
      cout << "NO" << endl;
    }
    else{
      cout << steps << endl;
    }
  }
  return 0;
}
