#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <string>

#define DEBUG 1

using namespace std;

int T;
vector<string> contour;

int maximum(int a, int b){
    return (a<b?b:a);
}

int main(){
	string temp;
	int h,w;
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
	}

	return 0;
}
