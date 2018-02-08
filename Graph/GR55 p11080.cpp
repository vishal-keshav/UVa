#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

int t,n,e;
int zero, one;
vector<vector<int> > adj_list(200);
vector<int> node_color(200);

bool guard(int node){
	bool ret = true;
	for(int i=0;i<adj_list[node].size();i++){
		if(node_color[adj_list[node][i]]==-1){
			node_color[adj_list[node][i]] = 1 - node_color[node];
			if(node_color[node]==0){
				one++;
			}
			else{
				zero++;
			}
			ret = (ret && guard(adj_list[node][i]));
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
	cin >> t;
	while(t--){
		cin >> n >> e;
		for(int i=0;i<n;i++){
			adj_list[i].clear();
			node_color[i] = -1;
		}
		for(int i=0;i<e;i++){
			cin >> n1 >> n2;
			adj_list[n1].push_back(n2);
			adj_list[n2].push_back(n1);
		}
		int min_guard = 0;
		bool possible = true;
		for(int i=0;i<n;i++){
			if(node_color[i]==-1){
				zero = 0;
				one = 1;
				node_color[i] = 1;
				possible = possible && guard(i);
                if(!possible){
                    break;
                }
                else{
                    min_guard+=min(zero,one);
                }
			}

		}
		if(possible){
			cout << min_guard << endl;
		}
		else{
			cout << -1 << endl;
		}
	}
	return 0;
}
