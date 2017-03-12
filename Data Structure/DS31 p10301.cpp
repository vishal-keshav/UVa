#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

struct ring{
	float x,y,r;
};

vector<struct ring> elements;

int uf_max_size;
vector<int> uf_size;
vector<int> uf_set;
void init_set(int _size){
	uf_set.resize(_size);
	uf_size.resize(_size);
	for(int i=0;i<_size;i++){
		uf_set[i] = i;
		uf_size[i] = 1;
	}
	uf_max_size = 1;
}
int uf_find(int node){
	return (uf_set[node]==node?node:uf_set[node] = uf_find(uf_set[node]));
}
bool uf_same_set(int node1, int node2){
	return (uf_find(node1)==uf_find(node2));
}
void uf_union(int node1, int node2){
	if(uf_same_set(node1, node2)){
		return;
	}
	int set_size1 = uf_size[uf_find(node1)];
	int set_size2 = uf_size[uf_find(node2)];
	uf_set[node1] = uf_find(node2);
	uf_size[uf_find(node1)] = set_size1+set_size2;
	uf_max_size = max(uf_max_size, uf_size[uf_find(node1)]);
}

float distance(float x1, float y1, float x2, float y2){
	return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

bool is_intersecting(struct ring e1, struct ring e2){
    //Case 1: Circles are in one another
    if(e1.r>e2.r){
        if(e1.r > distance(e1.x,e1.y,e2.x,e2.y)){
            if(distance(e1.x,e1.y,e2.x,e2.y) + e2.r > e1.r){
                return true;
            }
            else{
                return false;
            }
        }
        else{
            if(distance(e1.x, e1.y, e2.x, e2.y) < e1.r + e2.r){
                return true;
            }
            else{
                return false;
            }
        }
    }
    else{
        if(e2.r > distance(e1.x,e1.y,e2.x,e2.y)){
            if(distance(e1.x,e1.y,e2.x,e2.y) + e1.r > e2.r){
                return true;
            }
            else{
                return false;
            }
        }
        else{
            if(distance(e1.x, e1.y, e2.x, e2.y) < e1.r + e2.r){
                return true;
            }
            else{
                return false;
            }
        }
    }
}

int main(){
    //freopen("output.txt","w",stdout);
	int T;
	cin >> T;
	float x,y,r;
	while(T!=-1){
		elements.resize(T);
		struct ring push_elem;
		for(int i=0;i<T;i++){
            cin >> push_elem.x >> push_elem.y >> push_elem.r;
			elements[i] = push_elem;
		}
		init_set(T);
		for(int i=0;i<T;i++){
			for(int j=i-1;j>=0;j--){
				if(is_intersecting(elements[i],elements[j])){
					uf_union(i,j);
				}
			}
		}
		if(uf_max_size==1){
			cout << "The largest component contains " << uf_max_size << " ring." << endl;
		}
		else{
			cout << "The largest component contains " << uf_max_size << " rings." << endl;
		}
		cin >> T;
	}
	return 0;
}
