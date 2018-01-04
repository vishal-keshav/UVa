#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>

using namespace std;

int move_x[8] = {-2, -2, -1, 1, 2, 2, 1, -1};
int move_y[8] = {-1, 1, 2, 2, 1, -1, -2, -2};

struct state{
	string row[5];
	int empty_x, empty_y;
};

struct state final_state;

void construct_final(void){
	final_state.row[0] = "11111";
	final_state.row[1] = "01111";
	final_state.row[2] = "00 11";
	final_state.row[3] = "00001";
	final_state.row[4] = "00000";
	final_state.empty_x = 2;
	final_state.empty_y = 2;
    return;
}

void compute_empty(struct state *input){
	for(int i=0;i<5;i++){
		for(int j=0;j<5;j++){
			if(input->row[i][j] == ' '){
				input->empty_x = i;
				input->empty_y = j;
				return;
			}
		}
	}
	return;
}

bool state_is_final(struct state s){
	if(s.empty_x!=final_state.empty_x){
		return false;
	}
	if(s.empty_y!=final_state.empty_y){
		return false;
	}
	for(int i=0;i<5;i++){
		for(int j=0;j<5;j++){
			if(s.row[i][j]!=final_state.row[i][j]){
				return false;
			}
		}
	}
	return true;
}

bool valid(int x, int y){
	if(x>=0 && x<5 && y>=0 && y<5){
		return true;
	}
	return false;
}

void copy_state(struct state *a, struct state *b){
	(*a).empty_x = (*b).empty_x;
	(*a).empty_y = (*b).empty_y;
	for(int i=0;i<5;i++){
		for(int j=0;j<5;j++){
			(*a).row[i][j] = (*b).row[i][j];
		}
	}
	return;
}

void change_state(int x, int x_new, int y, int y_new, struct state *s){
	s->empty_x = x_new;
	s->empty_y = y_new;
	s->row[x][y] = s->row[x_new][y_new];
	s->row[x_new][y_new] = ' ';
	return;
}

void print_state(struct state s){
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            cout << s.row[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int compute_moves(struct state s){
	int ret = 0;
	struct state null_state;
	null_state.empty_x = -1;
	queue<struct state> bfs_queue;
	bfs_queue.push(s);
	bfs_queue.push(null_state);
	while(!bfs_queue.empty()){
		struct state temp = bfs_queue.front();
		bfs_queue.pop();
		if(ret<=2){
            print_state(temp);
		}
		if(temp.empty_x == -1){
			if(bfs_queue.empty()){
				break;
			}
			ret++;
			if(ret>10){
				break;
			}
			bfs_queue.push(null_state);
		}
		else{
			if(state_is_final(temp)){
				break;
			}
			else{
				struct state new_state;
				//copy_state(&new_state, &temp);
                new_state.empty_x = temp.empty_x;
                new_state.empty_y = temp.empty_y;
                for(int i=0;i<5;i++){
                    for(int j=0;j<5;j++){
                        new_state.row[i][j] = temp.row[i][j];
                    }
                }
                if(ret<=2){
                    print_state(new_state);
                }
				int x = temp.empty_x;
				int y = temp.empty_y;
				for(int i=0;i<8;i++){
					int new_x = x+move_x[i];
					int new_y = y+move_y[i];
					if(valid(new_x, new_y)){
						change_state(x, new_x, y, new_y, &new_state);
						bfs_queue.push(new_state);
						change_state(new_x, x, new_y, y, &new_state);
					}
				}
			}
		}

	}
}

int main(){
	int T;
	construct_final();
	cin >> T;
	cin.ignore();
	while(T--){
		struct state initial_state;
		for(int i=0;i<5;i++){
			getline(cin, initial_state.row[i]);
		}
		compute_empty(&initial_state);
		int moves = compute_moves(initial_state);
		if(moves>10){
			cout << "Unsolvable in less than 11 move(s)." << endl;
		}
		else{
			cout << "Solvable in " << moves << " moves(s)." << endl;
		}
	}

	return 0;
}
