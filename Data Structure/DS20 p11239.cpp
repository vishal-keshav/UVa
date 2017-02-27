#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <algorithm>
#include <stdio.h>

using namespace std;

struct project{
	string project_name;
	int student_registered;
};

bool comp(struct project elem1, struct project elem2){
	if(elem1.student_registered == elem2.student_registered){
		return (elem1.project_name < elem2.project_name);
	}
	return (elem1.student_registered > elem2.student_registered);
}

int main(){
	string input,current_project;
	bool setup = true;
    set<string> student_set;
    map<string,int> project_map;
    map<string,string> student_map;
	while(1){
		if(setup){
			student_set.clear();
			project_map.clear();
			student_map.clear();
			setup = false;
		}
		getline(cin,input);
		if(input[0]=='1'){
			//Print
			vector<struct project> vec;
			struct project temp;
			for(map<string,int>::iterator iter = project_map.begin(); iter!=project_map.end();iter++){
				temp.project_name = iter->first;
				temp.student_registered = iter->second;
				vec.push_back(temp);
			}
			sort(vec.begin(),vec.end(), comp);
			for(vector<struct project>::iterator iter = vec.begin();iter!=vec.end();iter++){
				cout << (*iter).project_name << " " << (*iter).student_registered << endl;
			}
			//Setup, mark it true;
			setup = true;
			continue;
		}
		if(input[0]=='0'){
			break;
		}
		if(input[0]>='a' && input[0]<='z'){
			//student name
			//If student is in set
			set<string>::iterator it = student_set.find(input);
			if(it!=student_set.end()){
				//if student has registered for a different project or banned
				if(student_map[input]!=current_project){
					//If student is banned
					if(student_map[input] == "banned"){
						//dont register this student to current project
					}
					else{
						//Ban this student from previous project and future project
						project_map[student_map[input]]--;
						student_map[input] = "banned";
					}
				}
				//if student is register to this project already
				else{
					//dont register again
				}
			}
			//If student in new register
			else{
				student_map[input] = current_project;
				student_set.insert(input);
				project_map[student_map[input]]++;
			}
		}
		else{
			//Project name
			current_project = input;
			project_map[current_project] = 0;
		}
	}

	return 0;
}
