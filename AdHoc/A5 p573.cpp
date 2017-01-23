#include <iostream>

using namespace std;

int main(){
	int H,U,D,F,days;
	float dist,fatigue;
	cin >> H >> U >> D >> F;
	while(H){
		days = 0;
		fatigue = (float)(F*U)/100;
		dist = U - D;

		while(dist < H && dist >= 0){
			days++;
			if(dist - days*fatigue + U >= 0){
				dist += U - days*fatigue;
			}
			if(dist>H){
				break;
			}
			dist -= D;

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
