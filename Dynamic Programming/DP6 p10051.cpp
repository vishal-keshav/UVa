#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

#define NR_SIDES 6
/*Face color
0 - front
1 - back
2 - left
3- right
4 - top
5 - bottom*/
struct cube{
	vector<int> face_color(6);
	int cube_index;
};

int main(){
	int N,nr_test=1;
	cin >> N;
	while(N){
		vector<struct cube> cube_list;
		for(int i=0;i<N;i++){
			struct cube temp_cube;
			for(int j=0;j<NR_SIDES;j++){
				cin >> temp_cube.face_color[j];
			}
			temp_cube.cube_index = i+1;
			cube_list.push_back(temp_cube);
		}
		//Process the LIS for each face
		
		//Print result
		
		cin >> N;
		nr_test++;
	}
	
	return 0;
}