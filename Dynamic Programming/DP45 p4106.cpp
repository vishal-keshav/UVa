#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

int nr_oak,height;
int c,t,h,f;
vector<vector<int> > oak;
vector<vector<int> > DP;

int main(){
    //freopen("output.txt","w",stdout);
	cin >> c;
	while(c--){
		cin >> t >> h >> f;
		oak.clear();
		oak.resize(t, vector<int>(h+1,0));
		DP.clear();
		DP.resize(t, vector<int>(h+1,0));
		for(int i=0;i<t;i++){
			cin >> nr_oak;
			for(int j=0;j<nr_oak;j++){
				cin >> height;
				oak[i][height]++;
				DP[i][height]++;
			}
		}

		for(int i=height;i>0;i--){
			//Just traverse one step below
			for(int j=0;j<t;j++){
				DP[j][i-1] = max(DP[j][i-1],DP[j][i]+oak[j][i-1]);
			}
			//Move to each tree frorm each tree and decend f steps
			for(int j=0;j<t;j++){
				for(int k=0;k<t;k++){
					if(i>=f){
						DP[k][i-f] = max(DP[k][i-f],DP[j][i]+oak[k][i-f]);
					}
				}
			}
		}


		int ret = 0;
		for(int i=0;i<t;i++){
			ret = max(ret,DP[i][0]);
		}
		cout << ret << endl;
	}
	cin >> c;
	return 0;
}
