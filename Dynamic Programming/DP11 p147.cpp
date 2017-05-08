#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

long long int denomination[11] = {1,2,4,10,20,40,100,200,400,1000,2000};

long long int get_digits(long int n){
	long long int ret = 0;
	while(n){
		ret++;
		n=n/10;
	}
	return ret;
}

int main(){
    //freopen("output.txt","w",stdout);
	double input;
	long long int converted_input;
	cin >> input;
	while(input){
		converted_input = (long long int)(100*input)/(long long int)5;
		//cout << (long long int)(input*100) << endl;
		//cout << converted_input << endl;

		vector<long long int> DP(converted_input+1,0);
		DP[0] = 1;
		//Filling
        for(long long int i=0;i<11;i++){
            for(long long int j=0;j<=converted_input;j++){
                if(denomination[i]+j>converted_input){
                    break;
                }
                DP[denomination[i]+j]+=DP[j];
            }
        }
		//cout << input << " " << DP[converted_input] << endl;
        printf("%6.2f%17lld\n", input, DP[converted_input]);
		cin >> input;
	}

	return 0;
}
