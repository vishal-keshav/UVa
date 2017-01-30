#include <stdio.h>
#include <cstring>

using namespace std;

char line[100];

double time_hr(int H, int M, int S){
	return ((double)H + ((double)M)/(double)60 + ((double)S)/(double)3600);
}

double calc_dist(double now, double prev, int speed){
	return (double)speed*(now-prev);
}

int main(){
	int H,M,S,speed;
	double distance_covered = 0;
	int running_speed = 0;
	int running_H = 0, running_M = 0, running_S = 0;
	while(gets(line)){
		//If query
		if(strlen(line) == 8){
			//Parse the data from line in H,M,S
			sscanf(line, "%d:%d:%d", &H, &M, &S);
			distance_covered+= calc_dist(time_hr(H,M,S),time_hr(running_H,running_M,running_S), running_speed);
			running_H = H;
			running_M = M;
			running_S = S;
			printf("%s %.2lf km\n",line,distance_covered);
		}
		//Speed change point
		else{
			//Parse the data from line in H,M,S,speed
			sscanf(line, "%d:%d:%d %d", &H, &M, &S, &speed);
			distance_covered+= calc_dist(time_hr(H,M,S),time_hr(running_H,running_M,running_S), running_speed);
			running_H = H;
			running_M = M;
			running_S = S;
			running_speed = speed;
		}
	}
	return 0;
}
