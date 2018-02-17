#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <utility>

using namespace std;

int T, N, M, A;
int min_cost, nr_airport;
struct edge{
	pair<int, int> e;
	int w;
};

vector<struct edge> edges;

vector<int> union_set;
int nr_sets;
void init_uf(void){
	union_set.clear();
	union_set.resize(N);
	for(int i=0;i<N;i++){
		union_set[i] = i;
	}
	nr_sets = N;
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

void compute(void){
	int temp_cost = A*N;
	min_cost = A*N;
	nr_airport = N;
	init_uf();
	auto sort_fn = [](struct edge e1, struct edge e2) -> bool{
		return (e1.w < e2.w);
	};
	sort(edges.begin(), edges.end(), sort_fn);
	for(int i=0;i<M;i++){
		if(!is_sameset(edges[i].e.first, edges[i].e.second)){
			make_union(edges[i].e.first, edges[i].e.second);
			temp_cost = temp_cost - A + edges[i].w;
			if(temp_cost < min_cost){
				min_cost = temp_cost;
				nr_airport = nr_sets;
			}
		}
	}
	return;
}

int main(){
    //freopen("output.txt","w",stdout);
	struct edge temp;
	int nr_case = 1;
	cin >> T;
	while(T--){
		cin >> N >> M >> A;
		edges.clear();
		for(int i=0;i<M;i++){
			cin >> temp.e.first >> temp.e.second >> temp.w;
			temp.e.first--;
			temp.e.second--;
			edges.push_back(temp);
		}
		compute();
		cout << "Case #" << nr_case << ": " << min_cost << " " << nr_airport << endl;
		nr_case++;
	}

	return 0;
}
