#include <iostream>
#include <stdio.h>
#include <map>
#include <vector>

using namespace std;

//Function declaration//
int get_enemy_of(int node);
bool setFriends(int x, int y);
bool setEnemies(int x, int y);
int areFriends(int x, int y);
int areEnemies(int x, int y);


vector<int> uf_set(10000);
void init_set(int _size){
	uf_set.resize(_size);
	for(int i=0;i<_size;i++){
		uf_set[i] = i;
	}
}
int uf_find(int node){
	return (uf_set[node]==node?node:uf_set[node]=uf_find(uf_set[node]));
}
void uf_union(int node1, int node2){
	uf_set[uf_find(node1)] = uf_find(node2);
}
bool uf_same_set(int node1, int node2){
	return (uf_find(node1)==uf_find(node2));
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
	int T,c,x,y;
	cin >> T;
	init_set(T);
	while(1){
		cin >> c >> x >> y;
		if(c==0){
			break;
		}
		switch(c){
			case 1:
				if(!setFriends(x,y)){
					cout << "-1" << endl;
				}
				break;
			case 2:
				if(!setEnemies(x,y)){
					cout << "-1" << endl;
				}
				break;
			case 3:
				cout << areFriends(x,y) << endl;
				break;
			case 4:
				cout << areEnemies(x,y) << endl;
				break;
		}
	}
	return 0;
}
