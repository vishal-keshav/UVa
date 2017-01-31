#include <iostream>
#include <cstring>
#include <stdio.h>

using namespace std;

int mat[3][3] = {{0,0,0},
				{0,0,0},
				{0,0,0}};

char line[4];

bool process(void){
	/*
	1. count(X)==count(O) or count(X) == count(O)+1
	2. nr_wins(X)<=1 && nr_wins(O)<=1 && nr_wins(X)!=nr_wins(O)
	*/
	int sum =0,win_sum_row,win_sum_column,win_dig_1=0,win_dig_2=0;
	int nr_wins_X=0,nr_wins_O=0;
	for(int i=0;i<3;i++){
		win_sum_row = 0;
		win_sum_column = 0;
		win_dig_1+=mat[i][i];
		win_dig_2+=mat[i][2-i];
		for(int j=0;j<3;j++){
			sum+=mat[i][j];
			win_sum_row+=mat[i][j];
			win_sum_column+=mat[j][i];
		}
		if(win_sum_row == 3){
			nr_wins_X++;
		}
		else if(win_sum_row == -3){
			nr_wins_O++;
		}
		if(win_sum_column == 3){
			nr_wins_X++;
		}
		else if(win_sum_column == -3){
			nr_wins_O++;
		}
	}
	if(win_dig_1 == 3){
		nr_wins_X++;
	}
	else if(win_dig_1 == -3){
		nr_wins_O++;
	}
	if(win_dig_2 == 3){
		nr_wins_X++;
	}
	else if(win_dig_2 == -3){
		nr_wins_O++;
	}
	if(!(sum==0 || sum==1)){
		return false;
	}
	if(nr_wins_X<=1 && nr_wins_O<=1 && nr_wins_X!=nr_wins_O){
		return true;
	}
	return false;
}

int main(){
	int T;
	cin >> T;
	cin.ignore();
	while(T--){
		for(int i=0;i<3;i++){
			gets(line);
			for(int j=0;j<3;j++){
				if(line[j] == '.'){
					mat[i][j] = 0;
				}
				else if(line[j] == 'X'){
					mat[i][j] = 1;
				}
				else{
					mat[i][j] = -1;
				}
			}
		}
		if(process()){
			cout << "yes" << endl;
		}
		else{
			cout << "no" << endl;
		}
		/*for(int i=0;i<3;i++){
			for(int j=0;j<3;j++){
				cout << mat[i][j] << " ";
			}
			cout << endl;
		}*/
		if(T!=0){
			gets(line);
		}
	}
	return 0;
}
