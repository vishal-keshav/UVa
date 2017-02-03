#include <iostream>
#include <string>

using namespace std;

void swap_num(int *a, int *b){
    int temp = (*a);
    (*a) = (*b);
    (*b) = temp;
}

int main(){
	int W,H,N;
	int X1,Y1,X2,Y2;
	while(cin >> W >> H >> N && (W+H+N)){
		int count_space = 0;
		int **mat = new int*[W+1];
		for(int i=0;i<=W;i++){
			mat[i] = new int[H+1];
			for(int j=0;j<=H;j++){
				mat[i][j] = 0;
			}
		}
		for(int i=0;i<N;i++){
			cin >> X1 >> Y1 >> X2 >> Y2;
			if(X1>X2){
                swap_num(&X1,&X2);
			}
			if(Y1>Y2){
                swap_num(&Y1,&Y2);
			}
			for(int x=X1;x<=X2;x++){
				for(int y=Y1;y<=Y2;y++){
					if(mat[x][y]==0){
						mat[x][y] = 1;
						count_space++;
					}
				}
			}
		}
		if(W*H-count_space == 0){
            cout << "There is no empty spots." << endl;
		}
		else if(W*H-count_space == 1){
            cout << "There is one empty spot." << endl;
		}
		else{
            cout << "There are " << W*H-count_space <<" empty spots." << endl;
		}
	}
	return 0;
}
