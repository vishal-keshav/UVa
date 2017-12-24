#include <iostream>
#include <stdio.h>
#include <utility>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int N;
vector<vector<int> > graph;

vector<int> compute_path(int s, int e){
	vector<int> ret;
	bool found = false;
	vector<int> visited(N,0);
	vector<int> parent(N);
	for(int i=0;i<N;i++){
		parent[i] = i;
	}
	queue<int> bfs_queue;
	bfs_queue.push(s);
	visited[s] = 1;
	while(!bfs_queue.empty()){
		int temp = bfs_queue.front();
		//cout << temp << endl;
		bfs_queue.pop();
		if(temp == e){
            //cout << "Matched, exiting" << endl;
			found = true;
			break;
		}
		else{
			for(int i=0;i<graph[temp].size();i++){
			    //cout << "for " << temp << " checking " << graph[temp][i] << endl;
				if(visited[graph[temp][i]]==0){
				    //cout << "Checkign success, enqued" << endl;
					bfs_queue.push(graph[temp][i]);
					visited[graph[temp][i]] = 1;
					parent[graph[temp][i]] = temp;
				}
			}
		}
	}
	/*for(int i=0;i<N;i++){
        cout << i << " " << parent[i] << endl;
	}*/
	if(found){
		int node = e;
		ret.clear();
		while(node!=s){
            //cout << node << endl;
			ret.push_back(node+1);
			node = parent[node];
		}
		ret.push_back(s+1);
		reverse(ret.begin(), ret.end());
	}
	return ret;
}

int main(){
    //freopen("output.txt","w",stdout);
	int E,start_node, end_node;
	vector<int> path;
	string connection;
	while(cin >> N){
		graph.clear();
		graph.resize(N);
		for(int i=0;i<N;i++){
			cin >> connection;
			//Process this connection
			int start_index, end_index;
			for(int i=0;i<connection.length(); i++){
				if(connection[i]=='-'){
					start_index = i+1;
					end_index = i+1;
					break;
				}
			}
			while(start_index<connection.length()){
				while(connection[end_index]!=',' && end_index<connection.length()){
					end_index++;
				}
				int temp = stoi(connection.substr(start_index, end_index-start_index));
				graph[i].push_back(temp-1);
				start_index = end_index+1;
				end_index++;
			}

		}
		for(int i=0;i<graph.size();i++){
            /*cout << i+1 << ":";
            for(int j=0;j<graph[i].size();j++){
                cout << graph[i][j]+1 << " ";
            }
            cout << endl;*/
			sort(graph[i].begin(), graph[i].end());
		}
		cin >> E;
		cout << "-----" << endl;
		for(int i=0;i<E;i++){
			cin >> start_node >> end_node;
			path = compute_path(start_node-1, end_node-1);
			if(path.size()>0){
				for(int i=0;i<path.size()-1;i++){
					cout << path[i] << " ";
				}
				cout << path[path.size()-1] << endl;
			}
			else{
				cout << "connection impossible" << endl;
			}
		}
	}

	return 0;
}
