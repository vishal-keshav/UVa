#include <iostream>
#include <stdio.h>
#include <vector>
#include <stack>

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

int opposite_side[6] = {1,0,3,2,5,4};
string string_side[6] = {"front", "back", "left" ,"right" ,"top" ,"bottom"};

int opposite(int side){
	return opposite_side[side];
}

string side_to_string(int side){
	return string_side[side];
}

int main(){
    //freopen("output.txt","w",stdout);
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
		vector<vector<int> > parent(N,vector<int>(6,-1));
		vector<vector<int> > side_parent(N,vector<int>(6,-1));
		int best_index = N-1;
		int best_side = 0;
		int max_lis = 1;
		for(int i=N-2;i>=0;i--){
			for(int j=i+1;j<N;j++){
				//Process each side of the cube
				for(int k=0;k<NR_SIDES;k++){
					for(int l=0;l<NR_SIDES;l++){
						if(cube_list[i].face_color[opposite(k)] == cube_list[j].face_color[l]){
							if(lis[i][k] < 1+lis[j][l]){
								lis[i][k] = 1 + lis[j][l];
								parent[i][k] = j;
								side_parent[i][k] = l;
								if(lis[i][k] > max_lis){
									max_lis = lis[i][k];
									best_index = i;
									best_side = k;
								}
							}
						}
					}
				}
			}
		}
		//Print result
		cout << "Case #" << nr_test << endl;
		cout << max_lis << endl;
		int iter_index = best_index;
		int iter_side = best_side;
		int temp_iter_index;
		//stack<int>
		while(iter_index!=-1 && iter_side!=-1){
			cout << cube_list[iter_index].cube_index << " " << side_to_string(iter_side) << endl;
			temp_iter_index = iter_index;
			iter_index = parent[iter_index][iter_side];
			iter_side = side_parent[temp_iter_index][iter_side];
		}
		cin >> N;
		if(N){
            cout << endl;
		}
		nr_test++;
	}

	return 0;
}
