#include <iostream>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <string>

using namespace std;

//#define DEBUG 1

string pirates;

vector<int> seg_tree;
vector<int> pending;

void lazy_update(int node, int s, int e, int qs, int qe, int op);
void init_seg(int node, int s, int e);
void init_seg_tree(void){
	int nr_elem = pirates.length();
	int tree_size = (int)(2*pow(2.0, floor((log((double)nr_elem)/log(2.0)) + 1)));
	seg_tree.resize(tree_size,9999);
	pending.resize(tree_size,-1);
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

////////////////////Helper Function//////////////////////////////
int get_new_op(int node, int op){
	if(op==0 || op==1){
		return op;
	}
	else if(op == 2){
		if(pending[node] == -1){
			return 2;
		}
		else if(pending[node] == 0){
			return 1;
		}
		else if(pending[node] == 1){
			return 0;
		}
		else{
			return -1;
		}
	}
	else{
		return pending[node];
	}
}

int get_sum(int node, int s, int e, int qs, int qe, int op){
	if(op == -1){
		return seg_tree[node];
	}
	else if(op == 0){
		return (e-s +1);
	}
	else if(op == 1){
		return 0;
	}
	else{
		return ((e-s +1) - seg_tree[node]);
	}
}

void change(int node, int s, int e, int qs, int qe, int op){
	if(op=-1){
		return;
	}
	int sum = get_sum(node, s, e, qs, qe, op);
	seg_tree[node] = sum;
	//If not a leaf node, propagate action to child node
	if(s!=e){
		int new_op = get_new_op(2*node, op);
		pending[2*node] = new_op;
		new_op = get_new_op(2*node +1, op);
		pending[2*node +1] = new_op;
	}
}

void propagate(int node, int s, int e, int qs, int qe, int op){
	if(op==-1){
		return;
	}
	else{
		change(node, s, e, qs, qe, op);
		pending[node] = -1;
	}
}
///////////////////////////////////////////////////////////////////

int lazy_query(int node, int s, int e, int qs, int qe){
	if(qs>e || qe<s || s>e){
		return 0;
	}

	if(s<=qs && qe<=e){
		if(pending[node]==0){
			return (qe-qs +1);
		}
		if(pending[node]==1){
			return 0;
		}
	}

	if(qs<=s && e<=qe){
		propagate(node, s, e, qs, qe, pending[node]);
		return seg_tree[node];
	}
	else{
		propagate(node, s, e, qs, qe, pending[node]);
		int left = lazy_query(2*node, s, (s+e)/2 , qs, qe);
		int right = lazy_query(2*node +1, (s+e)/2 +1, e, qs, qe);
		return (left+right);
	}
}

/*
 * If current segment tree node has any pending update, then first update that pending
 * update to current node.
 *
 * If the interval represented by current node lies completely in the interval to
 * update, then update the current node and update the lazy[] array for children nodes.
 *
 * If the interval represented by current node overlaps with the interval to update,
 * then update the nodes as usual.
 */


void lazy_update(int node, int s, int e, int qs, int qe, int op){
	if(s>e || (s>qe || e<qs)){
		return;
	}
	propagate(node,s,e,qs,qe,pending[node]);

	if(s>=qs && e<=qe){
		change(node,s,e,qs,qe,op);
		return;
	}
	int mid = (s+e)/2;
	lazy_update(2*node, s, mid, qs, qe, op);
	lazy_update(2*node +1, mid+1, e, qs, qe, op);
	seg_tree[node] = seg_tree[2*node] + seg_tree[2*node +1];
}

void update(int node, int s, int e, int qs, int qe, int op){
    //cout << "UPDATE: "<<s << " " << e << endl;
	if(s>e || s>qe || e<qs){
		return;
	}
	if(s>=qs && e<=qe){
		if(op==0){
			seg_tree[node] = (e-s +1);
			if(s!=e){
                update(2*node, s, (s+e)/2, qs, qe, op);
                update(2*node + 1, (s+e)/2 + 1, e, qs, qe, op);
			}
		}
		else if(op==1){
			seg_tree[node] = 0;
			if(s!=e){
                update(2*node, s, (s+e)/2, qs, qe, op);
                update(2*node + 1, (s+e)/2 + 1, e, qs, qe, op);
			}
		}
		else{
			seg_tree[node] = ((e-s +1) - seg_tree[node]);
			if(s!=e){
                update(2*node, s, (s+e)/2, qs, qe, op);
                update(2*node + 1, (s+e)/2 + 1, e, qs, qe, op);
			}
		}
		return;
	}
	int m = (s+e)/2;
	update(2*node,s,m,qs,qe,op);
	update(2*node+1,m+1,e,qs,qe,op);
	seg_tree[node] = seg_tree[2*node]+seg_tree[2*node+1];
}

int query(int node, int s, int e, int qs, int qe){
    //cout << "QUERY " << s << " " << e << endl;
	if(qs>e || qe<s || s>e){
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
		//seg_tree[node] = left+right;
		return left+right;
	}
}

int main(){
    //freopen("output.txt","w",stdout);
	int T,M,Q,R,nr_case,nr_question, nr_elem,a,b;
	char operation;
	string input;
	cin >> T;
	nr_case = 1;
	while(T--){
		cin >> M;
		nr_question = 1;
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
		cout << "Case " << nr_case << ":" << endl;
		while(Q--){
			cin >> operation >> a >> b;
			switch(operation){
				case 'F':
                    lazy_update(1,0,nr_elem-1,a,b,0);
#ifdef DEBUG
					for(vector<int>::iterator it = seg_tree.begin(); it!=seg_tree.end(); it++){
						cout << (*it) << " ";
					}
					cout << endl;
					for(vector<int>::iterator it = pending.begin(); it!=pending.end(); it++){
						cout << (*it) << " ";
					}
					cout << endl << endl;
#endif
					break;
				case 'E':
                    lazy_update(1,0,nr_elem-1,a,b,1);
#ifdef DEBUG
					for(vector<int>::iterator it = seg_tree.begin(); it!=seg_tree.end(); it++){
						cout << (*it) << " ";
					}
					cout << endl;
					for(vector<int>::iterator it = pending.begin(); it!=pending.end(); it++){
						cout << (*it) << " ";
					}
					cout << endl << endl;
#endif
					break;
				case 'I':
                    lazy_update(1,0,nr_elem-1,a,b,2);
#ifdef DEBUG
					for(vector<int>::iterator it = seg_tree.begin(); it!=seg_tree.end(); it++){
						cout << (*it) << " ";
					}
					cout << endl;
					for(vector<int>::iterator it = pending.begin(); it!=pending.end(); it++){
						cout << (*it) << " ";
					}
					cout << endl << endl;
#endif
					break;
				case 'S':
					cout << "Q" << nr_question << ": " <<lazy_query(1,0,nr_elem-1,a,b) << endl;
                    nr_question++;
					break;
			}
		}
		nr_case++;
	}

	return 0;
}
