#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<bool> > graph;
vector<bool> visited;
int T,N;

void dfs(int node){
	visited[node] = true;
	for(int i=0;i<N;i++){
		if(!visited[i] && graph[node][i]){
			dfs(i);
		}
	}
	return;
}

int main(){
	char max_char;
	string edge;
	cin >> T;
	cin.ignore();
	while(T--){

        cin >> max_char;
        N = (max_char-'A') + 1;
        cin.ignore();
		graph.clear();
		graph.resize(N,vector<bool>(N,false));
		while(1){
		    getline(cin,edge);
			if(edge.length()==2){
				graph[edge[0]-'A'][edge[1]-'A'] = true;
				graph[edge[1]-'A'][edge[0]-'A'] = true;
			}
			else{
				break;
			}
		}
		visited.clear();
		visited.resize(N,false);
		int ret = 0;
		for(int i=0;i<N;i++){
			if(!visited[i]){
				ret++;
				dfs(i);
			}
		}
		cout << ret << endl;
		if(T){
            cout << endl;
		}
	}
	return 0;
}
