#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <utility>
#include <cmath>

using namespace std;

double n,r;
int nr_states;
double road_len, rail_len;
vector<pair<double, double> > city;

struct edge{
	pair<int, int> e;
	double w;
};

vector<struct edge> edges;

double calculate_dist(pair<double, double> a, pair<double, double> b){
	double ret = (a.first - b.first)*(a.first - b.first);
	ret+= (a.second-b.second)*(a.second-b.second);
	return sqrt(ret);
}

vector<int> union_set;
int nr_sets;
void init_uf(void){
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
		nr_sets--;
	}
}

void compute(void){
	//Create edges
	struct edge temp;
	for(int i=0;i<n-1;i++){
		for(int j=i+1;j<n;j++){
			temp.e.first = i;
			temp.e.second = j;
			temp.w = calculate_dist(city[i], city[j]);
			edges.push_back(temp);
		}
	}
	auto sort_func = [](struct edge e1, struct edge e2) -> bool{
		return (e1.w < e2.w);
	};
	sort(edges.begin(), edges.end(), sort_func);
	init_uf();

	road_len = 0;
	rail_len = 0;
	int i;
	for(i=0;i<edges.size();i++){
		if(edges[i].w > r){
			break;
		}
		else{
            if(!is_sameset(edges[i].e.first, edges[i].e.second)){
                make_union(edges[i].e.first, edges[i].e.second);
                road_len+=edges[i].w;
            }
		}
	}
	nr_states = nr_sets;
    while(nr_sets!=1){
        if(!is_sameset(edges[i].e.first, edges[i].e.second)){
            make_union(edges[i].e.first, edges[i].e.second);
            rail_len+=edges[i].w;
        }
        i++;
    }
}

int main(){
    //freopen("output.txt","w",stdout);
	int T, nr_case=1;
	pair<double, double> temp;
	cin >> T;
	while(T--){
		cin >> n >> r;
		city.clear();
		edges.clear();
		for(int i=0;i<n;i++){
			cin >> temp.first >> temp.second;
			city.push_back(temp);
		}
		compute();
		cout << "Case #" << nr_case << ": " << nr_states << " " << round(road_len) << " " << round(rail_len) << endl;
		nr_case++;
	}

	return 0;
}
