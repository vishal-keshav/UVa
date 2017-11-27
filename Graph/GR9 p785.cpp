#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
#include <cstddef>

using namespace std;

int T,h,w;
vector<string> contour;
int done[40][100] = {};
char buffer[1001];

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
    done[i][j] = 1;
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
  char boundry;
	//cin >> T;
	//cin.ignore();
	while( gets(buffer) ){
		contour.clear();
		w = 0;
		h = 0;
		//getline(cin,temp);
		while(!(buffer.length()!=0 && buffer[0]=='_')){
			contour.push_back(buffer);
			w = maximum(w,buffer.length());
			h++;
			gets(buffer);
		}

		w++;
		for(int i=0;i<h;i++){
			string blanks(w-contour[i].length(),' ');
			contour[i].append(blanks);
		}

    //Find boundry
    bool break_case = false;
    for(int i=0;i<h;i++){
      for(int j=0;j<w;j++){
        if(contour[i][j]!=' '){
          boundry = contour[i][j];
          break_case = true;
          break;
        }
      }
      if(break_case){
        break;
      }
    }

		for(int i=0;i<h;i++){
			for(int j=0;j<w;j++){
				if(!(contour[i][j]==' ' || contour[i][j]=='_' || contour[i][j]==boundry)){
          if(done[i][j]){
            continue;
          }
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
    puts(buffer);
	}

	return 0;
}
