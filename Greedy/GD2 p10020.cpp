#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

struct segment{
	int left,right;
};

bool comp_start(struct segment s1, struct segment s2){
	return (s1.left < s2.left);
}

int main(){
	int T,M,left,right;
	cin >> T;
	while(T--){
		cin >> M;
		cin >> left >> right;
		vector<struct segment> input_segments;
		while(left || right){
			struct segment temp;
			temp.left = left;
			temp.right = right;
			input_segments.push_back(temp);
			cin >> left >> right;
		}
		//Sort w.r.t interval starting
		sort(input_segments.begin(),input_segments.end(),comp_start);
		int limit = 0;
		bool found = true;
		int index = 0;
		int nr_segments = input_segments.size();
		vector<struct segment> sol;
		int covered = 0;
		struct segment max_elem;
		int max_right;
		while(index < nr_segments && covered < M){
			max_right = -1;
			while(index < nr_segments && input_segments[index].left <= covered){
				if(max_right < input_segments[index].right){
					max_right = input_segments[index].right;
					max_elem = input_segments[index];
				}
				index++;
			}
			//Check if feasible to go further, otherwise prune
			if(max_right==-1 || max_right < covered){
				found = false;
				break;
			}
			else{
				//Solution found, update covered
				covered = max_right;
				sol.push_back(max_elem);
			}
		}
		if(!found || max_right < M){
			cout << "0" << endl;
		}
		else{
			cout << sol.size() << endl;
			for(vector<struct segment>::iterator it=sol.begin();it!=sol.end();it++){
				cout << (*it).left << " " <<(*it).right << endl;
			}
		}
		if(T){
			cout << endl;
		}
	}
	return 0;
}
