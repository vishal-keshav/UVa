#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <utility>
#include <string>

using namespace std;

/*
Part 1: construct graph
Part 2: Apply MST on graph
*/
struct edge{
    pair<int, int> coord;
    int weight;
};
int N,x,y;
vector<string> maze;
vector<pair<int, int> > alien_loc; //This contains start also
pair<int, int> start;

int nr_node;
int nr_edges;
vector<struct edge> edges;

int main(){
    string line;
    pair<int, int> temp;
	cin >> N;
	while(N--){
		cin >> x >> y;
		maze.clear();
		maze.resize(y, vector<char>(x));
		alien_loc.clear();
		cin.ignore();
		for(int i=0;i<y;i++){
			getline(cin, line);
			maze.push_back(line);
			for(int j=0;j<x;j++){
                if(maze[i][j]=='A'){
                    temp.first = i;
                    temp.second = j;
                    alien_loc.push_back(temp);
                }
                if(maze[i][j] == 'S'){
                    start.first = i;
                    start.first = j;
                    alien_loc.push_back(start);
                }
			}
		}
        //Construct graph

        //find mst
	}
	return 0;
}
