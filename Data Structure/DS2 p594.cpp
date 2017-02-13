#include <iostream>
#include <bitset>
#include <string>
#include <algorithm>

using namespace std;

int main(){
	long int N;
	string bit_to_string;
	while(cin >> N){
        bitset<32> num_to_bit(N);
        bit_to_string = num_to_bit.to_string();
        //Reversal technique
        for(int i=0;i<32;i+=8){
            reverse(bit_to_string.begin()+i, bit_to_string.begin()+i+8);
        }
        reverse(bit_to_string.begin(),bit_to_string.end());

        bitset<32> result(bit_to_string);
        cout << N << " converts to "<<(long int)(result.to_ulong()) << endl;
	}
	return 0;
}
