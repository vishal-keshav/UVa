#include <iostream>
#include <stdio.h>
#include <utility>
#include <vector>
#include <queue>

using namespace std;

vector<vector<int> > graph;

void print(int n){
	if(n/10 == 0){
		cout << " " << n;
	}
	else{
		cout << n;
	}
}

int compute_path_length(int s, int e){
	int ret = 0;
	vector<int> visited(20,0);
	queue<int> bfs_queue;
	bfs_queue.push(s);
	visited[s] = 1;
	bfs_queue.push(-1);
	while(!bfs_queue.empty()){
		int temp = bfs_queue.front();
		bfs_queue.pop();
		if(temp == -1){
			ret++;
			bfs_queue.push(-1);
		}
		else{
			if(temp==e){
				break;
			}
			else{
				for(int i=0;i<20;i++){
					if(graph[temp][i] == 1 && visited[i] == 0){
						bfs_queue.push(i);
					}
				}
			}
		}

	}
	return ret;
}

int main(){
    //freopen("output.txt","w",stdout);
	int N,E,neighbour;
	int nr_case = 1;
	int path, start_node, end_node;
	while(cin >> N){
		graph.clear();
		graph.resize(20, vector<int>(20, 0));
		for(int i=0;i<N;i++){
			cin >> neighbour;
			graph[0][neighbour-1] = 1;
			graph[neighbour-1][0] = 1;
		}
		for(int i=1;i<19;i++){
			cin >> N;
			for(int j=0;j<N;j++){
				cin >> neighbour;
				graph[i][neighbour-1] = 1;
				graph[neighbour-1][i] = 1;
			}
		}
		cin >> E;
		cout << "Test Set #" << nr_case << endl;
		for(int i=0;i<E;i++){
			cin >> start_node >> end_node;
			path = compute_path_length(start_node-1, end_node-1);
			print(start_node);
			cout << " to ";
			print(end_node);
			cout << ": " << path << endl;
		}
		cout << endl;

		nr_case++;
	}

	return 0;
}
