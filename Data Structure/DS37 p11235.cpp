#include <iostream>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

//#define DEBUG 1
vector<int> input;

vector<int> segment_tree;

void init_seg(int node, int s_index, int e_index);

void init_seg_tree(vector<int> vec){
	int nr_elem = vec.size();
	int tree_size = (int)(2 * pow(2.0, floor((log((double)nr_elem) / log(2.0)) + 1)));
	segment_tree.resize(tree_size,999);
	init_seg(1,0,nr_elem-1);
}
void init_seg(int node, int s_index, int e_index){
	if(s_index==e_index){
		segment_tree[node] = 1;
	}
	else{
		int left_child = 2*node;
		int right_child = 2*node + 1;
		init_seg(left_child, s_index, (s_index+e_index)/2);
		init_seg(right_child, (s_index+e_index)/2 + 1, e_index);
		if(input[(s_index+e_index)/2] != input[(s_index+e_index)/2 + 1]){
			segment_tree[node] = max(segment_tree[left_child], segment_tree[right_child]);
		}
		else{
			int middle_elem_freq = 0;
			int middle_elem = input[(s_index+e_index)/2];
			int index = (s_index+e_index)/2;
			//Going left
			while(index>=s_index){
				if(middle_elem == input[index]){
					middle_elem_freq++;
				}
				else{
					break;
				}
				index--;
			}
			//Going right
			index = (s_index+e_index)/2 + 1;
			while(index<=e_index){
				if(middle_elem == input[index]){
					middle_elem_freq++;
				}
				else{
					break;
				}
				index++;
			}
			//Take maximum of all three
			segment_tree[node] = max(max(segment_tree[left_child], segment_tree[right_child]), middle_elem_freq);
		}
	}
}

int seg_query(int node, int s_index, int e_index, int i, int j){
	if(i>e_index || j<s_index){
		return -1;
	}
	if(s_index>=i && e_index<=j){
		return segment_tree[node];
	}
	int left_ret = seg_query(2*node, s_index, (s_index+e_index)/2, i, j);
	int right_ret = seg_query(2*node + 1, (s_index+e_index)/2 + 1, e_index, i, j);
	if(left_ret==-1){
		return right_ret;
	}
	if(right_ret==-1){
		return left_ret;
	}

	if(input[(s_index+e_index)/2] != input[(s_index+e_index)/2 + 1]){
		return max(left_ret, right_ret);
	}
	else{
		int middle_elem_freq = 0;
		int middle_elem = input[(s_index+e_index)/2];
		int index = (s_index+e_index)/2;
		//Going left
		while(index>=i){
			if(middle_elem == input[index]){
				middle_elem_freq++;
			}
			else{
				break;
			}
			index--;
		}
		//Going right
		index = (s_index+e_index)/2 + 1;
		while(index<=j){
			if(middle_elem == input[index]){
				middle_elem_freq++;
			}
			else{
				break;
			}
			index++;
		}
		//Take maximum of all three
		return max(max(left_ret, right_ret), middle_elem_freq);
	}

}

int main(){
	int n,q,value,left,right;
	cin >> n;
	while(n){
		cin >> q;
		input.resize(n);
		for(int i=0;i<n;i++){
			cin >> value;
			input[i] = value;
		}
		//Construct segment tree out of input vector
		init_seg_tree(input);
#ifdef DEBUG
        int ts = segment_tree.size();
        for(int i=0;i<ts;i++){
            cout << segment_tree[i] << " ";
        }

#endif // DEBUG
		for(int i=0;i<q;i++){
			cin >> left >> right;
			cout << seg_query(1,0,n-1,left-1,right-1) << endl;
		}

		cin >> n;
	}
	return 0;
}
