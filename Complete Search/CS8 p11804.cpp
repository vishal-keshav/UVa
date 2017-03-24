#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct player{
	string name;
	int attack;
	int defend;
};

vector<struct player> list;

bool comp(struct player p1, struct player p2){
	return (p1.name < p2.name);
}

int checked[10] = {0,0,0,0,0,0,0,0,0,0};

int sum_attack(int i, int j, int k, int l, int m){
	return (list[i].attack + list[j].attack + list[k].attack + list[l].attack + list[m].attack);
}

int sum_defend(int i, int j, int k, int l, int m){
	int total = 0;
	for(int it=0;it<10;it++){
		total+=list[it].defend;
	}
	int temp = list[i].defend;
	temp+=list[j].defend;
	temp+=list[k].defend;
	temp+=list[l].defend;
	temp+=list[m].defend;
	return (total-temp);
}

void check_players(int i, int j, int k, int l, int m){
	for(int index=0;index<10;index++){
		checked[index] = 0;
	}
	checked[i] = 1;
	checked[j] = 1;
	checked[k] = 1;
	checked[l] = 1;
	checked[m] = 1;
}

void print_attackers(void){
	int done = 0;
	cout << "(";
	for(int i=0;i<10;i++){
		if(checked[i]==1){
			cout << list[i].name;
			done++;
			if(done==5){
				break;
			}
			cout << ", ";
		}
	}
	cout << ")" << endl;
}

void print_defenders(void){
	int done = 0;
	cout << "(";
	for(int i=0;i<10;i++){
		if(checked[i]==0){
			cout << list[i].name;
			done++;
			if(done==5){
				break;
			}
			cout << ", ";
		}
	}
	cout << ")" << endl;
}

int main(){
	int T,player_attack, player_defend, nr_case=1;
	string player_name;
	cin >> T;
	while(T--){
		list.clear();
		list.resize(10);
		for(int i=0;i<10;i++){
			cin >> player_name;
			cin >> player_attack >> player_defend;
			struct player temp;
			temp.name = player_name;
			temp.attack = player_attack;
			temp.defend = player_defend;
			list[i] = temp;
		}
		sort(list.begin(), list.end(), comp);
		int total_attack=0;
		int total_defend=0;
		for(int i=0;i<10;i++){
			for(int j=i+1;j<10;j++){
				for(int k=j+1;k<10;k++){
					for(int l=k+1;l<10;l++){
						for(int m=l+1;m<10;m++){
							if(total_attack<sum_attack(i,j,k,l,m)){
								total_attack = sum_attack(i,j,k,l,m);
								total_defend = sum_defend(i,j,k,l,m);
								check_players(i,j,k,l,m);
							}
							else if(total_attack==sum_attack(i,j,k,l,m)){
								if(total_defend < sum_defend(i,j,k,l,m)){
									total_defend = sum_defend(i,j,k,l,m);
									check_players(i,j,k,l,m);
								}
							}
							else{
								//Do not do anything
							}
						}
					}
				}
			}
		}
		cout << "Case " << nr_case << ":" << endl;
		print_attackers();
		print_defenders();

		nr_case++;
	}
	return 0;
}
