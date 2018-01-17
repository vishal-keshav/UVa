#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>
#include <string>

using namespace std;

struct config{
	int state[3][3];
};
struct config start_state, end_state;
string start_str, end_str;
map<string, int> map_state;
int global_counter;

struct action{
	char dir;
	int level;
};

string state_to_string(struct config s){
	string ret = "000000000";
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			ret[i*3+j] = (char)(s.state[i][j]+(int)'0');
		}
	}
	return ret;
}

struct config string_to_state(string s){
	struct config ret;
	for(int i=0;i<9;i++){
		ret.state[i/3][i%3] = (int)(s[i]-'0');
	}
	return ret;
}

void init_end(void){
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			end_state.state[i][j] = i*3 + j + 1;
		}
	}
	end_str = state_to_string(end_state);
}

string horizontal_move(int l, string s){
	char temp;
	int index;
	//Swap 1
	index = l*3;
	temp = s[index+0];
	s[index+0] = s[index+1];
	s[index+1] = temp;
	//Swap 2
	temp = s[index+0];
	s[index+0] = s[index+2];
	s[index+2] = temp;
	return s;
}

string vertical_move(int l, string s){
	char temp;
	//Swap 1
	temp = s[3*0+l];
	s[3*0+l] = s[3*1+l];
	s[3*1+l] = temp;
	//Swap 2
	temp = s[3*1+l];
	s[3*1+l] = s[3*2+l];
	s[3*2+l] = temp;
	return s;
}

string horizontal_move_reverse(int l, string s){
	char temp;
	int index;
	//Swap 1
	index = l*3;
	temp = s[index+0];
	s[index+0] = s[index+1];
	s[index+1] = temp;
	//Swap 2
	temp = s[index+1];
	s[index+1] = s[index+2];
	s[index+2] = temp;
	return s;
}

string vertical_move_reverse(int l, string s){
	char temp;
	//Swap 1
	temp = s[3*0+l];
	s[3*0+l] = s[3*2+l];
	s[3*2+l] = temp;
	//Swap 2
	temp = s[3*1+l];
	s[3*1+l] = s[3*2+l];
	s[3*2+l] = temp;
	return s;
}

bool state_is_null(string s){
	if(s[0] == 'X'){
		return true;
	}
	return false;
}

bool state_is_end(string e){
	if(e!=end_str){
		return false;
	}
	return true;
}

bool state_visited(string s){
	if(map_state.find(s) == map_state.end()){
		return false;
	}
	return true;
}

bool visit_state(string s){
	map_state[s] = global_counter;
	global_counter++;
}

vector<struct action> compute_seq(void){
	int ret = 0;
	vector<struct action> parent_action;
	global_counter = 0;
	map_state.clear();
	queue<string> bfs_queue;
	string null = "X";
	bfs_queue.push(start_str);
	map_state[start_str] = global_counter;
	global_counter++;
	struct action no_action;
	parent_action.push_back(no_action);
	bfs_queue.push(null);
	while(!bfs_queue.empty()){
		string temp = bfs_queue.front();
		bfs_queue.pop();
		if(state_is_null(temp)){
			if(bfs_queue.empty()){
				ret = -1;
				break;
			}
			ret++;
			bfs_queue.push(null);
		}
		else{
			if(state_is_end(temp)){
				break;
			}
			else{
				string new_state = temp;
				struct action temp_action;
				//Horizontal moves
				for(int i=0;i<3;i++){
					string new_state_h = horizontal_move(i, new_state);
					if(!state_visited(new_state_h)){
						bfs_queue.push(new_state_h);
						visit_state(new_state_h);
						temp_action.dir = 'H';
						temp_action.level = i;
						parent_action.push_back(temp_action);
					}
				}
				//Vertical moves
				for(int i=0;i<3;i++){
					string new_state_v = vertical_move(i, new_state);
					if(!state_visited(new_state_v)){
						bfs_queue.push(new_state_v);
						visit_state(new_state_v);
						temp_action.dir = 'V';
						temp_action.level = i;
						parent_action.push_back(temp_action);
					}
				}
			}
		}
	}
	vector<struct action> action_seq;
	if(ret==-1){
		return action_seq;
	}
	string temp_state = end_str;
	struct action ac;
	while(map_state[temp_state]!=0){
		ac = parent_action[map_state[temp_state]];
		action_seq.push_back(ac);
		if(ac.dir == 'H'){
			temp_state = horizontal_move_reverse(ac.level, temp_state);
		}
		else{
			temp_state = vertical_move_reverse(ac.level, temp_state);
		}
	}
	reverse(action_seq.begin(), action_seq.end());
	return action_seq;
}

int main(){
    //freopen("output.txt","w",stdout);
	init_end();
	cin >> start_state.state[0][0];
	while(start_state.state[0][0]){
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++){
				if(i+j > 0){
					cin >> start_state.state[i][j];
				}
			}
		}
		start_str = state_to_string(start_state);
		vector<struct action> ans = compute_seq();
		if(ans.size()==0){
            if(start_str == end_str){
                cout << "0 "<< endl;
            }
            else{
                cout << "Not solvable" << endl;
            }
		}
		else{
			cout << ans.size() << " ";
			for(int i=0;i<ans.size();i++){
				cout << ans[i].dir << (ans[i].level+1);
			}
			cout << endl;
		}
		cin >> start_state.state[0][0];
	}
	return 0;
}
