#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

int N,nr,node;
vector<vector<bool> > graph;

int main(){
	cin >> N;
	while(N){
		graph.clear();
		graph.resize(N+1,vector<int>(N+1,false));
		for(int i=1;i<=N;i++){
			cin >> nr;
			for(int j=0;j<nr;j++){
				cin >> node;
				graph[i][node] = true;
				graph[node][i] = true;
			}
		}
		
		cin >> N;
	}
	
	return 0;
}