#include <iostream>
#include <stdio.h>
#include <vector>
#include <map>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

int nr_word;
vector<string> word_name;
vector<vector<int> > graph;

vector<int> compute_path(int s, int e){
	vector<int> ret;
	bool found = false;
	vector<int> visited(nr_word,0);
	vector<int> parent(nr_word);
	for(int i=0;i<nr_word;i++){
		parent[i] = i;
	}
	queue<int> bfs_queue;
	bfs_queue.push(s);
	visited[s] = 1;
	while(!bfs_queue.empty()){
		int temp = bfs_queue.front();
		bfs_queue.pop();
		if(temp == e){
			found = true;
			break;
		}
		else{
			for(int i=0;i<graph[temp].size();i++){
				if(visited[graph[temp][i]]==0){
					bfs_queue.push(graph[temp][i]);
					visited[graph[temp][i]] = 1;
					parent[graph[temp][i]] = temp;
				}
			}
		}
	}
	if(found){
		int node = e;
		ret.clear();
		while(node!=s){
			ret.push_back(node);
			node = parent[node];
		}
		ret.push_back(s);
		reverse(ret.begin(), ret.end());
	}
	return ret;
}

int mod(int a){
	if(a<0){
		return (0-a);
	}
	else{
		return a;
	}
}

bool adjacent(string word1, string word2){
	if(word1.length() == word2.length()){
		int diff = 0;
		for(int i=0; i<word1.length();i++){
			diff+= mod((int)word1[i] - (int)word2[i])>0?1:0;
		}
		if(diff!=1){
			return false;
		}
	}
	else{
		return false;
	}
	return true;
}

int main(){
    //freopen("output.txt","w",stdout);
	string start_word, end_word;
	string word;
	getline(cin ,word);
	word_name.clear();
    graph.clear();
    map<string, int> word_map;
	nr_word = 0;
	while(word.length()!=0){
		if(word_map.find(word) == word_map.end()){
			word_map[word] = nr_word;
			nr_word++;
			word_name.push_back(word);
			vector<int> vec;
			graph.push_back(vec);
		}
		getline(cin, word);
	}
	//Process words and make the graph
	for(int i=0;i<word_name.size()-1;i++){
		for(int j=i+1; j<word_name.size(); j++){
			if(adjacent(word_name[i], word_name[j])){
				graph[word_map[word_name[i]]].push_back(word_map[word_name[j]]);
				graph[word_map[word_name[j]]].push_back(word_map[word_name[i]]);
			}
		}
	}
    bool blank = false;
	while(cin >> start_word >> end_word){
        if(!blank){
            blank = true;
        }
        else{
            cout << endl;
        }
		vector<int> path;
		path = compute_path(word_map[start_word], word_map[end_word]);
		if(path.size()>0){
            for(int i=0;i<path.size();i++){
                cout << word_name[path[i]] << endl;
            }
		}
		else{
            cout << "No solution." << endl;
		}
	}
	return 0;
}
