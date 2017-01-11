#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <string.h>
#include <math.h>

using namespace std;

int N;
double dist[20][20], memo[1<<16];//1<<16 represents 2^(16) as there can be atmost 16 students

//Resursive memoization function
double matching(int bit_mask){
	if(memo[bit_mask] > -0.5){//If filled, optimal sum has to be positive
		return memo[bit_mask];//Return if we already have the result
	}
	if(bit_mask == (1<<2*N)-1){//We reached the end where every student is considered
		return memo[bit_mask]=0; //Return the ans but with setting the memo to zero
		//Returned value here returned represents no distance is left to be added.
	}

	double matching_value = 32767*32767;//start with big number since we are taking min
	
	for(int p1 = 0; p1<2*N; p1++){//take first student for pairing
		if(!(bit_mask & (1<<p1))){//Consider only if this p1 is not selected
			for(int p2 = p1+1;p2<2*N;p2++){//take second student for pairing
				if(!(bit_mask & (1<<p2))){//Consider only if p2 is not selected
					matching_value = min(matching_value, dist[p1][p2]+matching(bit_mask|(1<<p1)|(1<<p2)));
				}
			}
		}

	}
	return memo[bit_mask] = matching_value; //Return after  noting the result
}

int main(){
	/*Input buffer: line for sufficiently large number of test cases,
	name to hold name string
	i,j are local variables, x,y for coordinated*/
	char line[1000], name[1000];
	int i,j,caseNo = 1, x[20], y[20];
	/*gets(line) take input buffer in line and returns buffer pointer,
	an input to sscanf, additional parameter to format and parse in N*/
	while(sscanf(gets(line), "%d", &N),N){ //execute till N has 0
		for(i=0;i<2*N;i++){
			sscanf(gets(line), "%s %d %d",&name, &x[i], &y[i]);
		}
		//Building pairwise distance
		for(i=0;i<2*N;i++){
			for(j=0;j<2*N;j++){
				dist[i][j] = sqrt((double)(x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]));
			}
		}
		/*for memoization memo is used, solving bitwise DP problem
		memo[bits set at 1,2,3,4] represents optimal addition with distance pairing either
		student (1,2),(3,4) or pairing (1,3),(2,4), index in memo[index] represents there
		how many even number of considered for pairing and calculating optimal distance sum
		represented by memo[index]*/
		memset(memo,-1,sizeof(memo));
		printf("Case %d: %.2lf\n", caseNo++, matching(0));
	}
	return 0;
}
