#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

int C,S,E,T;
vector<vector<int> > profit;
vector<int> end_point;
vector<vector<int> > DP;

int main(){
	cin >> C >> S >> E >> T;
	while(C+S+E+T){
		profit.clear();
		profit.resize(C,vector<int>(C,0));
		for(int i=0;i<C;i++){
			for(int j=0;j<C;j++){
				cin >> profit[i][j];
			}
		}
		end_point.clear();
		end_point.resize(E);
		for(int i=0;i<E;i++){
			cin >> end_point[i];
			end_point[i]--;
		}
		DP.clear();
		DP.resize(C,vector<int>(T+1,-1));
		DP[S-1][0] = 0;
		for(int i=1;i<=T;i++){
			for(int j=0;j<C;j++){
                for(int k=0;k<C;k++){
                    if(j!=k && DP[j][i-1]!=-1){
                        DP[k][i] = max(DP[k][i],DP[j][i-1]+profit[j][k]);
                    }
                }
			}
		}
		int ret = 0;
		for(int i=0;i<E;i++){
			ret = max(ret,DP[end_point[i]][T]);
		}
		cout << ret << endl;
		cin >> C >> S >> E >> T;
	}
	return 0;
}