#include <iostream>
using namespace std;
int main(){
	int input;
	while(cin >> input)
		cout << (input/2)*3 + (input%2) << endl;
	return 0;}