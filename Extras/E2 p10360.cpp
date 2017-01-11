#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string.h>

using namespace std;

int rat[1024][1024];
int sum[1024][1024];

int calculate_sum(int k1, int k2, int d){
	int total=0;
	int bound_x_left=k1>=d?k1-d:0;
	int bound_x_right=1024>k1+d?k1+d:1023;
	int bound_y_up=k2>=d?k2-d:0;
	int bound_y_down=1024>k2+d?k2+d:1023;
	for(int i=bound_x_left;i<=bound_x_right;i++){
		for(int j=bound_y_up;j<=bound_y_down;j++){
			total+=rat[i][j];
		}
	}
	return total;
}

void find_best_site(int *x, int *y, int *rat_nr, int d){
	int temp;
	*x =0;
	*y =0;
	*rat_nr=0;
	for(int k1=0;k1<1024;k1++){
		for(int k2=0;k2<1024;k2++){
			if((temp=calculate_sum(k1,k2,d))>*rat_nr){
				*rat_nr = temp;
				*x = k1;
				*y = k2;
			}
		}
	}
}

int main(){
	int T,d,n,x,y,rat_nr;
	scanf("%d",&T);
	while(T--){
		scanf("%d %d",&d,&n);
		memset(rat, 0, sizeof(rat[0][0]) * 1024 * 1024);
		memset(sum, 0, sizeof(sum[0][0]) * 1024 * 1024);
		for(int i=0;i<n;i++){
			scanf("%d %d %d",&x,&y,&rat_nr);
			rat[x][y] = rat_nr;
		}
		find_best_site(&x,&y,&rat_nr,d);
		printf("%d %d %d\n",x,y,rat_nr);
	}
	return 0;
}