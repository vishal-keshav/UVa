#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <utility>
#include <string>
#include <map>

using namespace std;

int s,c;

struct edge{
	pair<int, int> e;
	int w;
};

vector<struct edge> edges;
map<string, int> city_map;

vector<int> union_set;
int nr_sets;
void init_uf(void){
	union_set.clear();
	union_set.resize(s);
	for(int i=0;i<s;i++){
		union_set[i] = i;
	}
	nr_sets = s;
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

int mst(void){
	int ret = 0;
	auto sort_func = [](struct edge e1, struct edge e2) -> bool{
		return (e1.w < e2.w);
	};
	sort(edges.begin(), edges.end(), sort_func);
	init_uf();
	for(int i=0;i<c;i++){
		if(!is_sameset(edges[i].e.first, edges[i].e.second)){
			make_union(edges[i].e.first, edges[i].e.second);
			ret+=edges[i].w;
		}
	}
	if(nr_sets==1){
		return ret;
	}
	else{
		return -1;
	}
}

int main(){
    //freopen("output.txt","w",stdout);
	struct edge temp;
	string temp_city,c1,c2;
	cin >> s >> c;
	while(s+c){
		edges.clear();
		city_map.clear();
		for(int i=0;i<s;i++){
			cin >> temp_city;
			city_map[temp_city] = i;
		}
		for(int i=0;i<c;i++){
			cin >> c1 >> c2 >> temp.w;
			temp.e.first = city_map[c1];
			temp.e.second = city_map[c2];
			edges.push_back(temp);
		}
		cin >> temp_city;
		int ans = mst();
		if(ans==-1){
			cout << "Impossible" << endl;
		}
		else{
			cout << ans << endl;
		}
		cin >> s >> c;
	}

	return 0;
}
