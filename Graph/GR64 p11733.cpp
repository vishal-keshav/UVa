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
			edges.push_back(temp);
		}
		compute();
		cout << "Case #" << nr_case << ": " << min_cost << " " << nr_airport << endl;
	}

	return 0;
}
