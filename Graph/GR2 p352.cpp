#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
using namespace std;

int N;
vector<string> image;
int n_x[8] = {-1,-1,-1,0,0,1,1,1};
int n_y[8] = {-1,0,1,-1,1,-1,0,1};
vector<vector<int> > graph;

bool is_valid(int x, int y){
	if(x>=0 && y>=0 && x<N && y<N){
		return true;
	}
	return false;
}

bool flood_fill(int row, int col){
	if(!is_valid(row,col)){
		return false;
	}
	if(image[row][col]=='0'){
		return false;
	}
	if(graph[row][col]!=-1){
		return false;
	}
	//Iterate to every neighbour and flood_fill
	bool temp;
	graph[row][col] = 1;
	for(int i=0;i<8;i++){
		temp = flood_fill(row+n_x[i], col+n_y[i]);
	}
	return true;
}

int main(){
	int nr_case = 1;
	int nr_war;
	while(cin >> N){
		image.clear();
		image.resize(N);
		for(int i=0;i<N;i++){
			cin >> image[i];
		}
		graph.clear();
		graph.resize(N,vector<int>(N,-1));
		nr_war = 0;
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				if(flood_fill(i,j)){
					nr_war++;
				}
			}
		}
        cout << "Image number " << nr_case << " contains " << nr_war << " war eagles." << endl;
		nr_case++;
	}
	return 0;
}
