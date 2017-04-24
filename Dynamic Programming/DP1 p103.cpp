#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

//#define DEBUG 1

struct box_elem{
	vector<int> box;
	int index;
};

bool nest(vector<int> a, vector<int> b){
	bool ret = true;
	int nr_dim = a.size();
	for(int i=0;i<nr_dim;i++){
		if(a[i]>b[i]){
			ret = false;
		}
	}
	return ret;
}

bool comp(struct box_elem a, struct box_elem b){
	return nest(a.box, b.box);
}

int main(){
    //freopen("output.txt","w",stdout);
	int nr_box, nr_dim;
	while(cin >> nr_box >> nr_dim){
		vector<struct box_elem> boxes(nr_box);
		for(int i=0;i<nr_box;i++){
			vector<int> box(nr_dim);
			for(int j=0;j<nr_dim;j++){
				cin >> box[j];
			}
			sort(box.begin(),box.end());
			struct box_elem temp;
			temp.box = box;
			temp.index = i+1;
			boxes[i] = temp;
		}
		sort(boxes.begin(),boxes.end(), comp);
#ifdef DEBUG
        for(int i=0;i<nr_box;i++){
            cout << boxes[i].box[0] << endl;
        }
#endif // DEBUG
		vector<int> lis(nr_box);
		vector<int> lis_parent(nr_box);
		for(int i=0;i<nr_box;i++){
			lis[i] = 1;
			lis_parent[i] = i;
		}
		int max_lis = 1;
		int max_idx = 0;
		for(int i=1;i<nr_box;i++){
			for(int j=i-1;j>=0;j--){
				if(comp(boxes[j],boxes[i])){
					if(lis[i] < 1+lis[j]){
						lis[i] = 1+lis[j];
						if(lis[i]>max_lis){
							max_lis = lis[i];
							max_idx = i;
						}
						lis_parent[i] = j;
					}
				}
			}
		}
#ifdef DEBUG
        for(int i=0;i<nr_box;i++){
            cout << lis_parent[i] << " ";
        }
#endif // DEBUG
		cout << max_lis << endl;
        vector<int> ret;
        while(lis_parent[max_idx]!=max_idx){
			//cout << boxes[max_idx].index << " ";
			ret.push_back(boxes[max_idx].index);
			max_idx = lis_parent[max_idx];
		}
		//cout << boxes[max_idx].index << endl;
		ret.push_back(boxes[max_idx].index);
		for(int i=ret.size()-1;i>0;i--){
            cout << ret[i] << " ";
		}
		cout << ret[0] << endl;
	}


	return 0;
}
