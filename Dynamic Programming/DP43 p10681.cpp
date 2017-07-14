#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

int C,L;
int S,E,D;
vector<vector<bool> > link;
vector<vector<bool> > DP;

int main(){
	int c1, c2;
	cin >> C >> L;
	while(C+L){
        link.clear();
        link.resize(C,vector<bool>(C,false));
        for(int i=0;i<L;i++){
            cin >> c1 >> c2;
            link[c1-1][c2-1] = true;
            link[c2-1][c1-1] = true;
        }
        cin >> S >> E >> D;
        DP.clear();
        DP.resize(C,vector<bool>(D+1,false));
        DP[S-1][0] = true;
        for(int i=1;i<=D;i++){
            for(int j=0;j<C;j++){
                if(DP[j][i-1]){
                    for(int k=0;k<C;k++){
                        if(k!=j && link[j][k]){
                            DP[k][i] = true;
                        }
                    }
                }
            }
        }
        if(DP[E-1][D]){
            cout << "Yes, Teobaldo can travel." << endl;
        }
        else{
            cout  << "No, Teobaldo can not travel." << endl;
        }
        cin >> C >> L;
	}
	return 0;
}
