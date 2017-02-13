#include <iostream>
#include <cstring>
#include <stdio.h>
#include <map>

using namespace std;

char temp_char,line[10050];

int main(){
	int T;
	cin >> T;
	cin.ignore();
	map<char,long long int> my_hash;
	while(T--){

		long long int value;
		long long int K,M,total_value = 0;
		double result=0;
		cin >> K;
        cin.ignore();
		for(long long int i=0;i<K;i++){
			cin >> temp_char >> value;
			cin.ignore();
			my_hash[temp_char] = value;
		}
		cin >> M;
		cin.ignore();
		while(M--){
			gets(line);
			for(int i=0;i<strlen(line);i++){
				if(my_hash.count(line[i])){
					total_value+=my_hash[line[i]];
				}
			}
		}
		result = (double)(total_value/100.0);
		printf("%0.2lf$\n",result);
		my_hash.clear();
	}
	return 0;
}
