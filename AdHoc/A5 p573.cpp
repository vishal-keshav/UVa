#include <iostream>

using namespace std;

int main(){
	int H,U,D,F,days;
	float dist,fatigue,last_climb;
	cin >> H >> U >> D >> F;
	while(H){
		days = 0;
		fatigue = (float)(F*U)/100;
		if(U>H){
			dist+=U;
		}
		else{
			dist = U - D;
			last_climb = U;
			while(dist < H && dist >= 0){
				days++;
				if(last_climb-fatigue >= 0){
					dist += last_climb-fatigue;
					last_climb = last_climb - fatigue;
				}
				else{
					last_climb = 0;
				}
				if(dist>H){
					break;
				}
				dist -= D;

			}
		}
		
		if(dist>0){
			cout << "success on day " << days+1 << endl;
		}
		else{
			cout << "failure on day " << days+1 << endl;
		}
		cin >> H >> U >> D >> F;
	}

	return(0);
}
