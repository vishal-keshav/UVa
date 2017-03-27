#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

#define INT_MAXIMUM 10000000

int R,C,loc_x, loc_y, nr_beepers;
int min_dist;
struct loc{
	int x,y;
};

vector<struct loc> beepers;
vector<int> collected;

int absolute(int n){
	if(n>0){
		return n;
	}
	else{
		return (0-n);
	}
}
int find_distance(int x1, int y1, int x2, int y2){
	return(absolute(x1-x2)+absolute(y1-y2));
}
void collect_beepers(int c, int dist, int my_x, int my_y){
	//Base case
	if(c>=nr_beepers){
		min_dist = min(min_dist, dist + find_distance(my_x, my_y, loc_x, loc_y));
		return;
	}
	else{
		for(int i=0;i<nr_beepers;i++){
			if(collected[i]==-1){
				collected[i] = 1;
				collect_beepers(c+1,dist+find_distance(my_x, my_y,beepers[i].x, beepers[i].y), beepers[i].x, beepers[i].y);
				collected[i] = -1;
			}
		}
	}
}

int main(){
	int T;
	int temp_x, temp_y;
	cin >> T;
	while(T--){
		cin >> R >> C >> loc_x >> loc_y >> nr_beepers;
		beepers.clear();
		beepers.resize(nr_beepers);
		collected.clear();
		collected.resize(nr_beepers,-1);
		min_dist = INT_MAXIMUM;
		for(int i=0;i<nr_beepers;i++){
			cin >> temp_x >> temp_y;
			struct loc temp;
			temp.x = temp_x;
			temp.y = temp_y;
			beepers[i] = temp;
		}
		collect_beepers(0,0,loc_x, loc_y);
		cout << "The shortest path has length " << min_dist << endl;
	}
	return 0;
}
