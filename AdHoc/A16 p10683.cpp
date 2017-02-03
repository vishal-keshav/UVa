#include <iostream>
#include <stdio.h>

using namespace std;

int main(){
	unsigned long long int input,time;
	long double fraction = 10000000.0/8640000.0;

	while(cin >> input){
        int zeros = 0;
		time = 0;
		time+=360000*(input/1000000);
		input = input%1000000;
		time+=6000*(input/10000);
		input = input%10000;
		time+=100*(input/100);
		input = input%100;
		time+=input;
        input = time*fraction;
        /*while(input){
            input = input/10;
            zeros++;
        }
        zeros = 6-zeros;
        for(int i=0;i<zeros;i++){
            cout << "0";
        }
		cout << (int)(time*fraction) << endl;*/
		printf("%07d\n", (int)(time*fraction));
	}
	return 0;
}
