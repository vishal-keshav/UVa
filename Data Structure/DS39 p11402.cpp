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

int lazy_query(int node, int s, int e, int qs, int qe){
    cout << "QUERY " << s << " " << e << endl;
	if(qs>e || qe<s || s>e){
		return -1;
	}
	/*
	 * Lazy update, changes query
	 */
	if(pending[node]!=-1){
		if(pending[node]==0){
			seg_tree[node] = (e-s +1);
		}
		else if(pending[node]==1){
			seg_tree[node] = 0;
		}
		else{
			seg_tree[node] = (e-s +1) - seg_tree[node];
		}
		if(s!=e){
			pending[2*node] = pending[node];
			pending[2*node+1] = pending[node];
		}
		pending[node] = -1;
	}

	if(s>=qs && e<=qe){
		return seg_tree[node];
	}
	else{
		int m = (s+e)/2;
		int left = lazy_query(2*node, s,m,qs,qe);
		int right = lazy_query(2*node+1, m+1,e,qs,qe);
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
    cout << "UPDATE: "<<s << " " << e << endl;
    if(pending[node]!=-1){
		//Update on this node is required
		if(pending[node]==0){
			//Convert everyone to 1
			seg_tree[node] = (e-s +1);
		}
		else if(pending[node]==1){
			//Convert everyone to 0
			seg_tree[node] = 0;
		}
		else{
			//Invert pirates
			seg_tree[node] = ((e-s +1) - seg_tree[node]);
		}
		//Now, make childs pending for update
		if(s!=e){
			if(pending[2*node]!=-1){
				lazy_update(2*node, s, (s+e)/2, qs,qe, pending[node]);
			}
			//pending[2*node] = op;
			if(pending[2*node+1]!=-1){
				lazy_update(2*node+1, (s+e)/2+1, e, qs,qe, pending[node]);
			}
			//pending[2*node+1] = op;
		}
		pending[node] = -1;
		/*lazy_update(2*node, s, (s+e)/2, qs, qe, op);
		lazy_update(2*node+1, (s+e)/2 +1, e, qs, qe, op);*/
	}
	if(s>e || s>qe || e<qs){
		return;
	}
	if(s>=qs && e<=qe){
		if(op==0){
			seg_tree[node] = (e-s +1);
		}
		else if(op==1){
			seg_tree[node] = 0;
		}
		else{
			seg_tree[node] = ((e-s +1) - seg_tree[node]);
		}
		if(s!=e){
			pending[2*node] = op;
			pending[2*node + 1] = op;
		}
		return;
	}
	int m = (s+e)/2;
	lazy_update(2*node,s,m,qs,qe,op);
	lazy_update(2*node+1,m+1,e,qs,qe,op);
	seg_tree[node] = seg_tree[2*node]+seg_tree[2*node+1];
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
                    update(1,0,nr_elem-1,a,b,0);
					break;
				case 'E':
                    update(1,0,nr_elem-1,a,b,1);
					break;
				case 'I':
                    update(1,0,nr_elem-1,a,b,2);
					break;
				case 'S':
					cout << "Q" << nr_question << ": " <<query(1,0,nr_elem-1,a,b) << endl;
                    nr_question++;
					break;
			}
		}
		nr_case++;
	}

	return 0;
}
