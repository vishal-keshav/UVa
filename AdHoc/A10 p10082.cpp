#include <iostream>
#include <stdio.h>
#include <cstring>

using namespace std;

int row1[] = {'Q','W','E','R','T','Y','U','I','O','P','[',']','\\'};
int row2[] = {'A','S','D','F','G','H','J','K','L',';','\''};
int row3[] = {'Z','X','C','V','B','N','M',',','.','/'};

int nr_row1 = 13;
int nr_row2 = 11;
int nr_row3 = 10;

char char_hash[100];
char line[100000];


int main(){
	/*for(int i=0;i<nr_row1;i++){
		cout << (char)row1[i] << " " << (int)row1[i] << endl;
	}
	for(int i=0;i<nr_row2;i++){
		cout << (char)row2[i] << " " << (int)row2[i] << endl;
	}
	for(int i=0;i<nr_row3;i++){
		cout << (char)row3[i] << " " << (int)row3[i] << endl;
	}*/
	//Fill hash
	for(int i=1;i<nr_row1;i++){
		char_hash[(int)row1[i]] = row1[i-1];
	}
	for(int i=1;i<nr_row2;i++){
		char_hash[(int)row2[i]] = row2[i-1];
	}
	for(int i=1;i<nr_row3;i++){
		char_hash[(int)row3[i]] = row3[i-1];
	}
	while(gets(line)){
		for(int i=0;i<strlen(line);i++){
			if(line[i] == ' '){
				printf(" ");
			}
			else{
				printf("%c",char_hash[(int)line[i]]);
			}
		}
		printf("\n");
	}
	
	
	return 0;
}