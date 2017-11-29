#include <iostream>
#include <vector>
#include <iostream>
#include <algorithm>

#define NEG_INF -2147483648

using namespace std;
int n,m;


vector<vector<int> > graph;
vector<int> visited;

int find_max_component(int node, int ppa){
	int ret = 1;
	visited[node] = 1;
	for(int i=0;i<n;i++){
		if(graph[node][i]==ppa && visited[i]==0){
			ret+=find_max_component(i, ppa);
		}
	}
	return ret;
}

int main(){
    //freopen("output.txt","w",stdout);
	int node1, node2, ppa;
	int max_ppa, nr_node;
	cin >> n >> m;
	while(n+m){
        max_ppa = NEG_INF;
		graph.clear();
		graph.resize(n, vector<int>(n,NEG_INF));
		visited.clear();
		visited.resize(n,0);
		for(int i=0;i<m;i++){
			cin >> node1 >> node2 >> ppa;
			if(ppa > max_ppa){
				max_ppa = ppa;
			}
			graph[node1-1][node2-1] = max(graph[node1-1][node2-1],ppa);
			graph[node2-1][node1-1] = max(graph[node2-1][node1-1],ppa);
		}
		nr_node = 0;
		for(int i=0;i<n;i++){
			if(visited[i]==0){
				nr_node = max(nr_node,find_max_component(i, max_ppa));
			}
		}
		if(nr_node==1){
            nr_node = 0;
		}
		cout <<nr_node << endl;

		cin >> n >> m;
	}
    return 0;
}
