#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int T;

struct num{
	int digit[4];
};

bool visited[10][10][10][10];


bool num_is_null(struct num e){
	if(e.digit[0]==-1){
		return true;
	}
	return false;
}

bool num_is_end(struct num s, struct num e){
	bool ret = true;
	for(int i=0; i<4;i++){
		if(s.digit[i]!=e.digit[i]){
			ret = false;
			break;
		}
	}
	return ret;
}

bool num_is_valid(struct num e){
	if(!visited[e.digit[0]][e.digit[1]][e.digit[2]][e.digit[3]]){
		return true;
	}
	return false;
}

void num_visit(struct num e){
	visited[e.digit[0]][e.digit[1]][e.digit[2]][e.digit[3]] = true;
}

int compute(struct num s, struct num e){
	int ret = 0;
	queue<struct num> bfs_queue;
	struct num null;
	null.digit[0] = -1;
	bfs_queue.push(s);
	bfs_queue.push(null);
	num_visit(s);
	while(!bfs_queue.empty()){
		struct num temp = bfs_queue.front();
        //cout << temp.digit[0] << " " << temp.digit[1] << " " << temp.digit[2] << " " << temp.digit[3] << endl;
		bfs_queue.pop();
		if(num_is_null(temp)){
			if(bfs_queue.empty()){
				ret = -1;
				break;
			}
			ret++;
			bfs_queue.push(null);
		}
		else{
			if(num_is_end(temp, e)){
				break;
			}
			else{
				struct num elem;
				for(int i=0;i<4;i++){
					for(int j=0;j<4;j++){
						elem.digit[j] = temp.digit[j];
					}
					elem.digit[i] = (temp.digit[i]+1)%10;
					if(num_is_valid(elem)){
						bfs_queue.push(elem);
						num_visit(elem);
					}
					elem.digit[i] = (temp.digit[i]+9)%10;
					if(num_is_valid(elem)){
						bfs_queue.push(elem);
						num_visit(elem);
					}
				}
			}
		}
	}
	return ret;
}

void reset(void){
	for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			for(int k=0;k<10;k++){
				for(int l=0;l<10;l++){
					visited[i][j][k][l] = false;
				}
			}
		}
	}
}

int main(){
    //freopen("output.txt","w",stdout);
	cin >> T;
	int F;
	struct num start, end, forbid;
	while(T--){
		for(int i=0;i<4;i++){
			cin >> start.digit[i];
		}
		for(int i=0; i<4; i++){
			cin >> end.digit[i];
		}
		cin >> F;
		reset();
		for(int i=0;i<F;i++){
			for(int j=0;j<4;j++){
				cin >> forbid.digit[j];
			}
			visited[forbid.digit[0]][forbid.digit[1]][forbid.digit[2]][forbid.digit[3]] = true;
		}
		
		cout << compute(start, end) << endl;
	}

	return 0;
}
