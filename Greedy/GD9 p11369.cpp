#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

bool comp(int a, int b){
    return(a>b);
}

int main(){
	int T,N,discount;
	cin >> T;
	while(T--){
		cin >> N;
		vector<int> price(N);
		for(int i=0;i<N;i++){
			cin >> price[i];
		}
		sort(price.begin(), price.end(),comp);
		discount = 0;
		for(int i=2;i<N;i+=3){
			discount+=price[i];
		}
		cout << discount << endl;
	}
	return 0;
}
