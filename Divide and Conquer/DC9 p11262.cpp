#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

//#define DEBUG 1

struct pole{
	int x, y;
};

int P,k;
int P_blue, P_red;
double mid_temp;

struct pole blue[101];
struct pole red[101];

bool blue_covered[101];
bool red_covered[101];

void init(void){
	for(int i=0;i<P_blue;i++){
		blue_covered[i] = false;
	}
	for(int i=0;i<P_red;i++){
		red_covered[i] = false;
	}
}

double dist(int blue_idx, int red_idx){
	double ret=sqrt(pow(blue[blue_idx].x-red[red_idx].x,2) + pow(blue[blue_idx].y-red[red_idx].y,2));
#ifdef DEBUG
//	cout << "Distance between blue "<< blue_idx << " and red " << red_idx << " = "<< ret << endl;
#endif
	return ret;
}

int max_fences(int blue_idx){
#ifdef DEBUG
	cout << "max_fences call for " << blue_idx << endl;
#endif
	//Base case
	if(blue_idx == P_blue){
        //cout << "Base condition" << endl;
		return 0;
	}
	//Main case
	else{
		int ret = 0;
		//Try connecting with possible reds
		for(int i=0;i<P_red;i++){
			if(!red_covered[i] && dist(blue_idx,i) <= mid_temp){
				red_covered[i] = true;
				ret = max(ret,1+max_fences(blue_idx+1));
				red_covered[i] = false;
			}
		}
		//Dont try connecting this blue
		ret = max(ret, max_fences(blue_idx+1));
#ifdef DEBUG
//		cout << "max_fences for " << blue_idx << " returns " << ret << endl;
#endif
		return ret;
	}
}

int get_nr_fences(double d){
	mid_temp = d;
	return max_fences(0);
}

int main(){
    //freopen("output.txt","w",stdout);
	int T,temp_x,temp_y;
	string color;
	cin >> T;
	while(T--){
		cin >> P >> k;
		P_blue = 0;
		P_red = 0;
		for(int i=0;i<P;i++){
			cin >> temp_x >> temp_y >> color;
			if(color=="blue"){
				blue[P_blue].x = temp_x;
				blue[P_blue].y = temp_y;
				P_blue++;
			}
			else{
				red[P_red].x = temp_x;
				red[P_red].y = temp_y;
				P_red++;
			}
		}
		if(min(P_blue,P_red)<k){
			cout << "Impossible" << endl;
			continue;
		}
		init();
		double left = 0.0;
		double right = 2000.00;
		double mid;
		int prev_mid = 0;
		int nr_fences;
		while(1){
#ifdef DEBUG
//		cout << "In loop" << endl;
#endif
			mid = (left + right)/2;
			nr_fences = get_nr_fences(mid);
#ifdef DEBUG
			cout << "mid is " << mid << ". nr_fences is " << nr_fences << endl;
#endif
			if(nr_fences == k){
				if(right-left<0.1){
					break;
				}
				else{
					right = mid;
					prev_mid = (int)mid;
				}
			}
			else if(nr_fences > k){
				right = mid;
				prev_mid = (int)mid;
			}
			else{
				left = mid;
				prev_mid = (int)mid;
			}
		}
		if(get_nr_fences((double)floor(mid))==k){
            cout << floor(mid) << endl;
		}
		else{
            cout << ceil(mid) << endl;
		}
	}

	return 0;
}
