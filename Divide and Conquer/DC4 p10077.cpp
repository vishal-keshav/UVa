#include <iostream>
#include <stdio.h>
#include <vector>
#include <math.h>

using namespace std;

double fraction(int n, int d){
	return ((double)n/(double)d);
}

int main(){
	int left_num, left_deno, right_num, right_deno, num, deno;
	int temp_num, temp_deno;
	cin >> num >> deno;
	while(!(num==1 && deno==1)){
		left_num = 0;
		left_deno = 1;
		right_num = 1;
		right_deno = 0;
		temp_num = 1;
		temp_deno = 1;
		while(!(temp_num==num && temp_deno==deno)){
			if(fraction(num,deno) < fraction(temp_num, temp_deno)){
				//Go left
				cout << "L";
				right_num = temp_num;
				right_deno = temp_deno;
				temp_num = left_num + right_num;
				temp_deno = left_deno + right_deno;
			}
			else{
				//Go right
				cout << "R";
				left_num = temp_num;
				left_deno = temp_deno;
				temp_num = left_num + right_num;
				temp_deno = left_deno + right_deno;
			}
			/*if(temp_num==num && temp_deno==deno){

                break;
			}*/
		}
		cout << endl;
		cin >> num >> deno;
	}
	return 0;
}
