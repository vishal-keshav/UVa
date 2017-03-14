#include <iostream>
#include <stdio.h>
#include <map>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

//#define DEBUG 1

int get_enemy_of(int node);
bool setFriends(int x, int y);
bool setEnemies(int x, int y);
int areFriends(int x, int y);
int areEnemies(int x, int y);

vector<int> uf_set;
vector<int> uf_size;
void init_set(int _size){
	uf_set.resize(_size);
	uf_size.resize(_size);
	for(int i=0; i<_size;i++){
		uf_set[i] = i;
		uf_size[i] = 1;
	}
}
int uf_find(int node){
	return (uf_set[node]==node?node:uf_set[node]=uf_find(uf_set[node]));
}
bool uf_same_set(int node1, int node2){
	return (uf_find(node1)==uf_find(node2));
}
void uf_union(int node1, int node2){
	if(uf_same_set(node1, node2)){
		return;
	}
	int size1 = uf_size[uf_find(node1)];
	int size2 = uf_size[uf_find(node2)];
	uf_set[uf_find(node1)] = uf_find(node2);
	uf_size[uf_find(node1)] = size1 + size2;
}


map<int, int> enemy_of;

int get_enemy_of(int node){
	if(enemy_of.count(uf_find(node))==0){
		return -1;
	}
	else{
		return (enemy_of[uf_find(node)]);
	}
}

bool setFriends(int x, int y){
	/*
	We apply the rule
	x~y, y~z => x~z for union
	x~y <=> y~x (taken care by union)
	x~y, y*z => x*z
	*/
	if(areEnemies(x,y)==1){
		return false;
	}
	int x_enemy = get_enemy_of(x);
	int y_enemy = get_enemy_of(y);
	if(areEnemies(x_enemy, y_enemy)==1){
		return false;
	}
	//There are no problmes, we can combine constrained to the rule
	if(x_enemy<0 && y_enemy<0){
		//Just combine them
		uf_union(x,y);
	}
	else if(x_enemy < 0){
		uf_union(x,y);
		enemy_of[uf_find(x)] = uf_find(y_enemy);
		enemy_of[uf_find(y_enemy)] = uf_find(x);
	}
	else if(y_enemy < 0){
		uf_union(x,y);
		enemy_of[uf_find(y)] = uf_find(x_enemy);
		enemy_of[uf_find(x_enemy)] = uf_find(y);
	}
	else{
		uf_union(x,y);
		uf_union(x_enemy,y_enemy);
		enemy_of[uf_find(x)] = uf_find(x_enemy);
		enemy_of[uf_find(x_enemy)] = uf_find(x);
	}
	return true;
}

bool setEnemies(int x, int y){
	/*
	We apply the rule
	x*y <=> y*x (taken care by map both side)
	Not x*x (no such entries in map)
	x*y, y*z => x~z
	*/
	if(areFriends(x,y)==1){
		return false;
	}
	int x_enemy = get_enemy_of(x);
	int y_enemy = get_enemy_of(y);
	if(areEnemies(x,y_enemy)==1){
		return false;
	}
	if(areEnemies(x_enemy,y)==1){
		return false;
	}
	if(x_enemy >= 0){
		uf_union(x_enemy,y);
	}
	if(y_enemy >= 0){
		uf_union(x,y_enemy);
	}
	//Update enemy_of map
	enemy_of[uf_find(x)] = uf_find(y);
	enemy_of[uf_find(y)] = uf_find(x);
	return true;
}

int areFriends(int x, int y){
	//Error checking
	if(x<0 || y<0){
		return 0;
	}
	if(uf_same_set(x,y)){
		return 1;
	}
	else{
		return 0;
	}
}

int areEnemies(int x, int y){
	//Error checking
	if(x<0 || y<0){
		return 0;
	}
	if(areFriends(x,y)==1){
		return 0;
	}
	if(enemy_of.count(uf_find(x))!=0){
		if(enemy_of[uf_find(x)] == uf_find(y)){
			return 1;
		}
		else{
			return 0;
		}
	}
	return 0;
}




int main(){
    //freopen("output.txt","w",stdout);
	int M,N,p,E,prev_E;
	cin >> M;
	while(M--){
		cin >> N;
		init_set(201);
		vector<int> vec;
		//map<int,int> enemy_of;
		enemy_of.clear();
		set<int> invited, not_invited;
		for(int i=1;i<=N;i++){
			cin >> p;
			for(int j=0;j<p;j++){
				cin >> E;
				if(E>N){
                    continue;
				}
				if(!setEnemies(i,E)){

					//not_invited.insert(i);
					//not_invited.insert(E);
					vec.push_back(i);
                    vec.push_back(E);
#ifdef DEBUG
                    cout << "Inconsistancy found" << endl;
#endif
				}
			}
		}
#ifdef DEBUG
        for(int i=1;i<=N;i++){
            cout << i << " belongs to " << uf_find(i)<<endl;
            if(enemy_of.count(uf_find(i))==0){
                cout << i << " got no enemy" << endl;
            }
            else{
                cout << i << " got enemy group " << uf_find(enemy_of[uf_find(i)]) << endl;
            }
        }
#endif
        for(vector<int>::iterator it = vec.begin(); it!=vec.end();it++){
            not_invited.insert(uf_find(*it));
            if(enemy_of.count(uf_find(*it))!=0){
                not_invited.insert(uf_find(enemy_of[uf_find(*it)]));
            }
        }
		int total_invited = 0;
		set<int>::iterator iter_invited;
		set<int>::iterator iter_not_invited;
        //bool taken_care;
		for(int i=1;i<=N;i++){
			/*if(enemy_of.count(uf_find(i))==0){
				total_invited+=uf_size[uf_find(i)];
				invited.insert(uf_find(i));
				continue;
			}*/
			iter_invited = invited.find(uf_find(i));
			iter_not_invited = not_invited.find(uf_find(i));
			/*taken_care = false;
            if(iter_invited==invited.end() && iter_not_invited==not_invited.end()){
                iter_not_invited = not_invited.find(uf_find(i));
                iter_invited = invited.find(uf_find(enemy_of[uf_find(i)]));
                if(iter_invited==invited.end() && iter_not_invited==not_invited.end()){
                    taken_care = true;
                }
            }*/

			if(iter_invited==invited.end() && iter_not_invited==not_invited.end()){
				//Invite the larger group
#ifdef DEBUG
				cout << "Processing for " << i << endl;
#endif
				if(uf_size[uf_find(i)] > uf_size[uf_find(enemy_of[uf_find(i)])]){
					total_invited+=uf_size[uf_find(i)];
					invited.insert(uf_find(i));
					not_invited.insert(uf_find(enemy_of[uf_find(i)]));
#ifdef DEBUG
                    cout << uf_find(i) << " is invited!" << endl;
					cout << uf_find(enemy_of[uf_find(i)]) << " is not invited!" << endl;
#endif
				}
				else{
                    total_invited+=uf_size[uf_find(enemy_of[uf_find(i)])];
					not_invited.insert(uf_find(i));
					invited.insert(uf_find(enemy_of[uf_find(i)]));
#ifdef DEBUG
                    cout << uf_find(i) << " is not invited." << endl;
					cout << uf_find(enemy_of[uf_find(i)]) << " is invited." << endl;
#endif
				}
			}
		}
		cout << total_invited << endl;
	}

	return 0;
}
