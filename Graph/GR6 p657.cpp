#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int w,h;
vector<string> picture;
vector<int> nr_dots;

int move_x[4] = {-1,0,0,1};
int move_y[4] = {0,-1,1,0};

bool is_valid(int x, int y){
	if(x>=0 && y>=0 && x<h && y<w){
		return true;
	}
	return false;
}

void flood_fill_dots(int x, int y){
	if(!is_valid(x,y)){
		return;
	}
	if(picture[x][y]!='X'){
		return;
	}
	picture[x][y] = '*';
	for(int i=0;i<4;i++){
		flood_fill_dots(x+move_x[i], y+move_y[i]);
	}
	return;
}

int flood_fill(int x, int y){
	//flood fills * and retun number of dots group X
	if(!is_valid(x,y)){
		return 0;
	}
	if(picture[x][y]=='.'){
		return 0;
	}
	int ret = 0;
	if(picture[x][y]=='X'){
		flood_fill_dots(x,y);
		ret++;
	}
	picture[x][y] = '.';
	for(int i=0;i<4;i++){
		ret+=flood_fill(x+move_x[i],y+move_y[i]);
	}
	return ret;
}

int compute_dots(void){
	int ret = 0;
	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
			if(picture[i][j]=='*' || picture[i][j]=='X'){
				ret = flood_fill(i,j);
				nr_dots.push_back(ret);
			}
		}
	}
	return nr_dots.size();
}

int main(){
	string temp;
	int nr_case=1;
	int nr_dice;
	cin >> w >> h;
	while(w+h){
		picture.clear();
		for(int i=0;i<h;i++){
			cin >> temp;
			picture.push_back(temp);
		}
		nr_dots.clear();
		nr_dice = compute_dots();
		sort(nr_dots.begin(),nr_dots.end());
		cout << "Throw " << nr_case << endl;
		for(int i=0;i<nr_dice-1;i++){
			cout << nr_dots[i] << " ";
		}
		cout << nr_dots[nr_dice-1] << endl << endl;
		cin >> w >> h;
		nr_case++;
	}

	return 0;
}
