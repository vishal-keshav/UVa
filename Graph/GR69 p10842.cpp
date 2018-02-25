#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

#define INT_MAXIMUM 100000000

int N,n,m;
struct edge{
	int n1,n2;
	int w;
};
vector<struct edge> edges;
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

bool is_samecity(int n1, int n2){
	if(n1==n2){
		return true;
	}
	return false;
}

int compute(void){
	init_uf(n);
	auto sort_fn = [](struct edge e1, struct edge e2) -> bool {
		return (e1.w > e2.w);
	};
	sort(edges.begin(), edges.end(), sort_fn);
	int index = 0;
	int ret = INT_MAXIMUM;
	while(nr_sets!=1){
		if(!is_sameset(edges[index].n1, edges[index].n2) && !is_samecity(edges[index].n1, edges[index].n2)){
			make_union(edges[index].n1, edges[index].n2);
			ret = min(ret, edges[index].w);
		}
		index++;
		if(index>=m){
            break;
		}
	}
	return ret;
}

int main(){
    //freopen("output.txt","w",stdout);
	int nr_case = 1;
	cin >> N;
	while(N--){
		cin >> n >> m;
		struct edge temp;
		edges.clear();
		for(int i=0;i<m;i++){
			cin >> temp.n1 >> temp.n2 >> temp.w;
			edges.push_back(temp);
		}
		cout << "Case #" << nr_case << ": " << compute() << endl;
		nr_case++;
	}
	return 0;
}
