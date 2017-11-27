#include <iostream>
#include <stdio.h>

using namespace std;

char board[9][9];
int move_x[4] = {-1, 0, 0, 1};
int move_y[4] = {0, -1, 1, 0};

bool valid(int x, int y){
  if(x>=0 && x<9 && y>=0 && y<9){
    return true;
  }
  return false;
}

int flood_fill(int x, int y, int *b, int *w){
  if(!valid(x,y)){
    return 0;
  }
  if(board[x][y]=='V'){
    return 0;
  }
  if(board[x][y]=='O'){
    *w = 1;
    return 0;
  }
  if(board[x][y]=='X'){
    *b = 1;
    return 0;
  }
  int ret = 0;
  if(board[x][y]=='.'){
    board[x][y] = 'V';
    for(int i=0;i<4;i++){
      ret+=flood_fill(x+move_x[i], y+move_y[i], b, w);
    }
  }
  return (ret+1);
}

int main(){
  //freopen("output.txt","w",stdout);
  int T;
  cin >> T;
  while(T--){
    for(int i=0;i<9;i++){
      for(int j=0;j<9;j++){
        cin >> board[i][j];
      }
    }
    int white_points = 0;
    int black_points = 0;
    int points = 0;
    for(int i=0;i<9;i++){
      for(int j=0;j<9;j++){
        if(board[i][j]=='O'){
          white_points++;
        }
        else if(board[i][j]=='X'){
          black_points++;
        }
        else{
          if(board[i][j]=='V'){
            continue;
          }
          int black = 0;
          int white = 0;
          points = flood_fill(i,j, &black, &white);
          if(black == 1 && white == 0){
            black_points+=points;
          }
          else if(black == 0 && white == 1){
            white_points+=points;
          }
          else{
            //Do nothing
          }
        }
      }
    }
    cout << "Black " << black_points << " White " << white_points << endl;
  }
}
