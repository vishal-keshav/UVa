#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <map>

using namespace std;

vector<vector<int> > block_info;

int index[5] = {0,4,8,12,16};
map<char, int> index_map;
map<char, int> garbage_map;
void init(void){
	index_map['r'] = 0;
	index_map['o'] = 1;
	index_map['y'] = 2;
	index_map['g'] = 3;
	index_map['b'] = 4;

	garbage_map['P'] = 0;
	garbage_map['G'] = 1;
	garbage_map['A'] = 2;
	garbage_map['S'] = 3;
	garbage_map['N'] = 4;
}

int get_num(int city_index, vector<vector<int> > vec){
	int total = 0;
	for(int i=0;i<5;i++){
		total+=vec[i][block_info[city_index][i]];
	}
	return total;
}

int main(){
	init();
	string input_line;
	//Clear things up
	input_line.clear();
	block_info.clear();

	cin >> input_line;
	while(input_line[0]!='#'){
		//Check for new case
		if(input_line[0]=='e'){
			//Process
			int nr_city = block_info.size();
			int min_city = 1, min_num = 100000;
			vector<vector<int> > vec(5, vector<int>(5,0));
			for(int i=0;i<5;i++){
				for(int j=0;j<5;j++){
					for(int k=0;k<nr_city;k++){
						if(block_info[k][i]!=j){
							vec[i][j]++;
						}
					}
				}
			}
			for(int k=0;k <nr_city;k++){
				int num = get_num(k, vec);
				if(num<min_num){
					min_num = num;
					min_city = k;
				}
			}
			cout << min_city+1<< endl;
			//Clear
			input_line.clear();
			block_info.clear();
			//Consider new input
			cin >> input_line;
			continue;
		}
		//Put in block info
		vector<int> temp_vec(5);
		for(int i=0;i<5;i++){
            /*To much indexing at once :-) */
			temp_vec[index_map[input_line[index[i]]]] = garbage_map[input_line[index[i]+2]];
		}
		block_info.push_back(temp_vec);
		cin >> input_line;
	}
	return 0;
}
