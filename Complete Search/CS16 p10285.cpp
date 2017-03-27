#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int R,C;
vector<vector<int> > height;
int max_slide;

int compute_slide(int row, int col, int prev_height){
	//Base case
	if(row>=R || col>=C || row <0 || col <0){
		return 0;
	}
	else if(height[row][col]>=prev_height){
		return 0;
	}
	//Main case
	else{
		int ret = 0;
		ret = max(ret,compute_slide(row-1,col,height[row][col]));
		ret = max(ret,compute_slide(row+1,col,height[row][col]));
		ret = max(ret,compute_slide(row,col-1,height[row][col]));
		ret = max(ret,compute_slide(row,col+1,height[row][col]));
		return ret+1;
	}
}

int main(){
	int T;
	string place;
	cin >> T;
	while(T--){
		cin >> place;
		cin >> R >> C;
		height.clear();
		height.resize(R, vector<int>(C));
		max_slide = 0;
		for(int i=0;i<R;i++){
			for(int j=0;j<C;j++){
				cin >> height[i][j];
			}
		}
		for(int i=0;i<R;i++){
			for(int j=0;j<C;j++){
				max_slide = max(max_slide,compute_slide(i,j,101));
			}
		}
		cout << place << ": " << max_slide << endl;
	}
	return 0;
}
