#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <sstream>

//#define DEBUG 1

using namespace std;

int T,row,col;
vector<string> plot;
int r,c;
string line;

int move_x[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int move_y[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

bool is_valid(int x, int y, int R, int C){
	if(x>=0 && y>=0 && x<R && y<C){
		return true;
	}
	return false;
}

int nr_water(int r, int c, int R, int C){
	if(!is_valid(r,c,R,C)){
		return 0;
	}
	if(plot[r][c]!='W'){
		return 0;
	}
	int ret = 1;
	plot[r][c] = 'l';
	for(int i=0; i<8; i++){
		ret+=nr_water(r+move_x[i],c+move_y[i],R,C);
	}
	//plot[r][c] = 'W';
	return ret;
}

void fill_water(int r, int c, int R, int C){
    if(!is_valid(r,c,R,C)){
		return;
	}
	if(plot[r][c]!='l'){
		return;
	}
	plot[r][c] = 'W';
	for(int i=0; i<8; i++){
		fill_water(r+move_x[i],c+move_y[i],R,C);
	}
	return;
}

int main(){
    //freopen("output.txt","w",stdout);
	cin >> T;
	cin.ignore();
	bool check = false;
	while(getline(cin,line)){
		if(line.length()==0){
			plot.clear();
			if(check){
                cout << endl;
			}
			else{
                check = true;
			}
			continue;
		}
		if(line[0]=='L' || line[0]=='W'){
			plot.push_back(line);
		}
		else{
			stringstream ss(line);
			ss >> row;
			ss >> col;
#ifdef DEBUG
			cout << plot.size() << " " << plot[0].length() << " " << row << " " << col << endl;
			for(int i=0;i<plot.size();i++){
				for(int j=0;j<plot[0].length();j++){
					cout << plot[i][j] << " ";
				}
				cout << endl;
			}
#endif
			cout << nr_water(row-1, col-1,plot.size(), plot[0].length()) << endl;
			fill_water(row-1, col-1, plot.size(), plot[0].length());
		}
	}
	return 0;
}
