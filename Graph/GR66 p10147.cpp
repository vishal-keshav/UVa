#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>

using namespace std;

int T,N,M;
map<pair<int, int>, int > vertex_map;
vector<pair<int, int> > vertex_list;
struct edge{
	int n1,n2;
	int w;
};
vector<struct edge> edges;

int dist(pair<int, int> p1, pair<int, int> p2){
	int ret = (p1.first - p2.first)*(p1.first - p2.first);
	ret+= (p1.second - p2.second)*(p1.second - p2.second);
	return ret;
}

//////////////////////////////////
vector<int> union_set;
int nr_sets;
void init_uf(int n){
	union_set.clear();
	union_set.resize(n);
	for(int i=0;i<n;i++){
		union_set[i] = i;
	}
	nr_sets = n;
}
int find_set(int n){
	if(n==union_set[n]){
		return n;
	}
	else{
		union_set[n] = find_set(union_set[n]);
		return union_set[n];
	}
}
bool is_sameset(int i, int j){
	return (find_set(i)==find_set(j));
}
void make_union(int n1, int n2){
	if(!is_sameset(n1,n2)){
		union_set[find_set(n1)] = find_set(n2);
	}
	nr_sets--;
}
////////////////////////////////////////
vector<pair<int, int> > compute(void){
	vector<pair<int, int> > ret;
	init_uf(N);
	auto sort_fn = [](struct edge e1, struct edge e2) -> bool {
		return (e1.w < e2.w);
	};
	sort(edges.begin(), edges.end(), sort_fn);
	int index = 0;
	pair<int, int> temp;
	while(nr_sets!=1){
		if(!is_sameset(edges[index].n1, edges[index].n2)){
			make_union(edges[index].n1, edges[index].n2);
			if(edges[index].w!=0){
				temp.first = edges[index].n1;
				temp.second = edges[index].n2;
				ret.push_back(temp);
			}
		}
		index++;
	}
	return ret;
}

int main(){
    //freopen("output.txt","w",stdout);
	cin >> T;
	while(T--){
		pair<int, int> temp;
		vertex_map.clear();
		vertex_list.clear();
		cin >> N;
		for(int i=0;i<N;i++){
			cin >> temp.first >> temp.second;
			vertex_list.push_back(temp);
			vertex_map[temp] = i;
		}
		//Constructs the edges
		edges.clear();
		struct edge temp_edge;
		for(int i=0;i<N-1;i++){
			for(int j=i+1;j<N;j++){
				temp_edge.n1 = vertex_map[vertex_list[i]];
				temp_edge.n2 = vertex_map[vertex_list[j]];
				temp_edge.w = dist(vertex_list[i], vertex_list[j]);
				edges.push_back(temp_edge);
			}
		}
		cin >> M;
		for(int i=0;i<M;i++){
			cin >> temp_edge.n1 >> temp_edge.n2;
			temp_edge.n1--;
			temp_edge.n2--;
			temp_edge.w = 0;
			edges.push_back(temp_edge);
		}
		vector<pair<int, int> > ans = compute();
		if(ans.size()==0){
			cout << "No new highways need" << endl;
		}
		else{
			for(int i=0;i<ans.size();i++){
				cout << ans[i].first+1 << " " << ans[i].second+1 << endl;
			}
		}
		if(T){
			cout << endl;
		}
	}
	return 0;
}
