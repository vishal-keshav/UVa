#include <iostream>
#include <cstring>
#include <stdio.h>

using namespace std;

int mat[3][3] = {{0,0,0},
				{0,0,0},
				{0,0,0}};

char line[4];

void win_inc(int win_value,int *X, int *Y){
	if(win_value == 3){
		(*X)++;
	}
	if(win_value == -3){
		(*Y)++;
	}
}

bool process(void){

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
		win_inc(win_sum_row,&nr_wins_X,&nr_wins_O);
		win_inc(win_sum_column,&nr_wins_X,&nr_wins_O);
	}
	if(!(sum==0 || sum==1)){
		return false;
	}
	win_inc(win_dig_1,&nr_wins_X,&nr_wins_O);
	win_inc(win_dig_2,&nr_wins_X,&nr_wins_O);

	if(nr_wins_O==1 && sum==1){
        return false;
	}
	if(nr_wins_X==1 && sum==0){
        return false;
	}

	if(nr_wins_X*nr_wins_O == 0){
		return true;
	}
	return false;
}

int main(){
    //freopen("output.txt","w",stdout);
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
		if(T!=0){
			gets(line);
		}
	}
	return 0;
}
