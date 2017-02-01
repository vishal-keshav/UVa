#include <iostream>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

struct love_count{
	string country;
	int count;
};

vector<struct love_count> vec;

bool sort_func(struct love_count elem1, struct love_count elem2){
	//return (strcmp(elem1.country, elem2.country) > 0);
	return (elem1.country < elem2.country);
}

bool already_recorded(string country){
	bool found = false;
	for(vector<struct love_count>::iterator it = vec.begin(); it!=vec.end();it++){
		if((*it).country == country){
			(*it).count++;
			found = true;
			break;
		}
	}
	return found;
}

int main(){
	int N;

	string line;
	struct love_count temp_push;
	cin >> N;
	cin.ignore();
	while(N--){
		getline(cin,line);
		line = line.substr(0,line.find(' '));
		if(!already_recorded(line)){
			temp_push.country = line;
			temp_push.count = 1;
			vec.push_back(temp_push);
		}
	}
	sort(vec.begin(),vec.end(),sort_func);
	for(vector<struct love_count>::iterator it = vec.begin();it!=vec.end();it++){
		cout << (*it).country << " " << (*it).count << endl;
	}
	return 0;
}
