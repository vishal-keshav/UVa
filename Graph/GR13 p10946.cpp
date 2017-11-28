#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <algorithm>

using namespace std;
int N, M;
vector<string> area;

struct dict{
  char letter;
  int occurance;
};

vector<struct dict> arr_hash;

bool sort_func(struct dict a, struct dict b){
  if(a.occurance > b.occurance){
    return true;
  }
  else if(a.occurance == b.occurance){
    return (a.letter < b.letter);
  }
  else{
    return false;
  }
}

int move_x[4] = {-1, 0, 0, 1};
int move_y[4] = {0, -1, 1, 0};

bool valid(int x, int y){
  if(x>=0 && x<N && y>=0 && y<M){
    return true;
  }
  return false;
}

int flood_fill(int x, int y, char l){
  if(!valid(x,y) || area[x][y]!=l){
    return 0;
  }
  else{
    int ret = 1;
    area[x][y] = '.';
    for(int i=0;i<4;i++){
      ret+= flood_fill(x+move_x[i], y+move_y[i], l);
    }
    return ret;
  }
}

void print_hash(void){
  for(vector<struct dict>::iterator it = arr_hash.begin();it!=arr_hash.end(); it++){
    cout << (*it).letter << " " << (*it).occurance << endl;
  }
}

int main(){
  //freopen("output.txt","w",stdout);
  int case_nr=1;
  string line;
  cin >> N >> M;
  while(N+M){
    area.clear();
    for(int i=0;i<N;i++){
      cin >> line;
      area.push_back(line);
    }
    arr_hash.clear();
    for(int i=0;i<N;i++){
      for(int j=0;j<M;j++){
        if(area[i][j]!='.'){
          struct dict tmp;
          tmp.letter = area[i][j];
          tmp.occurance = flood_fill(i,j,area[i][j]);
          arr_hash.push_back(tmp);
        }
      }
    }
    sort(arr_hash.begin(), arr_hash.end(), sort_func);
    cout << "Problem " << case_nr << ":" << endl;
    print_hash();
    case_nr++;
    cin >> N >> M;
  }
  return 0;
}
