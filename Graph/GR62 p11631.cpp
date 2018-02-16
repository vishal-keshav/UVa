#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <utility>

using namespace std;

long long int m,n;

struct edge{
	pair<long long int, long long int> e;
	long long int w;
};

vector<struct edge> edges;

vector<long long int> union_set;
void init_uf(void){
	union_set.clear();
	union_set.resize(m);
	for(long long int i=0;i<m;i++){
		union_set[i] = i;
	}
}
int find_set(long long int n){
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
}

long long int mst(void){
	long long int ret = 0;
	auto sort_func = [](struct edge e1, struct edge e2) -> bool{
		return (e1.w < e2.w);
	};
	sort(edges.begin(), edges.end(), sort_func);
	init_uf();
	for(long long int i=0;i<n;i++){
		if(!is_sameset(edges[i].e.first, edges[i].e.second)){
			make_union(edges[i].e.first, edges[i].e.second);
			ret+=edges[i].w;
		}
	}
	return ret;
}

int main(){
    //freopen("output.txt","w",stdout);
	struct edge temp;
	long long int total;
	cin >> m >> n;
	while(m+n){
        total = 0;
		edges.clear();
		for(long long int i=0;i<n;i++){
			cin >> temp.e.first >> temp.e.second >> temp.w;
			edges.push_back(temp);
			total+=temp.w;
		}
		cout << (total-mst()) <<endl;
		cin >> m >> n;
	}

	return 0;
}
