#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>

#define INT_MAXIMUM 1000000

//#define DEBUG 1

using namespace std;

vector<vector<int> > adj_list;
vector<bool> visited;
vector<vector<int> > DP;
int n,u,v,sz;

string input,temp_input;

int fill_dp(int node, int color){
	if(DP[node][color]!=INT_MAXIMUM){
		return DP[node][color];
	}
	else{
		int ret = color;
		int child_ret;
		//Iterate for each child with a different color than parent
		for(vector<int>::iterator it = adj_list[node].begin(); it!= adj_list[node].end();it++){
			if(!visited[*it]){
				visited[*it] = true;
				child_ret = INT_MAXIMUM;
				for(int i=1;i<=6;i++){
					if(i==color){
						continue;
					}
					child_ret = min(child_ret,fill_dp(*it,i));
				}
				visited[*it] = false;
				ret+=child_ret;
			}
		}
		DP[node][color] = ret;
		return ret;
	}
}

int main(){
    //freopen("output.txt","w",stdout);
	cin >> n;
	while(n){
        cin.ignore();
		adj_list.clear();
		adj_list.resize(n);
		for(int i=0;i<n;i++){
		    //cin.ignore();
			getline(cin,input);
			stringstream ss(input);
			ss >> temp_input;
			temp_input.pop_back();
			u = atoi(temp_input.c_str());
#ifdef DEBUG
			cout << u << " : ";
#endif
			while(ss >> temp_input){
				v = atoi(temp_input.c_str());
				adj_list[u].push_back(v);
				adj_list[v].push_back(u);
#ifdef DEBUG
				cout << v << " ";
#endif
			}
#ifdef DEBUG
			cout << endl;
#endif
		}
#ifdef DEBUG
		//Printing adj list
		for(int i=0;i<n;i++){
			cout << i << " : ";
			for(vector<int>::iterator iter = adj_list[i].begin(); iter!=adj_list[i].end();iter++){
				cout << *iter << " ";
			}
			cout << endl;
		}
#endif
		visited.clear();
		visited.resize(n,false);
		DP.clear();
		//God knows how 6 colors are sufficient
		DP.resize(n,vector<int>(7,INT_MAXIMUM));
		int ret = INT_MAXIMUM;
		for(int i=1;i<=6;i++){
			visited[0] = true;
			ret = min(ret,fill_dp(0,i));
			visited[0] = false;
		}
		cout << ret << endl;


		cin >> n;
	}

	return 0;
}
