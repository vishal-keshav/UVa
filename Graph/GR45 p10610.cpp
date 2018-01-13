#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <sstream>
#include <string>
#include <queue>

using namespace std;

float v, m;
struct hole{
	float x,y;
};
struct hole start_hole;
struct hole end_hole;
vector<struct hole> holes;
vector<bool> visited;

float dist(float x, float y){
	return (x*x + y*y);
}

bool reachable(struct hole s, struct hole e){
	if(dist(s.x-e.x, s.y-e.y) < (v*m*60.0)*(v*m*60.0)){
		return true;
	}
	return false;
}

int compute_holes(void){
	int ret = 0;
	queue<struct hole> bfs_queue;
	struct hole null;
	null.x = -1;
	bfs_queue.push(start_hole);
	bfs_queue.push(null);
	while(!bfs_queue.empty()){
		struct hole temp = bfs_queue.front();
		bfs_queue.pop();
		if(temp.x == -1){
			if(bfs_queue.empty()){
				ret = -1;
				break;
			}
			ret++;
			bfs_queue.push(null);
		}
		else{
			if(reachable(temp, end_hole)){
				break;
			}
			else{
				for(int i=0;i<holes.size();i++){
					if(!visited[i] && reachable(temp, holes[i])){
						bfs_queue.push(holes[i]);
						visited[i] = true;
					}
				}
			}
		}
	}
	return ret;
}

int main(){
    //freopen("output.txt","w",stdout);
	cin >> v >> m;
	string line;
	while(v+m){
		cin >> start_hole.x >> start_hole.y;
		cin >> end_hole.x >> end_hole.y;
		holes.clear();
		visited.clear();
		cin.ignore();
		getline(cin, line);
		while(line.length()>0){
			stringstream ss(line);
			struct hole temp;
			ss >> temp.x >> temp.y;
			holes.push_back(temp);
			visited.push_back(false);
			getline(cin, line);
		}
		/*for(int i=0;i<holes.size();i++){
			cout << holes[i].x << " " << holes[i].y << endl;
		}*/
		int nr_holes = compute_holes();
		if(nr_holes>=0){
			cout << "Yes, visiting " << nr_holes << " other holes." << endl;
		}
		else{
			cout << "No." << endl;
		}
		cin >> v >> m;
	}

	return 0;
}
