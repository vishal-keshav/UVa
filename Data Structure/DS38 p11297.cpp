#include <iostream>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <algorithm>

using namespace std;

//#define DEBUG 1

#define INT_MINIMUM -1
#define INT_MAXIMUM 1000000

vector<vector<int> > city_population;

vector<int> quad_tree_min;
vector<int> quad_tree_max;

void init_quad(int node, int x1, int y1, int x2, int y2);
void init_quad_tree(int nr_elem){
	int tree_size = ((int)(4*pow(4.0, floor((log((double)(nr_elem*nr_elem))/log(4.0))+1))) - 1)/3;
	quad_tree_min.resize(tree_size,INT_MAXIMUM);
	quad_tree_max.resize(tree_size,INT_MINIMUM);
	init_quad(0, 0, 0, nr_elem-1, nr_elem-1);
}
void init_quad(int node, int x1, int y1, int x2, int y2){
	/*For square city, just the checking of x1==x2 is enough*/
	if(x1>x2 || y1>y2){
        return;
	}
	//cout << "("<<x1 << "," << y1 << ") (" <<x2 << "," << y2 << ")" << endl;
	if(x1==x2 && y1==y2){
		quad_tree_min[node] = city_population[x1][y1];
		quad_tree_max[node] = city_population[x1][y1];
	}
	else{
		int upper_left = 4*node + 1;
		int upper_right = 4*node + 2;
		int lower_left = 4*node + 3;
		int lower_right = 4*node + 4;
		init_quad(upper_left, x1, y1, (x1+x2)/2, (y1+y2)/2);
		init_quad(upper_right, (x1+x2)/2 + 1, y1, x2, (y1+y2)/2);
		init_quad(lower_left, x1, (y1+y2)/2 + 1, (x1+x2)/2, y2);
		init_quad(lower_right, (x1+x2)/2 + 1, (y1+y2)/2 + 1, x2, y2);

		int upper_left_value_min = quad_tree_min[upper_left];
		int upper_right_value_min = quad_tree_min[upper_right];
		int lower_left_value_min = quad_tree_min[lower_left];
		int lower_right_value_min = quad_tree_min[lower_right];
		quad_tree_min[node] = min(min(upper_left_value_min, upper_right_value_min), min(lower_left_value_min, lower_right_value_min));

		int upper_left_value_max = quad_tree_max[upper_left];
		int upper_right_value_max = quad_tree_max[upper_right];
		int lower_left_value_max = quad_tree_max[lower_left];
		int lower_right_value_max = quad_tree_max[lower_right];
		quad_tree_max[node] = max(max(upper_left_value_max, upper_right_value_max), max(lower_left_value_max, lower_right_value_max));
	}
}

bool overlapping(int x1, int y1, int x2, int y2, int qx1, int qy1, int qx2, int qy2){
	//If one square is right of another one
	if(x2<qx1 || qx2<x1){
		return false;
	}
	//If one square is above another one
	if(y2 < qy1 || qy2 < y1){
		return false;
	}
	return true;
}

bool containing(int x1, int y1, int x2, int y2, int qx1, int qy1, int qx2, int qy2){
	if(qx1<=x1 && qy1<=y1 && qx2>=x2 && qy2>=y2){
		return true;
	}
	return false;
}

int query_min(int node, int x1, int y1, int x2, int y2, int query_x1, int query_y1, int query_x2, int query_y2){
	if(!overlapping(x1,y1,x2,y2,query_x1,query_y1,query_x2,query_y2)){
		return -1;
	}
	if(containing(x1,y1,x2,y2,query_x1,query_y1,query_x2,query_y2)){
		return quad_tree_min[node];
	}
	int upper_left_value = query_min(4*node + 1,x1,y1,(x1+x2)/2,(y1+y2)/2,query_x1,query_y1,query_x2,query_y2);
	int upper_right_value = query_min(4*node + 2,(x1+x2)/2 + 1, y1, x2, (y1+y2)/2,query_x1,query_y1,query_x2,query_y2);
	int lower_left_value = query_min(4*node + 3,x1, (y1+y2)/2 + 1, (x1+x2)/2, y2,query_x1,query_y1,query_x2,query_y2);
	int lower_right_value = query_min(4*node + 4,(x1+x2)/2 + 1, (y1+y2)/2 + 1, x2, y2,query_x1,query_y1,query_x2,query_y2);
	int ret = INT_MAXIMUM;
	if(upper_left_value!=-1){
		ret = min(ret,upper_left_value);
	}
	if(upper_right_value!=-1){
		ret = min(ret,upper_right_value);
	}
	if(lower_left_value!=-1){
		ret = min(ret,lower_left_value);
	}
	if(lower_right_value!=-1){
		ret = min(ret,lower_right_value);
	}
	return ret;
}

int query_max(int node, int x1, int y1, int x2, int y2, int query_x1, int query_y1, int query_x2, int query_y2){
	if(!overlapping(x1,y1,x2,y2,query_x1,query_y1,query_x2,query_y2)){
		return -1;
	}
	if(containing(x1,y1,x2,y2,query_x1,query_y1,query_x2,query_y2)){
		return quad_tree_max[node];
	}
	int upper_left_value = query_max(4*node + 1,x1,y1,(x1+x2)/2,(y1+y2)/2,query_x1,query_y1,query_x2,query_y2);
	int upper_right_value = query_max(4*node + 2,(x1+x2)/2 + 1, y1, x2, (y1+y2)/2,query_x1,query_y1,query_x2,query_y2);
	int lower_left_value = query_max(4*node + 3,x1, (y1+y2)/2 + 1, (x1+x2)/2, y2,query_x1,query_y1,query_x2,query_y2);
	int lower_right_value = query_max(4*node + 4,(x1+x2)/2 + 1, (y1+y2)/2 + 1, x2, y2,query_x1,query_y1,query_x2,query_y2);
	int ret = INT_MINIMUM;
	if(upper_left_value!=-1){
		ret = max(ret,upper_left_value);
	}
	if(upper_right_value!=-1){
		ret = max(ret,upper_right_value);
	}
	if(lower_left_value!=-1){
		ret = max(ret,lower_left_value);
	}
	if(lower_right_value!=-1){
		ret = max(ret,lower_right_value);
	}
	return ret;
}

void update(int node, int x1, int y1, int x2, int y2, int cx, int cy, int value){
	if(x1==x2 && y1==y2){
		city_population[cx][cy] = value;
		quad_tree_max[node] = value;
		quad_tree_min[node] = value;
	}
	else{
		int x_mid = (x1+x2)/2;
		int y_mid = (y1+y2)/2;
		if(cx<=x_mid && cy<=y_mid){
			update(4*node+1, x1, y1, x_mid, y_mid, cx, cy, value);
		}
		else if(cx>x_mid && cy<=y_mid){
			update(4*node+2, x_mid+1, y1, x2, y_mid, cx, cy, value);
		}
		else if(cx<=x_mid && cy>y_mid){
			update(4*node+3, x1, y_mid+1, x_mid, y2, cx, cy, value);
		}
		else{
			update(4*node+4, x_mid+1, y_mid+1, x2, y2, cx, cy, value);
		}
		int upper_left_value = quad_tree_min[4*node+1];
        int upper_right_value = quad_tree_min[4*node+2];
        int lower_left_value = quad_tree_min[4*node+3];
        int lower_right_value = quad_tree_min[4*node+4];

        quad_tree_min[node] = min(min(upper_left_value, upper_right_value), min(lower_left_value, lower_right_value));

        upper_left_value = quad_tree_max[4*node+1];
        upper_right_value = quad_tree_max[4*node+2];
        lower_left_value = quad_tree_max[4*node+3];
        lower_right_value = quad_tree_max[4*node+4];

        quad_tree_max[node] = max(max(upper_left_value, upper_right_value), max(lower_left_value, lower_right_value));
	}
	return;
}

int main(){
    //freopen("output.txt","w",stdout);
	int N,Q,query_x1, query_y1, query_x2, query_y2;
	int change_x, change_y, change_v, population;
	char operation;
	cin >> N;
	city_population.resize(N, vector<int>(N));
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			cin >> population;
			city_population[i][j] = population;
		}
	}
#ifdef DEBUG
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			cout << city_population[i][j] << " ";
		}
		cout << endl;
	}
#endif
	init_quad_tree(N);
	cin >> Q;
	while(Q--){
		cin >> operation;
		if(operation=='q'){
			cin >> query_x1 >> query_y1 >> query_x2 >> query_y2;
			cout << query_max(0,0,0,N-1,N-1,query_x1-1,query_y1-1,query_x2-1,query_y2-1)<<" "<<query_min(0,0,0,N-1,N-1,query_x1-1,query_y1-1,query_x2-1,query_y2-1) << endl;
		}
		else{
			cin >> change_x >> change_y >> change_v;
			update(0,0,0,N-1,N-1,change_x-1,change_y-1,change_v);
		}
	}
	return 0;
}
