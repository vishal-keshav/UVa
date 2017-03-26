#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

int N,H;

void print_binary(int index, int ones, string binary){
	if(index>=N){
        if(ones == H){
            cout << binary << endl;
        }
        return;
	}
	else{
        //cout << binary << " "<< ones << " " << index << endl;
		if(ones >H){
			return;
		}
        //Dont put anything
		print_binary(index+1, ones,binary);

		//Put one at this index
		binary[index] = '1';
		print_binary(index+1, ones+1,binary);
		binary[index] = '0';

	}
}

int main(){
	int T;
	cin >> T;
	while(T--){
		cin >> N >> H;
		//binary.resize(N,'0');
		string binary(N, '0');
		print_binary(0,0,binary);
		if(T){
            cout << endl;
		}
	}
	return 0;
}
