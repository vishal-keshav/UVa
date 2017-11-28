#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>
#include <sstream>

using namespace std;
vector<vector<int> > board;
vector<int> nr_board;
int N;

int move_x[4] = {-1, 0, 0, 1};
int move_y[4] = {0, -1, 1, 0};

bool valid(int x, int y){
  if(x>=0 && x<N && y>=0 && y<N){
    return true;
  }
  return false;
}

void flood_fill(int x, int y, int n){
  if(!valid(x,y) || board[x][y]!=n){
    return;
  }
  else{
    board[x][y] = 0;
    for(int i=0;i<4;i++){
      flood_fill(x+move_x[i], y+move_y[i], n);
    }
    return;
  }
}

int main(){
  //freopen("output.txt","w",stdout);
  string line;
  int x,y, nr_sets;
  bool break_case;
  cin >> N;
  while(N){
    cin.ignore();
    board.clear();
    board.resize(N, vector<int>(N, N));
    nr_board.clear();
    nr_board.resize(N,0);
    break_case = false;
    for(int i=1;i<N;i++){
      getline(cin, line);
      stringstream ss(line);
      nr_sets = 0;
      while(ss >> x){
        ss >> y;
        if(board[x-1][y-1]!=i){
          board[x-1][y-1] = i;
          nr_sets++;
        }
      }
      if(nr_sets!=N){
        break_case = true;
      }
    }
    if(!break_case){
      for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
          if(board[i][j]){
            nr_board[board[i][j]-1]++;
            if(nr_board[board[i][j]-1]>1){
              break_case = true;
              break;
            }
            flood_fill(i,j, board[i][j]);
          }
        }
        if(break_case){
          break;
        }
      }
    }

    if(break_case){
      cout << "wrong" << endl;
    }
    else{
      cout << "good" << endl;
    }
    cin >> N;
  }
  return 0;
}
