#include <iostream>
#include <stdio.h>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int main(){
	int n,orig_loc,target_loc;
	cin >> n;
	while(n){
		vector<int> before(2*n, 0);
		vector<int> after(2*n, 0);
		map<int, int> location_hash;
		int nr_location = 0;
		for(int i=0;i<n;i++){
			cin >> orig_loc >> target_loc;
			if(location_hash.count(orig_loc)==0){
				location_hash[orig_loc] = nr_location;
				nr_location++;
			}
			if(location_hash.count(target_loc)==0){
				location_hash[target_loc] = nr_location;
				nr_location++;
			}
			before[location_hash[orig_loc]]++;
			after[location_hash[target_loc]]++;
		}
		bool success = true;
		for(int i=0;i<nr_location;i++){
			if(after[i]!=before[i]){
				success = false;
				break;
			}
		}
		if(success){
			cout << "YES" << endl;
		}
		else{
			cout << "NO" << endl;
		}
		cin >> n;
	}
	return 0;
}