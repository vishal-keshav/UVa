#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

int move_x[4] = {-1, 0, 1, 0};
int move_y[4] = {0, 1, 0, -1};

struct barrier{
  int x1,y1,x2,y2;
};
vector<struct barrier> b;

int R,C;
struct coord{
  int x, y;
};
struct coord start_loc, end_loc;
vector<vector<bool> > visited;
vector<vector<struct coord> > parent;

void visit(struct coord s){
  visited[s.x][s.y] = true;
}

bool valid(struct coord s){
  if(s.x>=0 && s.x<R && s.y>=0 && s.y<C && visited[s.x][s.y]==false){
    return true;
  }
  return false;
}

bool valid_move(struct coord s, struct coord e){
  for(int i=0;i<3;i++){
    if(b[i].x1 == b[i].x2){
      //vertical barrier
      if((s.y==(b[i].x1)-1 && e.y==(b[i].x1)) || (e.y==(b[i].x1)-1 && s.y==(b[i].x1))){
        if((s.x>=b[i].y1 && s.x<b[i].y2) || (s.x>=b[i].y2 && s.x<b[i].y1)){
          return false;
        }
      }
    }
    else{
      //horizontal barrier
      if((s.x==(b[i].y1)-1 && e.x==(b[i].y1)) || (e.x==(b[i].y1)-1 && s.x==(b[i].y1))){
        if((s.y>=b[i].x1 && s.y<b[i].x2) || (s.y>=b[i].x2 && s.y<b[i].x1)){
          return false;
        }
      }
    }
  }
  return true;
}

bool loc_is_end(struct coord s){
  if(s.x == end_loc.x && s.y == end_loc.y){
    return true;
  }
  return false;
}

vector<char> compute_path(void){
  visited[start_loc.x][start_loc.y] = true;
  queue<struct coord> bfs_queue;
  bfs_queue.push(start_loc);
  struct coord null;
  null.x = -1;
  bfs_queue.push(null);
  while(!bfs_queue.empty()){
    struct coord temp = bfs_queue.front();
    bfs_queue.pop();
    if(temp.x == -1){
      if(bfs_queue.empty()){
        break;
      }
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
            if(valid_move(temp, new_loc)){
              bfs_queue.push(new_loc);
              visited[new_loc.x][new_loc.y] = true;
              parent[new_loc.x][new_loc.y]  = temp;
            }
          }
        }
      }
    }
  }
  vector<char> res;
  struct coord temp = end_loc;
  while(!(parent[temp.x][temp.y].x == temp.x && parent[temp.x][temp.y].y == temp.y)){
    struct coord p = parent[temp.x][temp.y];
    if(p.x == temp.x){
      if(p.y>temp.y){
        res.push_back('W');
      }
      else{
        res.push_back('E');
      }
    }
    else{
      if(p.x>temp.x){
        res.push_back('N');
      }
      else{
        res.push_back('S');
      }
    }
    temp = p;
  }
  return res;
}

int main(){
  //freopen("output.txt","w",stdout);
  cin >> start_loc.x >> start_loc.y;
  while(start_loc.x + start_loc.y){
    cin >> end_loc.x >> end_loc.y;
    b.clear();
    struct barrier temp_b;
    for(int i=0;i<3;i++){
      cin >> temp_b.x1 >> temp_b.y1;
      cin >> temp_b.x2 >> temp_b.y2;
      b.push_back(temp_b);
    }
    visited.clear();
    visited.resize(6, vector<bool>(6, false));
    parent.clear();
    parent.resize(6, vector<struct coord>(6));
    for(int i=0;i<6;i++){
      for(int j=0;j<6;j++){
        parent[i][j].x = i;
        parent[i][j].y = j;
      }
    }

    vector<char> res = compute_path();
    reverse(res.begin(), res.end());
    for(int i=0;i<res.size();i++){
      cout << res[i];
    }
    cout << endl;
    cin >> start_loc.x >> start_loc.y;
  }
  return 0;
}
