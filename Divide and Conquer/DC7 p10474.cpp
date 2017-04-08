#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
	int N,Q,marble_nr,nr_case=1;
	cin >> N >> Q;
	while(N || Q){
		vector<int> marbles(N);
		vector<int>::iterator iter;
		for(int i=0;i<N;i++){
			cin >> marbles[i];
		}
		sort(marbles.begin(), marbles.end());
		cout << "CASE# " << nr_case << ":" << endl;
		for(int i=0;i<Q;i++){
			cin >> marble_nr;
			iter = lower_bound(marbles.begin(),marbles.end(),marble_nr);
			if(iter==marbles.end() || (*iter)!=marble_nr){
				cout << marble_nr << " not found" << endl;
			}
			else{
				cout << marble_nr << " found at " << iter - marbles.begin() + 1 << endl;
			}
		}
		cin >> N >> Q;
		nr_case++;
	}

	return 0;
}
