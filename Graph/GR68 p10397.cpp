#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <utility>
#include <cmath>
#include <map>

using namespace std;

long long int N,M;
map<pair<long long int, long long int>, long long int > vertex_map;
vector<pair<long long int, long long int> > vertex_list;
struct edge{
	long long int n1,n2;
	double w;
};
vector<struct edge> edges;

double dist(pair<long long int, long long int> p1, pair<long long int, long long int> p2){
	double ret = (double)((p1.first - p2.first)*(p1.first - p2.first));
	ret+= (double)((p1.second - p2.second)*(p1.second - p2.second));
	return sqrt(ret);
}
//////////////////////////////////
vector<long long int> union_set;
long long int nr_sets;
void init_uf(long long int n){
	union_set.clear();
	union_set.resize(n);
	for(long long int i=0;i<n;i++){
		union_set[i] = i;
	}
	nr_sets = n;
}
long long int find_set(long long int n){
	if(n==union_set[n]){
		return n;
	}
	else{
		union_set[n] = find_set(union_set[n]);
		return union_set[n];
	}
}
bool is_sameset(long long int i, long long int j){
	return (find_set(i)==find_set(j));
}
void make_union(long long int n1, long long int n2){
	if(!is_sameset(n1,n2)){
		union_set[find_set(n1)] = find_set(n2);
	}
	nr_sets--;
}
////////////////////////////////////////
double compute(void){
	init_uf(N);
	auto sort_fn = [](struct edge e1, struct edge e2) -> bool {
		return (e1.w < e2.w);
	};
	sort(edges.begin(), edges.end(), sort_fn);
	long long int index = 0;
	double ret = 0.0;
	pair<long long int, long long int> temp;
	while(nr_sets!=1){
		if(!is_sameset(edges[index].n1, edges[index].n2)){
			make_union(edges[index].n1, edges[index].n2);
			ret+=edges[index].w;
		}
		index++;
	}
	return ret;
}

int main(){
    //freopen("output.txt","w",stdout);
	while(cin >> N){
		pair<long long int, long long int> temp;
		vertex_map.clear();
		vertex_list.clear();
		for(long long int i=0;i<N;i++){
			cin >> temp.first >> temp.second;
			vertex_list.push_back(temp);
			vertex_map[temp] = i;
		}
		//Constructs the edges
		edges.clear();
		struct edge temp_edge;
		for(long long int i=0;i<N-1;i++){
			for(long long int j=i+1;j<N;j++){
				temp_edge.n1 = vertex_map[vertex_list[i]];
				temp_edge.n2 = vertex_map[vertex_list[j]];
				temp_edge.w = dist(vertex_list[i], vertex_list[j]);
				edges.push_back(temp_edge);
			}
		}
		cin >> M;
		for(long long int i=0;i<M;i++){
			cin >> temp_edge.n1 >> temp_edge.n2;
			temp_edge.n1--;
			temp_edge.n2--;
			temp_edge.w = 0;
			edges.push_back(temp_edge);
		}
		printf("%0.2f\n", compute());
	}
	return 0;
}
