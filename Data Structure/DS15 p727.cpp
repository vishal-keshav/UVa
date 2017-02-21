#include <iostream>
#include <stack>
#include <string>

using namespace std;

int main(){
	int T;
	string line;
	cin >> T;
	cin.ignore();
	getline(cin,line);
	while(T--){
		stack<char> my_stack;
		while(getline(cin,line)){
			if(line.length() == 0){
				break;
			}
			//If paranthesis
			if(line[0] == '('){
				my_stack.push(line[0]);
			}
			else if(line[0] == ')'){
				//pop till ( is reached
				while(my_stack.top()!='('){
					cout << my_stack.top();
					my_stack.pop();
				}
				my_stack.pop();
			}
			else if(line[0]=='*' || line[0]=='/'){
				//if(!my_stack.empty() && (my_stack.top()=='+' || my_stack.top()=='-')){
                    //cout << line[0];
				//}
				//else{
                    //my_stack.push(line[0]);
				//}
				if(!my_stack.empty() && (my_stack.top()=='*' || my_stack.top()=='/')){
                    cout << my_stack.top();
                    my_stack.pop();
                    my_stack.push(line[0]);
				}
				else{
                    my_stack.push(line[0]);
				}
			}
			else if(line[0]=='+' || line[0]=='-'){
				while(!my_stack.empty() && (my_stack.top()=='*' || my_stack.top()=='/' \
                                /*|| my_stack.top()=='+' || my_stack.top()=='-'*/)){
					cout << my_stack.top();
					my_stack.pop();
				}
				if(!my_stack.empty() && (my_stack.top()=='+' || my_stack.top()=='-')){
                    cout << my_stack.top();
                    my_stack.pop();
				}
				my_stack.push(line[0]);
			}
			else{
				cout << line[0];
			}
		}
		while(!my_stack.empty()){
			cout << my_stack.top();
			my_stack.pop();
		}
		cout << endl;
		if(T!=0){
            cout << endl;
		}
	}

	return 0;
}
