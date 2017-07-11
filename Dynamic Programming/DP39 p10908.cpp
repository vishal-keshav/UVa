#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

int T,M,N,Q;
int max_len;
int cx,cy;
vector<vector<char> > arr;

bool valid(int x, int y){
	if(x>=0 && y>=0 && x<M && y<N){
		return true;
	}
	return false;
}

bool square(int x1,int y1, int x2, int y2, char word){
	if(!valid(x1,y1) || !valid(x2,y2)){
		return false;
	}
	//First and last line
	for(int i=y1;i<=y2;i++){
		if(arr[x1][i]!=word){
			return false;
		}
		if(arr[x2][i]!=word){
			return false;
		}
	}
	//Side lines
	for(int i=x1;i<=x2;i++){
		if(arr[i][y1]!=word){
			return false;
		}
		if(arr[i][y2]!=word){
			return false;
		}
	}
	return true;
}

int max_square(int x, int y){
	int len;
	for(len = 1;len<max_len;len++){
		if(!square(x-len,y-len,x+len,y+len,arr[x][y])){
			break;
		}
	}
	return 2*len - 1;
}

int main(){
	cin >> T;
	while(T--){
		cin >> M >> N >> Q;
		max_len = max(M,N);
		arr.clear();
		arr.resize(M,vector<char>(N));
		for(int i=0;i<M;i++){
			for(int j=0;j<N;j++){
				cin >> arr[i][j];
			}
		}
		cout << M << " " << N << " " << Q << endl;
		for(int i=0;i<Q;i++){
			cin >> cx >> cy;
			cout << max_square(cx,cy) << endl;
		}
	}

	return 0;
}
