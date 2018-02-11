#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <utility>
#include <cmath>

using namespace std;

int T, N;
struct coord{
	float x,y;
};
struct edge{
	pair<int, int> e;
	float w;
};

#define iterate(var, from, to) for(int var = int(from); var<=int(to); var++)
vector<int> pset(100);
void initSet(int _size) {pset.clear();
pset.resize(_size); iterate(i,0,_size-1) pset[i] = i;}
int findset(int i) {return (pset[i]==i)?i:(pset[i] = findset(pset[i]));}
void unionset(int i, int j) {pset[findset(i)] = findset(j);}
bool issameset(int i, int j) {return findset(i)==findset(j);}

vector<struct coord> vertices(100);
vector<struct edge> edges;
float calc_dist(struct coord c1, struct coord c2){
	return sqrt((c1.x-c2.x)*(c1.x-c2.x) + (c1.y-c2.y)*(c1.y-c2.y));
}
void sort_edges(void){
	auto sort_func = [](struct edge e1, struct edge e2)->bool{
		return (e1.w<e2.w)?true:false;
	};
	sort(edges.begin(), edges.end(), sort_func);
	return;
}
float min_len(void){
	float ret = 0.0;
	sort_edges();
	initSet(N);
	for(int i=0;i<edges.size();i++){
		if(!issameset(edges[i].e.first, edges[i].e.second)){
			unionset(edges[i].e.first, edges[i].e.second);
			ret+=edges[i].w;
		}
	}
	return ret;
}
int main(){
    //freopen("output.txt","w",stdout);
	struct coord temp_coord;
	cin >> T;
	while(T--){
		cin >> N;
		for(int i=0;i<N;i++){
			cin >> temp_coord.x >> temp_coord.y;
			vertices[i] = temp_coord;
		}
		//Create edges from these points
		edges.clear();
		struct edge temp_edge;
		pair<int,int> temp_pair;
		for(int i=0;i<N;i++){
			for(int j=i+1;j<N;j++){
				temp_pair.first = i;
				temp_pair.second = j;
				temp_edge.e = temp_pair;
				temp_edge.w = calc_dist(vertices[i], vertices[j]);
				edges.push_back(temp_edge);
			}
		}
		printf("%.2f\n", min_len());
		if(T){
            printf("\n");
		}
	}
	return 0;
}
