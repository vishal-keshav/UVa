#include <iostream>
#include <stdio.h>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <algorithm>
#include <locale>

using namespace std;

struct budget{
	int cost;
	string recipe_name;
};

bool comp(struct budget elem1, struct budget elem2){
	if(elem1.cost==elem2.cost){
		return (elem1.recipe_name < elem2.recipe_name);
	}
	return (elem1.cost < elem2.cost);
}

string all_capital(string input){
	locale loc;
	for(int i=0;i<input.length();i++){
		input[i] = toupper(input[i],loc);
	}
	return input;
}

int main(){
	int T,m,n,b,k,c,total_cost;
	cin >> T;
	string binding, ingredient, recipe;
	while(T--){
        cin.ignore();
		map<string,int> ingredient_map;
		vector<struct budget> vec;
		struct budget temp;
		getline(cin, binding);
		cin >> m >> n >> b;
		cin.ignore();
		while(m--){
			cin >> ingredient >> c;
			ingredient_map[ingredient] = c;
		}

		while(n--){
            cin.ignore();
			getline(cin, recipe);
			cin >> k;
			total_cost = 0;
			while(k--){
				cin >> ingredient >> c;
				total_cost+=c*ingredient_map[ingredient];
			}
			if(total_cost < b){
				temp.cost = total_cost;
				temp.recipe_name = recipe;
				vec.push_back(temp);
			}
		}
		cout << all_capital(binding) << endl;
		if(vec.size()==0){
			cout << "Too expensive!" << endl;
		}
		else{
			sort(vec.begin(),vec.end(),comp);
			for(vector<struct budget>::iterator iter = vec.begin(); iter!=vec.end(); iter++){
                cout << (*iter).recipe_name << endl;
			}
		}
		cout << endl;
	}
	return 0;
}
