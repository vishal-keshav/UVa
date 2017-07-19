#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

#define INT_MAXIMUM 1000000

//#define DEBUG 1

using namespace std;

int N,nr,node;
vector<vector<bool> > graph;
vector<vector<int> > DP;
void remove_back(int node){
	for(int i=1;i<=N;i++){
		if(graph[node][i]){
			graph[i][node] = false;
			remove_back(i);
		}
	}
	return;
}

int install(int node, int is_fill){
	if(DP[node][is_fill]!=INT_MAXIMUM){
		return DP[node][is_fill];
	}
	else{
		int ret;
		if(is_fill==0){
			ret = 0;
			for(int i=1;i<=N;i++){
				if(graph[node][i]){
					ret+=(install(i,1));
				}
			}
			DP[node][is_fill] = ret;
			return ret;
		}
		else{
			ret = 1;
			for(int i=1;i<=N;i++){
				if(graph[node][i]){
					ret+=min(install(i,0),install(i,1));
				}
			}
			DP[node][is_fill] = ret;
			return ret;
		}
	}
}

#ifdef DEBUG
void print_graph(int node){
	cout << node << " ";
	for(int i=1;i<=N;i++){
		if(graph[node][i]){
			print_graph(i);
		}
	}
}
#endif

int main(){
    //freopen("output.txt","w",stdout);
	cin >> N;
	while(N){
		graph.clear();
		graph.resize(N+1,vector<bool>(N+1,false));
		for(int i=1;i<=N;i++){
			cin >> nr;
			for(int j=0;j<nr;j++){
				cin >> node;
				graph[i][node] = true;
				graph[node][i] = true;
			}
		}
		//Remove back pointer using recursion
		remove_back(1);
		//Apply DP on each node, starting from root node 1
		DP.clear();
		DP.resize(N+1,vector<int>(2,INT_MAXIMUM));
		int ret;
		ret = min(install(1,0),install(1,1));
#ifdef DEBUG
		print_graph(1);
		cout << endl;
		for(int i=1;i<=N;i++){
            cout << i << " " << DP[i][0] << DP[i][1] << endl;
		}
#endif
        if(N==1){
            cout << "1" << endl;
        }
        else{
            cout << ret << endl;
        }
        cin >> N;
	}

	return 0;
}
