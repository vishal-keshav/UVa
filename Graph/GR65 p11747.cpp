#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <utility>

using namespace std;

int N, M;
struct edge{
	pair<int, int> e;
	int w;
};

vector<struct edge> edges;
vector<int> heavy_weights;

vector<int> union_set;
void init_uf(void){
	union_set.clear();
	union_set.resize(N);
	for(int i=0;i<N;i++){
		union_set[i] = i;
	}
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
}

void compute(void){
	init_uf();
	auto sort_fn = [](struct edge e1, struct edge e2) -> bool{
		return (e1.w < e2.w);
	};
	sort(edges.begin(), edges.end(), sort_fn);
	for(int i=0;i<M;i++){
		if(!is_sameset(edges[i].e.first, edges[i].e.second)){
			make_union(edges[i].e.first, edges[i].e.second);
		}
		else{
			heavy_weights.push_back(edges[i].w);
		}
	}
	return;
}

int main(){
    //freopen("output.txt","w",stdout);
	struct edge temp;
	cin >> N >> M;
	while(N+M){
		edges.clear();
		heavy_weights.clear();
		for(int i=0;i<M;i++){
			cin >> temp.e.first >> temp.e.second >> temp.w;
			edges.push_back(temp);
		}
		compute();
		int nr_weights = heavy_weights.size();
		if(nr_weights==0){
			cout << "forest" << endl;
		}
		else{
			for(int i=0;i<nr_weights-1;i++){
				cout << heavy_weights[i] << " ";
			}
			cout << heavy_weights[nr_weights-1] << endl;
		}
		cin >> N >> M;
	}

	return 0;
}
