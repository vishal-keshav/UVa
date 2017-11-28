#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

int n,m,l;
vector<vector<int> > depend;
vector<int> fall;

int dominoes(int node){
  if(fall[node]==1){
    return 0;
  }
  int ret = 1;
  fall[node] = 1;
  for(int i=0;i<n;i++){
    if(node!=i && fall[i]==0 && depend[node][i]==1){
      ret+=dominoes(i);
    }
  }
  return ret;
}

int main(){
  //freopen("output.txt","w",stdout);
  int T;
  int total_fall, x,y,k;
  cin >> T;
  while(T--){
    cin >> n >> m >> l;
    depend.clear();
    depend.resize(n, vector<int>(n,0));
    fall.clear();
    fall.resize(n,0);
    for(int i=0;i<m;i++){
      cin >> x >> y;
      depend[x-1][y-1] = 1;
    }
    total_fall = 0;
    for(int i=0;i<l;i++){
      cin >> k;
      total_fall+=dominoes(k-1);
    }
    cout << total_fall << endl;
  }
  return 0;
}
