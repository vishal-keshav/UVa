#include <iostream>
#include <stdio.h>
#include <map>
#include <vector>
#include <string>

using namespace std;

map<string,int> friend_map;

vector<int> uf_set;
vector<int> uf_size;
void init_set(int _size){
	uf_set.resize(_size);
	uf_size.resize(_size);
	for(int i=0; i<_size;i++){
		uf_set[i] = i;
		uf_size[i] = 1;
	}
}
int uf_find(int node){
	return (uf_set[node]==node?node:uf_set[node]=uf_find(uf_set[node]));
}
bool uf_same_set(int node1, int node2){
	return (uf_find(node1)==uf_find(node2));
}
int uf_union(int node1, int node2){
	if(uf_same_set(node1, node2)){
		return uf_size[uf_find(node1)];
	}
	int size1 = uf_size[uf_find(node1)];
	int size2 = uf_size[uf_find(node2)];
	uf_set[uf_find(node1)] = uf_find(node2);
	uf_size[uf_find(node1)] = size1 + size2;
	return uf_size[uf_find(node1)];
}

int main(){
	int T,F;
	string f1,f2;
	int running_index;
	cin >> T;
	while(T--){
		cin >> F;
		running_index = 0;
		friend_map.clear();
		init_set(F+1);
		for(int i=0;i<F;i++){
			cin >> f1 >> f2;
			if(friend_map.count(f1)==0){
				friend_map[f1] = running_index;
				running_index++;
			}
			if(friend_map.count(f2)==0){
				friend_map[f2] = running_index;
				running_index++;
			}
			cout << uf_union(friend_map[f1],friend_map[f2]) << endl;
		}
	}

	return 0;
}
