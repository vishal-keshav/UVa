#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

int C,L;
int S,E,D;
vector<vector<int> > link;

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
	
	
	return 0;
}