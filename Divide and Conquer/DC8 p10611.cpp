#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
	int N,Q;
	cin >> N;
	vector<long int> lady_chimps(N);
	vector<long int>::iterator high;
	for(int i=0;i<N;i++){
		cin >> lady_chimps[i];
	}
	cin >> Q;
	bool left_found,right_found;
	int height, left_height, right_height;
	for(int i=0;i<Q;i++){
		cin >> height;
		left_found = false;
		right_found = false;
		high = upper_bound(lady_chimps.begin(),lady_chimps.end(),height);
		if(high==lady_chimps.end()){
			//Start from end to find it
			for(int i=N-1;i>=0;i--){
				if(lady_chimps[i]<height){
					left_found = true;
					left_height = lady_chimps[i];
					break;
				}
			}
		}
		else{
			right_found = true;
			right_height = (*high);
			for(int i=high-lady_chimps.begin();i>=0;i--){
				if(lady_chimps[i]<height){
					left_found = true;
					left_height = lady_chimps[i];
					break;
				}
			}
		}
		if(left_found){
			cout << left_height << " ";
		}
		else{
			cout << "X ";
		}
		if(right_found){
			cout << right_height << endl;
		}
		else{
			cout << "X" << endl;
		}
	}
	return 0;
}
