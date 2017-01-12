#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <iostream>
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
	while (cin >> p >> q >> r >> s >> t >> u){ //Had to use cin because there was some problem with EOF detection
        left_ans = func(0);
        right_ans = func(1);
        left =0;
        right = 1;
        if(same_sign(left_ans, right_ans)){
            printf("No solution\n");
        }
        else{
            while(right-left>=0.000000001){
                middle = (right-left)/2 + left;
                middle_ans = func(middle);
                if(same_sign(left_ans,middle_ans)){
                    left = middle;
                }
                else{
                    right = middle;
                }
            }
            if(abs(func(middle)<=0.0001)){
                printf("%.4lf\n",middle);
            }
            else{
                printf("No solution\n");
            }
        }
	}
	return(0);
}
