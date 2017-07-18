#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

int nr_oak,height;
int c,t,h,f;
int temp;
vector<vector<int> > oak;
vector<int> DP;

int main(){
    //freopen("output.txt","w",stdout);
	cin >> c;
	while(c--){
		cin >> t >> h >> f;
		oak.clear();
		oak.resize(t, vector<int>(h+1,0));
		DP.clear();
		DP.resize(h+1,0);
		for(int i=0;i<t;i++){
			cin >> nr_oak;
			for(int j=0;j<nr_oak;j++){
				cin >> height;
				oak[i][height]++;
				DP[height]++;
			}
		}

		for(int i=h;i>0;i--){
			//Move to each tree frorm each tree and decend f steps
			for(int j=0;j<t;j++){
				//Update in oak itself
				temp = 0;
				if(i-1+f <= h){
					temp = DP[i-1+f];
				}
				oak[j][i-1]+= max(oak[j][i],temp);
				DP[i-1] = max(DP[i-1],oak[j][i-1]);
			}
		}
		cout << DP[0] << endl;
	}
	cin >> c;
	return 0;
}
