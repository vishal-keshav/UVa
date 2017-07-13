#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

int C,L;
int S,E,D;
vector<vector<int> > link;
vector<vector<bool> > DP;

int main(){
	int c1, c2;
	cin >> C >> L;
	link.clear();
	link.resize(C,vector<int>(C,0));
	for(int i=0;i<L;i++){
		cin >> c1 >> c2;
		link[c1-1][c2-1] = 1;
		link[c2-1][c1-1] = 1;
	}
	cin >> S >> E >> D;
	DP.clear();
	DP.resize(C,vector<bool>(D+1,false));
	DP[S-1][0] = true;
	for(int i=1;i<=D;i++){
		for(int j=0;j<C;j++){
			
		}
	}
	
	return 0;
}