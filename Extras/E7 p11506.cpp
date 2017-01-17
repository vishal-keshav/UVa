#include <iostream>
#include <algorithm>

using namespace std;

#define INT_MAX 10000000

#define DEBUG 1

int M,W;
int comp_cost[51];
int wire_cost[51][51];

bool max_flow_dfs(int source, int sink,int **graph, int **used, int V, bool *visited, int *maximum_flow, int *aug_path_min, int local_min){
    visited[source] = true;
	if(source == sink){
		*aug_path_min = local_min;
		*maximum_flow+= local_min;
		visited[source] = false;
		return true;
	}
	else{
		//iterate through positive neighbours
		//1. index is neighbour if connected node has residual_graph i.e. comp_cost[src][dest]>residual_graph[src][dest]
		//2. index is neighbour if reverse side can be used i.e. residual_graph[dest][src] > 0
		for(int i=0;i<V;i++){
			if(graph[source][i] > used[source][i] && !visited[i]){
				if(max_flow_dfs(i,sink,graph,used,V,visited,maximum_flow,aug_path_min,min(local_min,graph[source][i]-used[source][i]))){
					//we found M in this path
					used[source][i]+=*aug_path_min;
					visited[source] = false;
					return true;
				}
			}
			if(used[i][source]>0 && !visited[i]){
				if(max_flow_dfs(i,sink,graph,used,V,visited,maximum_flow,aug_path_min,min(local_min,used[i][source]))){
					//we found M in this path
					used[i][source]-= *aug_path_min;
					visited[source] = false;
					return true;
				}
			}
		}
		visited[source] = false;
		return false;
	}
}

/*Input parameters
1. Directed graph pointer as in adjancy matrix
2. Number of vertex (including src and dest)
3. source index (should not have incoming edges)
4. destination index (should not have outgoing edges)*/
int max_flow(int **graph, int n, int source, int sink){

	int aug_path_min=0, maximum_flow=0;
	bool *visited = new bool[n];
	int **used_flow = new int*[n];

	for(int i=0;i<n;i++){
		used_flow[i] = new int[n];
		visited[i] = false;
		for(int j=0;j<n;j++){
			used_flow[i][j] = 0;
		}
	}

	while(max_flow_dfs(source,sink,graph,used_flow,n,visited,&maximum_flow,&aug_path_min,INT_MAX)){

	}
	return maximum_flow;
}

#ifndef DEBUG
int min_cost(void){
    //Implementation goes here
}
#endif

int main(){
    int i,j,k;
	cin >> M >> W;
	while(M!=0){
#ifndef DEBUG
		for(int i=2;i<=M-1;i++){
			cin >> comp_cost[i];
		}
		for(int i = 0;i<W;i++){
			cin >> j >> k;
			cin >> wire_cost[j][k];
			wire_cost[k][j] = wire_cost[j][k];
		}
		cout << min_cost() << endl;
#endif

#ifdef DEBUG
		int **directed_graph = new int*[M+1];
		for(int i=0;i<=M;i++){
            directed_graph[i] = new int[M+1];
            for(int j=0;j<=M;j++){
                directed_graph[i][j] = 0;
            }
		}
		for(int index=0;index<W;index++){
            cin >> i >> j >> k;
            directed_graph[i][j] = k;
		}
		cout << max_flow(directed_graph,M,1,M) << endl;
#endif
		cin >> M >> W;
	}
	return(0);
}
