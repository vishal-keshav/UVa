#include <iostream>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <string>

using namespace std;

//#define DEBUG 1

string pirates;

vector<int> seg_tree;

void init_seg(int node, int s, int e);
void init_seg_tree(void){
	int nr_elem = pirates.length();
	int tree_size = (int)(2*pow(2.0, floor((log((double)nr_elem)/log(2.0)) + 1)));
	seg_tree.resize(tree_size,0);
	init_seg(1, 0, nr_elem-1);
}

void init_seg(int node, int s_index, int e_index){
    //cout << s_index << " " << e_index << endl;
	if(s_index>e_index){
		return;
	}
	if(s_index==e_index){
		if(pirates[s_index]=='1'){
			seg_tree[node] = 1;
		}
		else{
			seg_tree[node] = 0;
		}
	}
	else{
		int mid = (s_index+e_index)/2;
		init_seg(2*node, s_index, mid);
		init_seg(2*node +1, mid+1, e_index);
		seg_tree[node] = seg_tree[2*node] + seg_tree[2*node + 1];
	}
	return;
}

int query(int node, int s, int e, int qs, int qe){
	if(qs>e || qe<s){
		return -1;
	}
	if(s>=qs && e<=qe){
		return seg_tree[node];
	}
	else{
		int m = (s+e)/2;
		int left = query(2*node, s,m,qs,qe);
		int right = query(2*node+1, m+1,e,qs,qe);
		if(left==-1){
			return right;
		}
		if(right==-1){
			return left;
		}
		seg_tree[node] = left+right;
		return seg_tree[node];
	}
}

void lazy_update(int node, int s, int e, int qs, int qe, int op){
    return;
}

int main(){
	int T,M,Q,R,nr_case, nr_elem,a,b;
	char operation;
	string input;
	cin >> T;
	while(T--){
		cin >> M;
		nr_case = 1;
		pirates.clear();
		for(int i=0;i<M;i++){
			cin >> R >> input;
			for(int j=0;j<R;j++){
				pirates.append(input);
			}
		}
		nr_elem = pirates.length();
#ifdef DEBUG
		cout << pirates << " "<< nr_elem << endl;
#endif
		init_seg_tree();

		cin >> Q;
		while(Q--){
			cin >> operation >> a >> b;
			switch(operation){
				case 'F':
                    lazy_update(1,0,nr_elem-1,a,b,0);
					break;
				case 'E':
                    lazy_update(1,0,nr_elem-1,a,b,1);
					break;
				case 'I':
                    lazy_update(1,0,nr_elem-1,a,b,2);
					break;
				case 'S':
					cout << query(1,0,nr_elem-1,a,b);
					break;
			}
		}
	}

	return 0;
}
