#include <iostream>
#include <string>
#include <stack>

using namespace std;

int main(){
	int N,len;
	string input;
	cin >> N;
	cin.ignore();
	while(N--){
		//cin >> input;
		getline(cin,input);
		//If empty
		len = input.length();
		if(len==0){
			cout << "Yes" << endl;
			continue;
		}
		stack<char> my_stack;

		for(int i=0;i<len;i++){
			if(input[i]=='(' || input[i]=='['){
				my_stack.push(input[i]);
			}
			else if(input[i] == ')'){
				if(!my_stack.empty() && my_stack.top() == '('){
					my_stack.pop();
				}
				else{
					my_stack.push(input[i]);
				}
			}
			else{
				if(!my_stack.empty() && my_stack.top() == '['){
					my_stack.pop();
				}
				else{
					my_stack.push(input[i]);
				}
			}
		}
		if(my_stack.empty()){
			cout << "Yes" << endl;
		}
		else{
			cout << "No" << endl;
		}
	}
	return 0;
}
