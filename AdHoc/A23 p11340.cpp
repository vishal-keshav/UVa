#include <iostream>
#include <cstring>
#include <stdio.h>
#include <map>

using namespace std;

char line[10000];

int main(){
    //freopen("output.txt","w",stdout);
	int T;
	cin >> T;
	while(T--){
		map<char,int> my_hash;
		char temp_char;
		int value;
		int K,M,total_value = 0;
		float result=0;
		cin >> K;
		for(int i=0;i<K;i++){
			cin >> temp_char >> value;
			my_hash[temp_char] = value;
		}
		cin >> M;
		M++;
		while(M--){
			gets(line);
			for(int i=0;i<strlen(line);i++){
				if(my_hash.count(line[i])){
					total_value+=my_hash[line[i]];
				}
			}
		}
		result = (float)(total_value/100.0);
		printf("%.2f$\n",result);
	}
	printf("\n");
	return 0;
}
