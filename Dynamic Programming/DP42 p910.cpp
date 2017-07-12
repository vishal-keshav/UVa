#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

struct node{
	int right,wrong;
	bool is_special;
};

int n,m;
char S,E1,E2,sp;
vector<struct node> carpet;
vector<vector<int> > DP;

int main(){
	while(cin >> n){
		carpet.clear();
		carpet.resize(n);
		for(int i=0;i<n;i++){
			cin >> S >> E1 >> E2 >> sp;
			carpet[S-'A'].right = E1 - 'A';
			carpet[S-'A'].wrong = E2 - 'A';
			if(sp=='x'){
				carpet[S-'A'].is_special = true;
			}
			else{
				carpet[S-'A'].is_special = false;
			}
		}
		cin >> m;
		DP.clear();
		DP.resize(n,vector<int>(m+1,0));
		DP[0][0] = 1;
		for(int i=0;i<m;i++){
			for(int j=0;j<n;j++){
				if(DP[j][i]!=0){
					DP[carpet[j].right][i+1]+=DP[j][i];
					DP[carpet[j].wrong][i+1]+=DP[j][i];
				}
			}
		}
		int ret = 0;
		for(int i=0;i<n;i++){
			if(carpet[i].is_special){
				ret+=DP[i][m];
			}
		}
		cout << ret << endl;
	}
	return 0;
}
