#include <iostream>
#include <algorithm>

using namespace std;

#define INT_MAX 10000000

/*int M,W;
int comp_cost[51];
int wire_cost[51][51];

int used[51][51];*/

int M=6;
int comp_cost[7][7] = { {0, 0, 0, 0, 0, 0, 0},
						{0, 0, 16, 13, 0, 0, 0},
                        {0, 0, 0, 10, 12, 0, 0},
                        {0, 0, 4, 0, 0, 14, 0},
                        {0, 0, 0, 9, 0, 0, 20},
                        {0, 0, 0, 0, 7, 0, 4},
                        {0, 0, 0, 0, 0, 0, 0}
                      };

int used[7][7] = { {0, 0, 0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0}
                      };

int min_f = INT_MAX;
int maximum_flow = 0;

bool visited[7] = {false,false,false,false,false,false,false};

bool dfs(int src, int local_min){
    visited[src] = true;
	if(src == M){
		min_f = local_min;
		maximum_flow+= min_f;
		visited[src] = false;
		return true;
	}
	else{
		//iterate through positive neighbours
		//1. index is neighbour if connected node has residual_graph i.e. comp_cost[src][dest]>residual_graph[src][dest]
		//2. index is neighbour if reverse side can be used i.e. residual_graph[dest][src] > 0
		for(int i=1;i<=M;i++){
			if(comp_cost[src][i] > used[src][i] && !visited[i]){
				if(dfs(i,min(local_min,comp_cost[src][i]-used[src][i]))){
					//we found M in this path
					used[src][i]+=min_f;
					visited[src] = false;
					return true;
				}
			}
			if(used[i][src]>0 && !visited[i]){
				if(dfs(i,min(local_min,used[i][src]))){
					//we found M in this path
					used[i][src]-=min_f;
					visited[src] = false;
					return true;
				}
			}
		}
		visited[src] = false;
		return false;
	}
}

int max_flow(){
	//Works on directed graph
	//Assuming sarting is 1 and ending is M
	maximum_flow = 0;
	while(dfs(1,INT_MAX)){
		//cout << "Starting" << endl;
	}
	return maximum_flow;
}

/*int min_cost(void){

}*/

int main(){
	/*cin >> M >> W;
	while(M!=0){
		for(int i=2;i<=M-1;i++){
			cin >> comp_cost[i];
		}
		for(int i = 0;i<W;i++){
			cin >> j >> k;
			cin >> wire_cost[j][k];
			wire_cost[k][j] = wire_cost[j][k];
		}
		cout << min_cost() << endl;
		cin >> M >> N;
	}*/
	cout << max_flow() << endl;
	return(0);
}
