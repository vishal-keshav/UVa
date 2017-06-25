#include <iostream>

using namespace std;

bool dp[20][201];
int garment[20][21];

int main(){
	int T,M,C,K,index;
	cin >> T;
	while(T--){
		cin >> M >> C;
		for(int i=0;i<C;i++){
			cin >> garment[i][0];
			K = garment[i][0];
			for(int j=1;j<=K;j++){
				cin >> garment[i][j];
			}
		}
		//Setting dp memory
		for(int i=0;i<20;i++){
			for(int j=1;j<=M;j++){
				dp[i][j] = false;
			}
		}
		//initialize dp
		for(int i=1;i<=garment[0][0];i++){
			dp[0][garment[0][i]] = true;
		}
		//filling rest of the dp
		for(int i=1;i<C;i++){
			for(int j=1;j<=garment[i][0];j++){
				for(int k=1;k<=M;k++){
					if(dp[i-1][k] && (k+garment[i][j] <= M)){
						dp[i][k+garment[i][j]] = true;
					}
				}
			}
		}
		//search for the highest index
		index = M+1;
		for(int i=1;i<=M;i++){
			if(dp[C-1][i]){
				index = i;
			}
		}
		if(index<=M){
			cout << index << endl;
		}
		else{
			cout << "no solution" << endl;
		}
	}
	return(0);
}
