#include <iostream>
#include <stdio.h>
#include <vector>
#include <map>
#include <queue>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

int nr_author;
int erdos_node;
vector<string> author_name;
vector<vector<int> > graph;

int compute_erdos(int s, int e){
	int ret=0;
	vector<int> visited(nr_author,0);
	queue<int> bfs_queue;
	bfs_queue.push(s);
	bfs_queue.push(-1);
	visited[s] = 1;
	while(!bfs_queue.empty()){
		int temp = bfs_queue.front();
		bfs_queue.pop();
		if(temp==-1){
			if(bfs_queue.empty()){
				ret = -1;
				break;
			}
			ret++;
			bfs_queue.push(-1);
		}
		else{
			if(temp == e){
				break;
			}
			else{
				for(int i=0;i<graph[temp].size();i++){
					if(visited[graph[temp][i]]==0){
						bfs_queue.push(graph[temp][i]);
						visited[graph[temp][i]] = 1;
					}
				}
			}
		}
	}
	return ret;
}

int main(){
    //freopen("output.txt","w",stdout);
	int T,E,Q, nr_scenario = 1;
	string line;
	string surname, name, full_name;
	cin >> T;
	cin.ignore();
	string erdos = "Erdos, P.";
	while(T--){
		cin >> E >> Q;
        nr_author = 0;
        author_name.clear();
        graph.clear();
        map<string, int> author_map;
		cin.ignore();
		erdos_node=-1;
        for(int i=0;i<E;i++){
			getline(cin, line);
			stringstream ss(line);
            ss >> surname >> name;
			vector<int> paper_author;
			while(name[name.length()-1]!=':'){
				if(name[name.length()-1] == '.'){
					full_name = surname + " " + name.substr(0, name.size());
					ss >> name;
				}
				else{
					full_name = surname + " " + name.substr(0, name.size()-1);
				}
				if(author_map.find(full_name) == author_map.end()){
					author_map[full_name] = nr_author;
					nr_author++;
					author_name.push_back(full_name);
					vector<int> vec;
					graph.push_back(vec);
				}
				//cout << full_name << endl;
				if(full_name == erdos){
					erdos_node = author_map[full_name];
				}
				ss >> surname >> name;
				paper_author.push_back(author_map[full_name]);
				if(surname[surname.length()-1] == ':'){
					break;
				}
			}
			full_name = surname + " " + name.substr(0, name.size()-1);
			if(author_map.find(full_name) == author_map.end()){
				author_map[full_name] = nr_author;
				nr_author++;
				author_name.push_back(full_name);
				vector<int> vec;
				graph.push_back(vec);
			}
			//cout << full_name << endl;
			if(full_name == erdos){
				erdos_node = author_map[full_name];
			}
			paper_author.push_back(author_map[full_name]);

			for(int i=0;i<paper_author.size()-1;i++){
				for(int j=i+1;j<paper_author.size();j++){
					graph[paper_author[i]].push_back(paper_author[j]);
					graph[paper_author[j]].push_back(paper_author[i]);
				}
			}
        }
		cout << "Scenario " << nr_scenario << endl;
        for(int i=0;i<Q;i++){
            getline(cin, line);
            if(author_map.find(line) == author_map.end()){
                cout << line << " infinity" << endl;
                continue;
            }
			int erdos_number;
            erdos_number = compute_erdos(author_map[line], erdos_node);
			if(erdos_number == -1){
				cout << line << " infinity" << endl;
			}
			else{
				cout << line << " " << erdos_number << endl;
			}

        }
		nr_scenario++;
	}
	return 0;
}
