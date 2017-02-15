#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

struct board_element{
	int team_number,nr_solved,penalty;
	int problem_penalty[10];
	bool in_board;
};

vector<struct board_element> leader_board(101);

void init_board(void){
	for(int i=0;i<=100;i++){
		leader_board[i].team_number = i;
		leader_board[i].nr_solved = 0;
		leader_board[i].penalty = 0;
		leader_board[i].in_board = false;
		for(int j=0;j<=9;j++){
			leader_board[i].problem_penalty[j] = 0;
		}
	}
}

void update_leader_board(string input){
	int team_nr,problem_nr,time;
	char status;
	sscanf(input.c_str(),"%d %d %d %c", &team_nr, &problem_nr, &time, &status);
	leader_board[team_nr].in_board = true;
	if(status == 'C'){
		//Check if the problem is solved before
		if(leader_board[team_nr].problem_penalty[problem_nr] != -1){
			leader_board[team_nr].penalty+=time+leader_board[team_nr].problem_penalty[problem_nr];
			leader_board[team_nr].problem_penalty[problem_nr] = -1;
			leader_board[team_nr].nr_solved++;
		}
		else{
			//Do not consider that submission
		}
	}
	else if(status == 'I'){
        if(leader_board[team_nr].problem_penalty[problem_nr] != -1){
            leader_board[team_nr].problem_penalty[problem_nr] +=20;
        }
        else{
            //Do nothing
        }
	}
	else{
		//Do nothing
	}
}

bool compare(struct board_element elem1, struct board_element elem2){
    if(elem1.nr_solved > elem2.nr_solved){
        return true;
    }
    if(elem1.nr_solved < elem2.nr_solved){
        return false;
    }
    if(elem1.penalty < elem2.penalty){
        return true;
    }
    if(elem1.penalty > elem2.penalty){
        return false;
    }
    return (elem1.team_number < elem2.team_number);
}

int main(){
	int T;
	string input;
	cin >> T;
	cin.ignore(2);
	while(T--){
		init_board();
		while(getline(cin, input)){
			if(input.empty())
				break;
			update_leader_board(input);
			//cout << input << endl;
		}
		sort(leader_board.begin(),leader_board.end(),compare);
		for(int i=0;i<=100;i++){
            if(leader_board[i].in_board){
                cout << leader_board[i].team_number << " " << leader_board[i].nr_solved << " " << leader_board[i].penalty << endl;
            }
		}
		if(T!=0){
            cout << endl;
		}
	}
	return 0;
}
