#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

bool nest(vector<int> a, vector<int> b, int nr_dim){
	bool ret = true;
	for(int i=0;i<nr_dim;i++){
		if(a[i]>=b[i]){
			ret = false;
		}
	}
	return ret;
}

int main(){
	int nr_box, nr_dim;
	while(cin >> nr_box >> nr_dim){
		vector<vector<int> > boxes(nr_box);
		for(int i=0;i<nr_box;i++){
			vector<int> box(nr_dim);
			for(int j=0;j<nr_dim;j++){
				cin >> box[j];
			}
			sort(box.begin(),box.end());
			boxes[i] = box;
		}
	}
	
	
	return 0;
}