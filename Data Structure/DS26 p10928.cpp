#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct out_degree{
	int index;
	int nr_neighbour;
};

bool comp(struct out_degree elem1, struct out_degree elem2){
	if(elem1.nr_neighbour == elem2.nr_neighbour){
		return (elem1.index<elem2.index);
	}
	return (elem1.nr_neighbour < elem2.nr_neighbour);
}

int count_words(string input){
    int len = input.length();
    int ret = 1;
    if(len==0){
        return 0;
    }
    else{
        for(int i=0;i<len;i++){
            if(input[i]==' '){
                ret++;
            }
        }
        return ret;
    }
}

int main(){
	int T,P;
	string line;
	cin >> T;
	while(T--){
		cin >> P;
		struct out_degree temp;
		vector<struct out_degree> vec;
		cin.ignore();
		for(int i=1;i<=P;i++){
			getline(cin,line);
			temp.index = i;
			temp.nr_neighbour = count_words(line);
			vec.push_back(temp);
		}
		sort(vec.begin(),vec.end(),comp);
		int prev = vec[0].nr_neighbour;
		cout << vec[0].index;
		for(vector<struct out_degree>::iterator iter = vec.begin()+1; iter!=vec.end(); iter++){
			if((*iter).nr_neighbour!=prev){
				break;
			}
			else{
				cout << " " << (*iter).index;
			}
		}
		cout << endl;
	}
	return 0;
}
