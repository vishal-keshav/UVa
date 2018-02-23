#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

struct vertex{
	int x,y;
};

struct edges{
	int v1;
	int v2;
	float distance;
};

vector<int> uf_set;
int nr_groups;
void init_set(int _size){
	uf_set.resize(_size);
	for(int i=0;i<_size;i++){
		uf_set[i] = i;
	}
	nr_groups = _size;
}
int uf_find(int node){
	return (uf_set[node]==node?node:uf_set[node]=uf_find(uf_set[node]));
}
bool uf_same_set(int node1, int node2){
	return (uf_find(node1)==uf_find(node2));
}
void uf_union(int node1, int node2){
	if(uf_same_set(node1,node2)){
		return;
	}
	uf_set[uf_find(node1)] = uf_find(node2);
	nr_groups--;
}

vector<struct vertex> posts;
vector<struct edges> links;

bool comp(struct edges e1, struct edges e2){
	return (e1.distance < e2.distance);
}

float find_distance(int i, int j){
    return sqrt((float)(posts[i].x-posts[j].x)*(posts[i].x-posts[j].x) + (float)(posts[i].y-posts[j].y)*(posts[i].y-posts[j].y));
}

int main(){
	int T,S,P;
	cin >> T;
	while(T--){
		cin >> S >> P;
		struct vertex temp_post;
		posts.resize(0);
		for(int i=0;i<P;i++){
			cin >> temp_post.x >> temp_post.y;
			posts.push_back(temp_post);
		}
		links.resize(0);
		struct edges temp_edge;
		for(int i=0;i<P;i++){
			for(int j=i-1;j>=0;j--){
				temp_edge.v1 = i;
				temp_edge.v2 = j;
				temp_edge.distance = find_distance(i,j);
				//cout << temp_edge.distance << endl;
				links.push_back(temp_edge);
			}
		}
		sort(links.begin(), links.end(), comp);
		init_set(P);
		int running_index=0;
		int nr_edges = (P*(P-1))/2;
		while(nr_groups > S && running_index < nr_edges){
			if(!uf_same_set(links[running_index].v1, links[running_index].v2)){
				uf_union(links[running_index].v1, links[running_index].v2);
			}
			running_index++;
		}
		//cout << links[running_index-1].distance << endl;
		printf("%.2f\n",links[running_index-1].distance);
	}
	return 0;
}
