#include <iostream>
#include <stdio.h>
#include <cstring>

using namespace std;

string input;


int main(){
	//string input;
	int back_iter, forward_iter;

	while(getline (cin,input)){
		//Reverse and print
		forward_iter = 0;
		for(int i=0;i<input.size();i++){
            if(input[i]!=' '){
                forward_iter = 0;
                while(input[i+forward_iter]!=' ' && i+forward_iter < input.size()){
                    forward_iter++;
                }
                for(int j=forward_iter-1;j>=0;j--){
                    cout << input[i+j];
                }
                i+= forward_iter-1;
            }
            else{
                cout << input[i];
            }
		}
		cout << endl;
	}
	return 0;
}
