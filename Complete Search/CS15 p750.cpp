#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

vector<int> pos;
int nr_case;
int R, C;

int absolute(int n){
    if(n>0){
        return n;
    }
    else{
        return (0-n);
    }
}

bool valid(int row1, int col1, int row2, int col2){
	if(row1==row2 || absolute(row1-row2)==absolute(col1-col2)){
		return false;
	}
	else{
		return true;
	}
}

bool valid_placement(int row, int col){
	for(int i=1;i<col;i++){
		if(!valid(pos[i],i,row,col)){
			return false;
		}
	}
	return true;
}

void place_queens(int col){
	//Base case
	if(col>=9){
		if(nr_case<=9){
			cout << " " << nr_case <<"      ";
		}
		else{
			cout << nr_case <<"      ";
		}
		for(int i=1;i<8;i++){
			cout << pos[i] << " ";
		}
		cout << pos[8] << endl;
		nr_case++;
	}
	//Main case
	else{
		if(pos[col]!=-1){
			if(valid_placement(pos[col],col)){
				place_queens(col+1);
			}
			else{
				return;
			}
		}
		else{
			//Try all possibilities
			for(int i=1;i<=8;i++){
				if(valid_placement(i,col)){
					pos[col] = i;
					place_queens(col+1);
					pos[col] = -1;
				}
			}
		}
	}
}

int main(){
	int T;
	cin >> T;
	while(T--){
		cout << "SOLN       COLUMN"<< endl;
		cout << " #      1 2 3 4 5 6 7 8"<< endl << endl;
		pos.clear();
		pos.resize(9,-1);
		nr_case=1;
		cin >> R>>C;
		pos[C] = R;
		place_queens(1);
		if(T){
            cout << endl;
		}
	}
	return 0;
}
