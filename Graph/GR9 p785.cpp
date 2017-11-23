#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <string>
#include <cstddef>

using namespace std;

int T,h,w;
vector<string> contour;

int move_x[4] = {-1, 0, 0, 1};
int move_y[4] = {0, -1, 1, 0};

int maximum(int a, int b){
    return (a<b?b:a);
}

bool is_valid(int x, int y){
	if(x>=0 && y>=0 && x<h && y<w){
		return true;
	}
	return false;
}

void flood_fill_marker(int i, int j, char marker){
	if(!is_valid(i,j)){
		return;
	}
	if(contour[i][j]==' '){
		contour[i][j] = marker;
		for(int k=0;k<4;k++){
			flood_fill_marker(i+move_x[k], j+move_y[k],marker);
		}
	}
	return;
}

void trim_whitespaces(void){
	size_t index;
	for(int i=0;i<h;i++){
		index = contour[i].find_last_not_of(" ");
		contour[i] = contour[i].substr(0,index+1);
	}
}


int main(){
    //freopen("output.txt","w",stdout);
	string temp;
  char marker;
	//cin >> T;
	//cin.ignore();
	while(1){
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

		w++;
		for(int i=0;i<h;i++){
			string blanks(w-contour[i].length(),' ');
			contour[i].append(blanks);
		}

		for(int i=0;i<h;i++){
			for(int j=0;j<w;j++){
				if(!(contour[i][j]==' ' || contour[i][j]=='_' || contour[i][j]=='X')){
          marker = contour[i][j];
          contour[i][j] = ' ';
          flood_fill_marker(i,j,marker);
        }
			}
		}

		trim_whitespaces();
		for(int i=0;i<h;i++){
			cout << contour[i] << endl;
		}
		cout << temp << endl;
	}

	return 0;
}
