#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

int m,n;
vector<string> plot;
string line;

int move_x[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int move_y[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

bool is_valid(int x, int y){
	if(x>=0 && y>=0 && x<m && y<n){
		return true;
	}
	return false;
}

bool is_oil(int x, int y){
	if(!is_valid(x,y)){
		return false;
	}
	if(plot[x][y]=='*'){
		return false;
	}
	bool temp;
	plot[x][y] = '*';
	for(int i=0;i<8;i++){
		temp = is_oil(x+move_x[i], y+move_y[i]);
	}
	return true;
}

int main(){
	int res;
	cin >> m >> n;
	while(m+n){
		res = 0;
		plot.clear();
		for(int i=0;i<m;i++){
			cin >> line;
			plot.push_back(line);
		}
		for(int i=0;i<m;i++){
			for(int j=0;j<n;j++){
				if(is_oil(i,j)){
					res++;
				}
			}
		}
		cout << res << endl;
		cin >> m >> n;
	}
	
	
	return 0;
}