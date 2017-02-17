#include <stdio.h>

using namespace std;

int count[101];

int main(){
	long long int N;
	int age;
	bool spa;
	scanf("%lld",&N);
	while(N){
        spa = true;
		for(int i=0;i<101;i++){
			count[i] = 0;
		}
		for(long long int i=0;i<N;i++){
			scanf("%d",&age);
			count[age]++;
		}
		for(int i=1;i<101;i++){
			while(count[i]){
                if(spa){
                    printf("%d",i);
                    count[i]--;
                    spa = false;
                }
                else{
                    printf(" %d",i);
                    count[i]--;
                }
			}
			/*if(count[i]==1){
				printf("%d",i);
			}*/
		}
		printf("\n");
		scanf("%lld",&N);
	}
	return 0;
}
