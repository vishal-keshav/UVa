#include <stdio.h>
#include <cstring>

using namespace std;

char line[10000];

int main(){
	char letter;
	bool left = true;
	while(gets(line)){
		
		for(int i=0;i<strlen(line);i++){
			if(line[i]=='"'){
				if(left){
					printf("``");
					left = false;
				}
				else{
					printf("''");
					left = true;
				}
			}
			else{
				printf("%c",line[i]);
			}
		}
		printf("\n");
	}
	return 0;
}