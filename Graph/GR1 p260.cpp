#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

#define BLACK 1
#define WHITE 2

int N;
vector<vector<char> > input;
vector<vector<int> > graph;
int n_x[6] = {-1, -1, 0, 0, 1, 1};
int n_y[6] = {-1, 0, -1, 1, 0, 1};

bool is_valid(int x, int y){
	if(x>=0 && y>=0 && x<N && y<N){
		return true;
	}
	return false;
}

void flood_fill(int row, int col, char color){
	if(!is_valid(row,col)){
		return;
	}
	if(input[row][col]!=color){
		return;
	}
	if(graph[row][col]==-1){
		graph[row][col] = (color=='w'? WHITE:BLACK);
		//Iterate for each neighbour
		for(int i=0;i<6;i++){
			flood_fill(row+n_x[i],col+n_y[i],color);
		}
	}
	return;
}

int main(){

	int nr_case = 1;
	bool ret;
	cin >> N;

	while(N){
		input.clear();
		input.resize(N,vector<char>(N));
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				cin >> input[i][j];
			}
		}
		//Initialize graph
		graph.clear();
		graph.resize(N,vector<int>(N,-1));
		//Flood fill for white first (racist)
		for(int i=0;i<N;i++){
			flood_fill(i,0,'w');
		}
		//Check if white has succeeded
		ret = false;
		for(int i=0;i<N;i++){
			if(graph[i][N-1]==WHITE){
				ret = true;
				break;
			}
		}
		if(ret){
			cout  << nr_case << " W" << endl;
		}
		else{
			cout << nr_case << " B" << endl;
		}
		cin >> N;
		nr_case++;
	}

	return 0;
}
