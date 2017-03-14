#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

vector<int> uf_set;
int nr_set;
void init_set(int _size){
	uf_set.resize(_size);
	for(int i=0; i<_size;i++){
		uf_set[i] = i;
	}
	nr_set = _size;
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
	uf_set[uf_find(node1)] = uf_find(node2);
	nr_set--;
}

int main(){
	int n,m,s1,s2,nr_case=0;
	cin >> n >> m;
	while(n+m){
		nr_case++;
		init_set(n+1);
		for(int i=0;i<m;i++){
			cin >> s1 >> s2;
			uf_union(s1,s2);
		}
		cin >> n >> m;
		cout << "Case " << nr_case << ": " <<nr_set-1 << endl;
	}

	return 0;
}
