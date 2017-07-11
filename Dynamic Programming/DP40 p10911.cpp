#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <string>
#include <math.h>
#include <iomanip>

#define INT_MAXIMUM 1000000

using namespace std;

struct pos{
	int x,y;
};

int N,bitmap,nr_case;
string name;
vector<struct pos> s_pos;
vector<vector<double> > dist;
vector<double> DP;

double calc_dist(int i, int j){
	double ret = 0;
	ret+=(double)((s_pos[i].x-s_pos[j].x)*(s_pos[i].x-s_pos[j].x));
	ret+=(double)((s_pos[i].y-s_pos[j].y)*(s_pos[i].y-s_pos[j].y));
	return sqrt(ret);
}

int nr_bits(int num){
	return __builtin_popcount(num);
}

int main(){
	cin >> N;
	nr_case = 1;
	while(N){
		s_pos.clear();
		s_pos.resize(2*N);
		for(int i=0;i<2*N;i++){
			cin >> name;
			cin >> s_pos[i].x >> s_pos[i].y;
		}
		dist.clear();
		dist.resize(2*N,vector<double>(2*N,0));
		for(int i=0;i<2*N;i++){
			for(int j=0;j<2*N;j++){
				dist[i][j] = calc_dist(i,j);
			}
		}
		bitmap = pow(2,2*N);
		DP.clear();
		DP.resize(bitmap,INT_MAXIMUM);
		DP[0] = 0;
		for(int i=1;i<bitmap;i++){
			if(nr_bits(i)%2!=0){
				continue;
			}
			//Search for two set bits to unset it
			for(int k=0;k<2*N;k++){
				if(i & (1<<k)){
					for(int l=k+1;l<2*N;l++){
						if(i & (1<<l)){
							DP[i] = min(DP[i],dist[k][l]+DP[(i & ~(1<<k)) & ~(1<<l)]);
						}
					}
				}
			}
		}
		cout << fixed;
		cout << "Case " << nr_case << ": " << setprecision(2) << DP[bitmap-1] << endl;
		cin >> N;
		nr_case++;
	}
	return 0;
}
