#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <stdio.h>

using namespace std;

struct fraction{
	double frac;
	string tree_name;
};

bool comp(struct fraction elem1, struct fraction elem2){
	return (elem1.tree_name < elem2.tree_name);
}

int main(){
	int T;
	long long int total_trees;
	string input;
	cin >> T;
	cin.ignore();
	//scanf("%d\n",&T);
	getline(cin,input);
	//cout.precision(4);
	while(T--){
		total_trees = 0;
		map<string, long int> tree_map;
		while(1){
			getline(cin,input);
			//cout << input << endl;
			if(input.length() == 0){
				break;
			}
			if(tree_map.count(input) == 0){
				tree_map[input] = 1;
			}
			else{
				tree_map[input]++;
			}
			total_trees++;
		}
		vector<struct fraction> vec;
		struct fraction temp_frac;
		for(map<string, long int>::iterator iter = tree_map.begin();iter!=tree_map.end();iter++){
			temp_frac.frac = (double)(((double)(iter->second)*100.0)/(double)total_trees);
			temp_frac.tree_name = iter->first;
			vec.push_back(temp_frac);
		}
		sort(vec.begin(),vec.end(),comp);
		for(vector<struct fraction>::iterator iter = vec.begin();iter!=vec.end();iter++){
			//printf("%s %.4f\n",(*iter).tree_name, (*iter).frac);
			cout << (*iter).tree_name << " ";
			//<<(*iter).frac << endl;
			printf("%.4f\n",(*iter).frac);
		}
		if(T!=0){
            cout << endl;
		}
	}
	return 0;
}
