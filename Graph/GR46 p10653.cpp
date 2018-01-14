#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

int move_x[4] = {-1, 0, 1, 0};
int move_y[4] = {0, 1, 0, -1};

int R,C;
struct coord{
  int x, y;
};
struct coord start_loc, end_loc;
vector<vector<int> > grid;

void visit(struct coord s){
  grid[s.x][s.y] = 1;
}

bool valid(struct coord s){
  if(s.x>=0 && s.x<R && s.y>=0 && s.y<C && grid[s.x][s.y]==0){
    return true;
  }
  return false;
}

bool loc_is_end(struct coord s){
  if(s.x == end_loc.x && s.y == end_loc.y){
    return true;
  }
  return false;
}

int compute_time(void){
  int ret = 0;
  struct coord null;
  null.x = -1;
  queue<struct coord> bfs_queue;
  bfs_queue.push(start_loc);
  visit(start_loc);
  bfs_queue.push(null);
  while(!bfs_queue.empty()){
    struct coord temp = bfs_queue.front();
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
      if(loc_is_end(temp)){
        break;
      }
      else{
        struct coord new_loc;
        for(int i=0;i<4;i++){
          new_loc.x = temp.x + move_x[i];
          new_loc.y = temp.y + move_y[i];
          if(valid(new_loc)){
            bfs_queue.push(new_loc);
            visit(new_loc);
          }
        }
      }
    }
  }
  return ret;
}

int main(){
  //freopen("output.txt","w",stdout);
  int r, row, col, nr_bomb;
  cin >> R >> C;
  while(R+C){
    grid.clear();
    grid.resize(R, vector<int>(C, 0));
    cin >> r;
    for(int i=0;i<r;i++){
      cin >> row >> nr_bomb;
      for(int j=0;j<nr_bomb;j++){
        cin >> col;
        grid[row][col] = 1;
      }
    }
    cin >> start_loc.x >> start_loc.y >> end_loc.x >> end_loc.y;
    cout << compute_time() << endl;

    cin >> R >> C;
  }

  return 0;
}
