#include <stdio.h>
#include <algorithm>

using namespace std;

int memo[10000];
int sequence_len(int n){
	if(n>=10000){
		if(n%2!=0){
			return (1+sequence_len(3*n + 1));
		}
		else{
			return (1+sequence_len(n/2));
		}
	}
	else{
		if(memo[n]!=0){
			return memo[n];
		}
		if(n%2!=0){
			memo[n] = 1 + sequence_len(3*n + 1);
			return memo[n];
		}
		else{
			memo[n] = 1 + sequence_len(n/2);
			return memo[n];
		}
	}
}

/*int sequence_len(int n){
    if(n==1){
        return 1;
    }
    else{
        if(n%2!=0){
            return (1+sequence_len(3*n + 1));
        }
        else{
            return (1+sequence_len(n/2));
        }
    }
}*/

int main(){
	int i,j,maximum;
	int temp;
	for(int index = 0;index <10000;index++){
		memo[index] = 0;
	}
	memo[1] = 1;
	while(scanf("%d%d",&i,&j)==2 && i>0 && j>0){
		maximum = 0;
		printf("%d %d ",i,j);
		if(i>j){
            temp = i;
            i = j;
            j = temp;
		}
		for(int index = i; index<=j; index++){
			maximum = max(maximum, sequence_len(index));
		}
		printf("%d\n",maximum);
	}

	return(0);
}
