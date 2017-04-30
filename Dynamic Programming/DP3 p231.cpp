#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
	int temp,nr_test=1,nr_missiles;
	cin >> temp;
	while(temp!=-1){
		vector<int> missiles;
		missiles.push_back(temp);
		while(cin >> temp && temp!=-1){
			missiles.push_back(temp);
		}
		nr_missiles = missiles.size();
		//Process
		cout << "Test #" << nr_test << ":" << endl;
		vector<int> lds(nr_missiles,1);
		int max_intercepts = 1;
		for(int i=1;i<nr_missiles;i++){
			for(int j=0;j<i;j++){
				if(missiles[j] >= missiles[i]){
					if(lds[i]<1+lds[j]){
						lds[i] = 1+lds[j];
						if(lds[i] > max_intercepts){
							max_intercepts = lds[i];
						}
					}
				}
			}
		}
		cout << "  maximum possible interceptions: " << max_intercepts << endl;
		//New set of inputs
		cin >> temp;
		if(temp!=-1){
			cout << endl;
		}
		nr_test++;
	}

	return 0;
}
