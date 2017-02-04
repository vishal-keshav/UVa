#include <iostream>
#include <map>
#include <string>
#include <sstream>

using namespace std;

string code[53] = {".-","-...","-.-.","-..",".","..-.", "--.","....","..",\
					".---", "-.-",".-..","--","-.","---",".--.","--.-",".-.",\
					"...","-","..-","...-",".--","-..-","-.--","--..","-----",\
					".----","..---","...--","....-",".....","-....","--...","---..","----.",\
					".-.-.-","--..--","..--..",".----.","-.-.--","-..-.","-.--.","-.--.-",".-...",\
					"---...","-.-.-.","-...-",".-.-.","-....-","..--.-",".-..-.",".--.-."};
char symbol[53] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R',\
					'S','T','U','V','W','X','Y','Z','0','1','2','3','4','5','6','7','8','9',\
					'.',',','?','\'','!','/','(',')','&',':',';','=','+','-','_','"','@'};
map<string,char> hash_map;

void init_hash_map(void){
	for(int i=0;i<53;i++){
		hash_map[code[i]] = symbol[i];
	}
}

int main(){
	int T,iter=1;
	string line;
	cin >> T;
	init_hash_map();
	cin.ignore();
	while(T--){
		getline(cin,line);
		int index = 0;
		string word;
		stringstream ss(line);
		cout << "Message #" << iter << endl;
		while(ss >> word){
            cout << hash_map[word];
            index+=word.length();
            index++;
            if(line[index] == ' '){
                cout << " ";
                index++;
            }

		}
		cout << endl;
		iter++;
	}
	return 0;
}
