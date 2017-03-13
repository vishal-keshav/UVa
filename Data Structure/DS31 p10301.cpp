#include <iostream>
#include <stdio.h>
#include <vector>
#include <math.h>

using namespace std;

float min_float(float a, float b){
    return (a<b?a:b);
}
float max_float(float a, float b){
    return (a<b?b:a);
}
int max_int(int a, int b){
    return (a<b?b:a);
}

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
	uf_set[uf_find(node1)] = uf_find(node2);
	uf_size[uf_find(node1)] = set_size1+set_size2;
	uf_max_size = max_int(uf_max_size, uf_size[uf_find(node1)]);
}

float distance(float x1, float y1, float x2, float y2){
	return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

bool is_intersecting(struct ring e1, struct ring e2){
    //If intersecting a infinite points
    if(e1.x == e2.x && e1.y == e2.y && e1.r == e2.r){
        return true;
    }
    if(distance(e1.x,e1.y,e2.x,e2.y)<= e1.r+e2.r){
        //Case when circle ids within the other circle has to be taken
        if(distance(e1.x,e1.y,e2.x,e2.y) >= max_float(e1.r,e2.r) - min_float(e1.r,e2.r)){
            return true;
        }
        else{
            return false;
        }
    }
    else{
        return false;
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
		if(T==0){
            cout << "The largest component contains " << "0" << " rings." << endl;
		}
		else if(uf_max_size==1){
			cout << "The largest component contains " << uf_max_size << " ring." << endl;
		}
		else{
			cout << "The largest component contains " << uf_max_size << " rings." << endl;
		}
		cin >> T;
	}
	return 0;
}
