#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

struct pole{
	int x, y;
};

int P,k;
int P_blue, P_red;
int mid_temp;

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

int get_nr_fences(int d){
	mid_temp = d;
	
}

int main(){
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
		init();
		int left = 0;
		int right = 2000;
		int mid;
		int prev_mid = 0;
		while(1){
			mid = (left + right)/2;
			nr_fences = get_nr_fences(mid);
			if(nr_fences == k){
				if(prev_mid-mid==0){
					break;
				}
				else{
					right = mid;
				}
			}
			else if(nr_fences > k){
				left = mid;
			}
			else{
				right = mid;
			}
		}
		
	}
	
	return 0;
}