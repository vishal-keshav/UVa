#include <iostream>
#include <stdio.h>
#include <vector>
#include <math.h>

using namespace std;

struct outpost{
	int x, y;
};

struct outpost camps[501];

bool visited[501];
int S,P;
int temp_D;

void init_graph(void){
	for(int i=0;i<P;i++){
		visited[i] = false;
	}
}

int dist(int n1, int n2){
	return sqrt(pow(camps[n1].x-camps[n2].x,2)+pow(camps[n1].y-camps[n2].y,2));
}

void visit_dfs_way(int node){
	//Iterate through all unvisited node, visit it
	for(int i=0;i<P;i++){
		if(i!=node && !visited[i]){
			if(dist(node,i) <= D_temp){
				visited[i] = true;
				visit_dfs_way(i);
			}
		}
	}
}

int nr_sub_graphs(void){
	int sub_graph = 0;
	for(int i=0;i<P;i++){
		if(!visited[i]){
			visit_dfs_way(i);
			sub_graph++;
		}
	}
	return sub_graph;
}

int main(){
	
	return 0;
}