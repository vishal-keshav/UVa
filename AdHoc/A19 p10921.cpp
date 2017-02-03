#include <iostream>
#include <string>
#include<stdio.h>

using namespace std;

int conversion[26] = {2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,7,7,7,7,8,8,8,9,9,9,9};

int main(){
	string input;
	while(getline(cin, input)){
		for(int i=0;i<input.length();i++){
			if(input[i]=='0' || input[i]=='1' || input[i]=='-'){
				cout << input[i];
			}
			else{
				cout << conversion[(int)input[i]-'A'];
			}
		}
		cout << endl;
	}
	return 0;
}
