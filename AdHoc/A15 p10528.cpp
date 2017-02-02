#include <iostream>
#include <stdio.h>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include <sstream>



using namespace std;

map<string,int> hash_map;
string notes[12] = {"C","C#","D","D#","E","F","F#","G","G#","A","A#","B"};

void init_map(void){
	for(int i=0;i<12;i++){
		hash_map[notes[i]] = i+1;
	}
}

int sequence[7] = {0,2,4,5,7,9,11};

int valid_notes[13] = {0,0,0,0,0,0,0,0,0,0,0,0,0};

int enable_bit(int n){
	return (1 << n);
}

void init_valid_notes(void){
    int bit;
	for(int note = 1; note<=12; note++){
		for(int i=0;i<7;i++){
			bit = ((note+sequence[i]-1)%12 + 1);
			valid_notes[note]|=enable_bit(bit-1);
		}
	}
}

string line;

int main(){

	init_map();
	init_valid_notes();
#ifdef DEBUG
	cout << hash_map["C"] << " " << hash_map["B"] << endl;
	cout << enable_bit(10);
	for(int i=0;i<14;i++){
		cout << valid_notes[i] << endl;
	}
#endif
	while(getline(cin,line),line!="END"){
        string word;
		stringstream ss(line);
		int music_bit=0;
		int left, right;
		while (ss >> word) {
			//word.erase(std::remove(word.begin(), word.end(), '\r'), word.end());
			//cout << word << endl;
			music_bit|=enable_bit(hash_map[word]-1);
		}
		for(int note=1;note<=12;note++){
			left = (int)((int)(valid_notes[note]^music_bit) & (int)valid_notes[note]);
			right = (int)(valid_notes[note]^music_bit);
			/*if((valid_notes[note]^music_bit)&valid_notes[note] == (valid_notes[note]^music_bit)){
				cout << notes[note-1] << " ";
			}*/
			if(left == right){
                cout << notes[note-1] << " ";
			}
			//cout << left << " " << right << endl;
		}
		cout << endl;
	}
	return 0;
}
