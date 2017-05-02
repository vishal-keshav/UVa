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
    int cube_index;
	vector<int> face_color;

};

int opposite(int side){
	switch(side){
		case 0:
			return 1;
			break;
		case 1:
			return 0;
			break;
		case 2:
			return 3;
			break;
		case 3:
			return 2;
			break;
		case 4:
			return 5;
			break;
		case 5:
			return 4;
			break;
	}
}

int main(){
	int N,nr_test=1;
	cin >> N;
	while(N){
		vector<struct cube> cube_list;
		for(int i=0;i<N;i++){
			struct cube temp_cube;
			temp_cube.face_color = vector<int>(NR_SIDES);
			for(int j=0;j<NR_SIDES;j++){
				cin >> temp_cube.face_color[j];
			}
			temp_cube.cube_index = i+1;
			cube_list.push_back(temp_cube);
		}
		//Process the LIS for each face
		vector<vector<int> > lis(N,vector<int>(6,1));
		int max_lis = 1;
		for(int i=N-2;i>=0;i--){
			for(int j=i+1;j<N;j++){
				//Process each side of the cube
				for(int k=0;k<NR_SIDES;k++){
					for(int l=0;l<NR_SIDES;l++){
						if(cube_list[i].face_color[k] == cube_list[j].face_color[l]){
							if(lis[i][opposite(k)] < 1+lis[j][l]){
								lis[i][opposite(k)] = 1 + lis[j][l];
								if(lis[i][opposite(k)] > max_lis){
									max_lis = lis[i][opposite(k)];
								}
							}
						}
					}
				}
			}
		}
		//Print result
		cout << max_lis << endl;
		cin >> N;
		nr_test++;
	}

	return 0;
}
