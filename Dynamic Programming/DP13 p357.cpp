#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

int denom[5] = {1,5,10,25,50};
vector<long long int> ans(30001,0);

void init(void){
	ans[0] = 1;
	for(int i=0;i<5;i++){
		for(int j=1;j<=30000;j++){
			if(j-denom[i]>=0){
				ans[j]+=ans[j-denom[i]];
			}
		}
	}
}

int main(){
	int input;
	init();
	while(cin >> input){
		if(ans[input]==1){
			cout << "There is only " << ans[input] << " way to produce " << input << " cents change." << endl;
		}
		else{
			cout << "There are " << ans[input] << " ways to produce " << input << " cents change." << endl;
		}
	}

	return 0;
}
