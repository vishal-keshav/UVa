#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

void print_spaces(int nr_space){
	for(int i=0;i<nr_space;i++){
		cout << " ";
	}
}

void print_words(string word1, string word2){
	print_spaces(9);
	cout << word1;
	print_spaces(25-word1.length());
	cout << word2 << endl;
}

int code(char in){
	if(in == 'C' || in == 'S' || in == 'K' || in == 'G' ||
		in == 'J'|| in == 'Q' || in == 'X' || in == 'Z'){
		return (2);
	}
	else if(in == 'B' || in == 'P' || in == 'F' || in == 'V'){
		return (1);
	}
	else if(in == 'D' || in == 'T'){
		return (3);
	}
	else if(in == 'L'){
		return (4);
	}
	else if(in == 'M' || in == 'N'){
		return (5);
	}
	else if(in == 'R'){
		return (6);
	}
	else{
		return (0);
	}
}

int main(){
	string name;
	string soundex = "A000";
	int current_code, prev_code, index;
	print_words("NAME","SOUNDEX CODE");
	while(getline(cin,name)){
		prev_code = code(name[0]);
		index = 1;
		soundex[0] = name[0];
		for(int i=1;i<name.length();i++){
			current_code = code(name[i]);
			if(current_code == 0){
				prev_code = current_code;
				continue;
			}
			else if(prev_code == current_code){
				continue;
			}
			else{
				
				soundex[index] = to_string(current_code)[0];
				prev_code = current_code;
				index++;
			}

			if(index>3){
				break;
			}
		}
		while(index<=3){
			
			soundex[index] = '0';
			index++;
			
		}
		print_words(name,soundex);
	}
	print_spaces(19);
	cout << "END OF OUTPUT";
	return 0;
}
