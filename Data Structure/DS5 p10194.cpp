#include <iostream>
#include <stdio.h>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

string line_tournament;

struct team_history{
	string team_name;
	int points=0,wins=0,goal_diff=0,goals=0,nr_play=0,ties=0;
};

bool points_comp(struct team_history elem1, struct team_history elem2){
	return (elem1.points > elem2.points);
}

bool wins_comp(struct team_history elem1, struct team_history elem2){
	return (elem1.wins > elem2.wins);
}

bool goal_diff_comp(struct team_history elem1, struct team_history elem2){
	return (elem1.goal_diff > elem2.goal_diff);
}

bool goals_comp(struct team_history elem1, struct team_history elem2){
	return (elem1.goals > elem2.goals);
}

bool nr_play_comp(struct team_history elem1, struct team_history elem2){
	return (elem1.nr_play < elem2.nr_play);
}

bool lex_cmp(char a, char b){
	return (a<b);
}

bool lexo_comp(struct team_history elem1, struct team_history elem2){
	return lexicographical_compare(elem1.team_name.begin(),elem1.team_name.end(),elem2.team_name.begin(),elem2.team_name.end(),lex_cmp);
}

int main(){
	int N,T,G,team_rank;
	cin >> N;
	cin.ignore();
	while(N--){
		map<string,struct team_history> team_map;
		vector<struct team_history> team_list;
		string temp_team_name1,temp_team_name2,game_info;
		getline(cin,line_tournament,'\n');
		//cout << line_tournament << endl;
		cin >> T;
		cin.ignore();
		while(T--){
			getline(cin,temp_team_name1,'\n');
			struct team_history elem;
			elem.team_name = temp_team_name1;
			team_map[temp_team_name1] = elem;
		}
		cin >> G;
		cin.ignore();
		while(G--){
			getline(cin,game_info,'\n');
			int start = 0,len,i,team1_goals,team2_goals;
			bool first_hash = false;
			len = game_info.length();
			for(i=0;i<len;i++){
				if(game_info[i]=='#'){
					if(!first_hash){
						temp_team_name1 = game_info.substr(start,i-start);
						//cout << temp_team_name1 << endl;
						start = i+1;
						first_hash = true;
					}
					else{
						team2_goals = atoi((game_info.substr(start,i-start)).c_str());
						start = i+1;
						break;
					}
				}
				if(game_info[i]=='@'){
					team1_goals = atoi((game_info.substr(start,i-start)).c_str());
					start = i+1;
				}
			}
			temp_team_name2 = game_info.substr(start,len-start);
			//cout << temp_team_name2 << endl;
			team_map[temp_team_name1].goals+=team1_goals;
			team_map[temp_team_name1].goal_diff+=team1_goals-team2_goals;
			team_map[temp_team_name1].nr_play++;
			team_map[temp_team_name2].goals+=team2_goals;
			team_map[temp_team_name2].goal_diff+=team2_goals-team1_goals;
			team_map[temp_team_name2].nr_play++;

            if(team1_goals > team2_goals){
				team_map[temp_team_name1].points+=3;
				team_map[temp_team_name1].wins++;
            }
            else if(team1_goals == team2_goals){
				team_map[temp_team_name1].points+=1;
				team_map[temp_team_name1].ties+=1;
				team_map[temp_team_name2].points+=1;
				team_map[temp_team_name2].ties+=1;
            }
            else{
				team_map[temp_team_name2].points+=3;
				team_map[temp_team_name2].wins++;
            }
			/*for(map<string,struct team_history>::iterator iter = team_map.begin(); iter!=team_map.end();iter++){
				cout << iter->second.team_name << " " << iter->second.points << " " << iter->second.wins << " " << iter->second.goal_diff << " " << iter->second.goals << " " << iter->second.nr_play << endl;
			}*/
		}
		for(map<string,struct team_history>::iterator iter = team_map.begin(); iter!=team_map.end();iter++){
			team_list.push_back(iter->second);
		}
		//Partial sorting
		stable_sort(team_list.begin(),team_list.end(),lexo_comp);
		stable_sort(team_list.begin(),team_list.end(),nr_play_comp);
		stable_sort(team_list.begin(),team_list.end(),goals_comp);
		stable_sort(team_list.begin(),team_list.end(),goal_diff_comp);
		stable_sort(team_list.begin(),team_list.end(),wins_comp);
		stable_sort(team_list.begin(),team_list.end(),points_comp);

		//Output
		cout << line_tournament << endl;
		team_rank=1;
        for(vector<struct team_history>::iterator iter = team_list.begin(); iter!=team_list.end();iter++){
			cout << team_rank << ") " << (*iter).team_name << " " <<  (*iter).points << "p, " << (*iter).nr_play << "g (" <<\
			(*iter).wins << "-"<< (*iter).ties <<"-" << (*iter).nr_play - (*iter).wins - (*iter).ties << "), " << \
			(*iter).goal_diff << "gd (" <<(*iter).goals << "-" <<(*iter).goals - (*iter).goal_diff << ")" <<endl;
			team_rank++;
		}
		if(N!=0){
            cout << endl;
		}
	}
	return 0;
}
