#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <utility>

using namespace std;

//Unio-find
#define iterate(var, from, to) for(int var = int(from); var<=int(to); var++)
vector<int> pset;
void initSet(int _size) {pset.clear();
pset.resize(_size); iterate(i,0,_size-1) pset[i] = i;}
int findset(int i) {return (pset[i]==i)?i:(pset[i] = findset(pset[i]));}
void unionset(int i, int j) {pset[findset(i)] = findset(j);}
bool issameset(int i, int j) {return findset(i)==findset(j);}

struct edge_elem{
	pair<int, int> e;
	int w;
};

int N,K,M;
vector<struct edge_elem> edges;

void sort_edges(void){
	auto sort_lambda = [](struct edge_elem e1, struct edge_elem e2)->bool {
		return (e1.w<e2.w)?true:false;
	};
	sort(edges.begin(), edges.end(), sort_lambda);
	return;
}

int calculate_mst(void){
	int ret = 0;
	sort_edges();
	initSet(N);
	for(int i=0;i<edges.size();i++){
		if(!issameset(edges[i].e.first, edges[i].e.second)){
			ret+=edges[i].w;
			unionset(edges[i].e.first, edges[i].e.second);
		}
	}
	return ret;
}

int main(){
    //freopen("output.txt","w",stdout);
	int old_res, new_res;
	int temp_w, temp_e1, temp_e2;
	struct edge_elem temp_edge;
	bool state = false;
	pair<int, int> temp_pair;
	while(cin >> N){
        if(state){
            cout << endl;
        }
        else{
            state = true;
        }
		old_res = 0;
		edges.clear();
		for(int i=0;i<N-1;i++){
			cin >> temp_e1 >> temp_e2 >> temp_w;
			old_res+=temp_w;
		}
		cin >> K;
		for(int i=0;i<K;i++){
			cin >> temp_e1 >> temp_e2 >> temp_w;
			temp_pair.first = temp_e1-1;
			temp_pair.second = temp_e2-1;
			temp_edge.e = temp_pair;
			temp_edge.w = temp_w;
			edges.push_back(temp_edge);
		}
		cin >> M;
		for(int i=0;i<M;i++){
			cin >> temp_e1 >> temp_e2 >> temp_w;
			temp_pair.first = temp_e1-1;
			temp_pair.second = temp_e2-1;
			temp_edge.e = temp_pair;
			temp_edge.w = temp_w;
			edges.push_back(temp_edge);
		}
		cout << old_res << endl;
		new_res = calculate_mst();
		cout << new_res << endl;
	}
	return 0;
}
