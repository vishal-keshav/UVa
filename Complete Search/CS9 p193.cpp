#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>


using namespace std;

vector<vector<int> > connects_to;
vector<int> max_black_list;
vector<int> vec;
vector<int> node_color;
int max_black_nr;

void init_graph(int n){
	connects_to.clear();
	connects_to.resize(n+1);
	node_color.clear();
	node_color.resize(n+1,-1);
	vec.clear();
	max_black_list.clear();
	max_black_nr = 0;
}

void color_graph(int node, int total_nr){
	//Base case
	if(node>total_nr){
		if(vec.size() > max_black_nr){
			max_black_nr = vec.size();
			max_black_list = vec;
			return;
		}
	}
	else{
		//Check if this node can be colored black_list
		bool can_be_black = true;
		for(vector<int>::iterator it = connects_to[node].begin(); it!=connects_to[node].end(); it++){
			if(node_color[(*it)]==1){
				can_be_black = false;
				break;
			}
		}
		if(can_be_black){
            //cout << node << endl;
			node_color[node] = 1;
			vec.push_back(node);
			color_graph(node+1, total_nr);
			vec.pop_back();
			node_color[node] = -1;
		}
		//White can be used anyways
		node_color[node] = 0;
		color_graph(node+1, total_nr);
		node_color[node] = -1;
	}
}

int main() {
	int m, n, k, n1, n2;
	cin >> m;
	while (m--) {
		cin >> n >> k;
		init_graph(n);
		for (int i = 0; i<k; i++) {
			cin >> n1 >> n2;
			connects_to[n1].push_back(n2);
			connects_to[n2].push_back(n1);
		}
		/*for(int i=1;i<=n;i++){
			for(int j=0;j<connects_to[i].size();j++){
				cout << connects_to[i][j] << " ";
			}
			cout << endl;
		}*/
		color_graph(1,n);
        int nr_black = max_black_list.size();
		cout << nr_black << endl;
		for(int i=0;i<nr_black-1;i++){
			cout << max_black_list[i] << " ";
		}
		cout << max_black_list[nr_black-1] << endl;
	}
	return 0;
}
