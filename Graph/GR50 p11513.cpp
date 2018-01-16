#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

struct config{
	int state[3][3];
};
struct config start_state, end_state;

void init_end(void){
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			end_state.state[i][j] = i*3 + j + 1;
		}
	}
}

vector<char> compute_seq(void){
	vector<int> parent;
	//map<struct config, int>
}

int main(){
	
	init_end();
	cin >> start_state.state[0][0];
	while(state_state.state[0][0]){
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++){
				if(i+j > 0){
					cin >> start_state.state[i][j];
				}
			}
		}
		vector<char> ans = compute_seq();
		if(ans.size()==0){
			cout << "Not solvable" << endl;
		}
		else{
			cout << ans.size() << " ";
			for(int i=0;i<ans.size();i++){
				cout << ans[i];
			}
			cout << endl;
		}
		cin >> start_state.state[0][0];
	}
	
	return 0;
}