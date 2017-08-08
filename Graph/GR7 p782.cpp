#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <string>

//#define DEBUG 1

using namespace std;

int T,h,w;
vector<string> contour;

int move_x[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int move_y[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

int maximum(int a, int b){
    return (a<b?b:a);
}

bool is_valid(int x, int y){
	if(x>=0 && y>=0 && x<h && y<w){
		return true;
	}
	return false;
}

/*Proposed algorithm
1. Search for the star
2. From that location, flood fill spaces and star with star
3. Apply boundry condition to convert star to hash
4. Convert star to spaces*/

void flood_fill_star(int i, int j){
	if(!is_valid(i,j)){
		return;
	}
	if(contour[i][j]==' '){
		contour[i][j] = '*';
		for(int i=0;i<8;i++){
			flood_fill_star(i+move_x[i], j+move_y[i]);
		}
	}
	return;
}

void apply_boundry(void){
	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
			if(contour[i][j]=='X'){
				//Convert closest * to #
			}
		}
	}
}

int main(){
	string temp;
	cin >> T;
	while(T--){
		contour.clear();
		w = 0;
		h = 0;
		getline(cin,temp);
		while(!(temp.length()!=0 && temp[0]=='_')){
			contour.push_back(temp);
			w = maximum(w,temp.length());
			h++;
			getline(cin,temp);
		}
		//fix the contour grid
		w++;
		for(int i=0;i<h;i++){
			string blanks(w-contour[i].length(),' ');
			contour[i].append(blanks);
		}
#ifdef DEBUG
		for(int i=0;i<h;i++){
			cout << contour[i] << endl;
		}
#endif
		for(int i=0;i<h;i++){
			for(int j=0;j<w;j++){
				if(contour[i][j]=='*'){
					contour[i][j] = ' ';
					flood_fill_star(i,j);
					break;//Can be optimized more
				}
			}
		}
		apply_boundry();
		for(int i=0;i<h;i++){
			for(int j=0;j<w;j++){
				if(contour[i][j]=='*'){
					contour[i][j] = ' ';
				}
			}
		}
		//Return answer
		for(int i=0;i<h;i++){
			cout << contour[i] << endl;
		}
		cout << temp << endl;
	}

	return 0;
}
