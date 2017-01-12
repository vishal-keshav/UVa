#include <stdio.h>
#include <math.h>
#include <algorithm>

using namespace std;

int p,q,r,s,t,u;

double func(double x){
	return (double)(p*exp(-x) + q*sin(x) + r*cos(x) + s*tan(x) + t*x*x + u);
}

bool same_sign(double a, double b){
	return (a*b > 0);
}

int main(){
	double left, middle, right;
	double left_ans,middle_ans,right_ans;
	char line[2000];

	while(sscanf(gets(line), "%d %d %d %d %d %d",&p,&q,&r,&s,&t,&u)!=EOF){
        left_ans = func(0);
        right_ans = func(1);
        left =0;
        right = 1;
        if(same_sign(left_ans, right_ans)){
            printf("No solution\n");
        }
        else{
            while(right-left>=0.0001){
                middle = (right-left)/2 + left;
                middle_ans = func(middle);
                if(same_sign(left_ans,middle_ans)){
                    left = middle;
                }
                else{
                    right = middle;
                }
            }
            printf("%.4lf\n",middle);
        }
	}
	return 0;
}
