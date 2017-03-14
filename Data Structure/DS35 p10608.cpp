#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

vector<int> uf_set;
vector<int> uf_size;
int max_set_size;
void init_set(int _size){
	uf_set.resize(_size);
	uf_size.resize(_size);
	for(int i=0; i<_size;i++){
		uf_set[i] = i;
		uf_size[i] = 1;
	}
	max_set_size = 1;
}
int uf_find(int node){
	return (uf_set[node]==node?node:uf_set[node]=uf_find(uf_set[node]));
}
bool uf_same_set(int node1, int node2){
	return (uf_find(node1)==uf_find(node2));
}
void uf_union(int node1, int node2){
	if(uf_same_set(node1, node2)){
		return;
	}
	int size1 = uf_size[uf_find(node1)];
	int size2 = uf_size[uf_find(node2)];
	uf_set[uf_find(node1)] = uf_find(node2);
	uf_size[uf_find(node1)] = size1 + size2;
	max_set_size = max(max_set_size,uf_size[uf_find(node1)]);
}

int main(){
	int T,c1,c2;
	long int N,M;
	cin >> T;
	while(T--){
		cin >> N >> M;
		init_set(N+1);
		for(long int i=0;i<M;i++){
			cin >> c1 >> c2;
			uf_union(c1,c2);
		}
		cout << max_set_size << endl;
	}
	return 0;
}
