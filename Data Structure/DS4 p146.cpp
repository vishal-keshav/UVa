#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main(){
	string input;
	cin >> input;
	while(input[0]!='#'){
		if(next_permutation(input.begin(),input.end())){
			cout << input << endl;
		}
		else{
			cout << "No Successor" << endl;
		}
		cin >> input;
	}
	return 0;
}
