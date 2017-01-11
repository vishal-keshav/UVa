
#include <stdio.h>
#include <algorithm>
#include <string.h>

using namespace std;

int rat[1024][1024];
int ans_x, ans_y, ans_nr;

void fill_and_find(int x, int y, int rat_nr,int d){
	int bound_x_left=x-d>=0?x-d:0;
	int bound_x_right=x+d<1024?x+d:1023;
	int bound_y_up=y-d>=0?y-d:0;
	int bound_y_down=y+d<1024?y+d:1023;
	for(int i=bound_x_left;i<=bound_x_right;i++){
		for(int j=bound_y_up;j<=bound_y_down;j++){
			rat[i][j]+=rat_nr;
			if(rat[i][j]>ans_nr){
				ans_nr = rat[i][j];
				ans_x = i;
				ans_y = j;
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
		ans_x=ans_y=ans_nr=0;
		for(int i=0;i<n;i++){
			scanf("%d %d %d",&x,&y,&rat_nr);
			fill_and_find(x,y,rat_nr,d);
		}
		printf("%d %d %d\n",ans_x,ans_y,ans_nr);
	}
	return 0;
}