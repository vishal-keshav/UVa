#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

vector<string> dictionary;
vector<string> password;
string rule;

int D,R;
int rule_length;

void generate_password(int index){
	//Base case
	if(index>=rule_length){
		for(int i=0;i<rule_length;i++){
			cout << password[i];
		}
		cout << endl;
	}
	//Main case
	else{
		if(rule[index]=='#'){
			for(int i=0;i<D;i++){
				password.push_back(dictionary[i]);
				generate_password(index+1);
				password.pop_back();
			}
		}
		else{
			for(int i=0;i<10;i++){
				string num = "0";
				num[0] = (char)((int)'0'+i);
				password.push_back(num);
				generate_password(index+1);
				password.pop_back();
			}
		}
	}
}


int main(){
	while(cin >> D){
        cout << "--" << endl;
		dictionary.clear();
		dictionary.resize(D);
		password.clear();
		for(int i=0;i<D;i++){
			cin >> dictionary[i];
		}
		cin >> R;
		for(int i=0;i<R;i++){
			cin >> rule;
			rule_length = rule.length();
			generate_password(0);
		}
	}
	return 0;
}
