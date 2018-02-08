#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

int n,e;
vector<vector<int> > adj_list(200);
vector<int> node_color(200);

bool bicolorable(int node){
	int ret = true;
	for(int i=0;i<adj_list[node].size();i++){
		if(node_color[adj_list[node][i]]==-1){
			node_color[adj_list[node][i]] = 1 - node_color[node];
			ret = (ret && bicolorable(adj_list[node][i]));
			if(!ret){
				return ret;
			}
		}
		else if(node_color[adj_list[node][i]]==node_color[node]){
			return false;
		}
		else{
			//Do not do anything
		}
	}
	return ret;
}

int main(){
    int n1, n2;
	cin >> n;
	while(n){
		cin >> e;
		for(int i=0;i<n;i++){
			adj_list[i].clear();
			node_color[i] = -1;
		}
		for(int i=0;i<e;i++){
			cin >> n1 >> n2;
			adj_list[n1].push_back(n2);
			adj_list[n2].push_back(n1);
		}
		node_color[0] = 0;
		if(bicolorable(0)){
			cout << "BICOLORABLE." << endl;
		}
		else{
			cout << "NOT BICOLORABLE." << endl;
		}

		cin >> n;
	}
	return 0;
}
