#include <iostream>
#include <stdio.h>

using namespace std;

int main(){
	int N,M,X,Y,K;
	cin >> K;
	while(K){
		cin >> N >> M;
		for(int i=0;i<K;i++){
			cin >> X >> Y;
			if(X==N || Y==M){
				printf("divisa\n");
			}
			else if(X<N){
				if(Y<M){
					printf("SO\n");
				}
				else{
					printf("NO\n");
				}
			}
			else{
				if(Y<M){
					printf("SE\n");
				}
				else{
					printf("NE\n");
				}
			}
		}
		cin >> K;
	}
	return 0;
}
