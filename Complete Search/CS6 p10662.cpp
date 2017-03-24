#include <iostream>

using namespace std;

#define INT_MAXIMUM 100000000

int travel[20][21];
int rest[20][21];
int hotel[20][21];

int main(){
	int T,R,H;
	int min_expense, min_t, min_r, min_h;
	while(cin >> T >> R >> H){
		for(int i=0;i<T;i++){
			for(int j=0;j<=R;j++){
				cin >> travel[i][j];
			}
		}
		for(int i=0;i<R;i++){
			for(int j=0;j<=H;j++){
				cin >> rest[i][j];
			}
		}
		for(int i=0;i<H;i++){
			for(int j=0;j<=T;j++){
				cin >> hotel[i][j];
			}
		}
		min_expense = INT_MAXIMUM;
		for(int i=0;i<T;i++){
			for(int j=0;j<R;j++){
				for(int k=0;k<H;k++){
					if(travel[i][j+1]==0 && rest[j][k+1]==0 && hotel[k][i+1]==0){
						if(min_expense > travel[i][0]+rest[j][0]+hotel[k][0]){
							min_expense = travel[i][0]+rest[j][0]+hotel[k][0];
							min_t = i;
							min_r = j;
							min_h = k;
						}
					}
				}
			}
		}
		if(min_expense!=INT_MAXIMUM){
			cout << min_t << " " << min_r << " " << min_h << ":" << min_expense<< endl;
		}
		else{
			cout << "Don't get married!" << endl;
			/*Seriously, never get married, otherwise freedom gone*/
		}
	}
	return 0;
}
