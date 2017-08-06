#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int w,h;
vector<string> picture;
vector<int> nr_dots;

bool is_valid(int x, int y){
	if(x>=0 && y>=0 && x<h && y<w){
		return true;
	}
	return false;
}

int flood_fill(int x, int j){
	//flood fills * and retun number of dots group X
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
	
}

int main(){
	string temp;
	int nr_case=1;
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
		cout << nr_dots[nr_dice-1] << endl;
	}
	
	return 0;
}