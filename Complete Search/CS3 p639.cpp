#include <iostream>
#include <algorithm>

using namespace std;

int max_rooks=0;
int N;
int x[16] = {0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3};
int y[16] = {0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3};

void init(void){
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			x[i*N+j] = i;
			y[i*N+j] = j;
		}
	}
}

char board[4][4];

bool can_place(int pos){
	if(pos==N*N){
		return true;
	}
	if(board[x[pos]][y[pos]]=='X'){
		return false;
	}
	for(int i = x[pos]-1;i>=0;i--){
		if(board[i][y[pos]]=='X'){
			break;
		}
		if(board[i][y[pos]]=='O'){
			return false;
		}
	}
	for(int j = y[pos]-1;j>=0;j--){
		if(board[x[pos]][j]=='X'){
			break;
		}
		if(board[x[pos]][j]=='O'){
			return false;
		}
	}
	return true;
}

void find_max_placing(int pos, int rooks){
	//Base case
	if(pos==N*N){
		max_rooks = max(max_rooks,rooks-1);
		return;
	}
	else{
		for(int i=pos+1;i<=N*N;i++){
			if(can_place(pos)){
				board[x[pos]][y[pos]] = 'O';
				find_max_placing(i, rooks+1);
				board[x[pos]][y[pos]] = '.';
			}
		}
		return;
	}
}

int main(){
	cin >> N;
	while(N){
		init();
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				cin >> board[i][j];
			}
		}
		for(int i=0;i<=N*N;i++){
			if(board[x[i]][y[i]]!='X'){
				find_max_placing(i,1);
			}
		}
		cout << max_rooks << endl;
		max_rooks = 0;
		cin >> N;
	}
	return 0;
}
