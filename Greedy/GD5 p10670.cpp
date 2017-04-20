#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct agency{
	string agency_name;
	int one_rate;
	int half_rate;
	int total_cost;
};

int find_cost(int one_rate, int half_rate, int total_load, int reduced_load){
	int cost = 0;
	int reduction;
	while(total_load>reduced_load){
		//Check if half reduction is possible
		if(total_load/2 >= reduced_load){
			reduction = total_load - total_load/2;
			//Check for optimal cost
			if(reduction*one_rate > half_rate){
				cost+=half_rate;
			}
			else{
				cost+=reduction*one_rate;
			}
			total_load-=reduction;
		}
		else{
			reduction = total_load - reduced_load;
			cost+=one_rate*reduction;
			total_load-=reduction;
		}
	}
	return cost;
}

struct agency parse_agency_info(string info, int N, int M){
	struct agency ret;
	int index_hash, index_comma;
	int nr_word = info.size();
	for(int i=0;i<nr_word;i++){
		if(info[i]==':'){
			index_hash = i;
		}
		if(info[i]==','){
			index_comma = i;
			break;
		}
	}
	ret.agency_name = info.substr(0,index_hash);
	ret.one_rate = atoi(info.substr(index_hash+1, index_comma-index_hash-1).c_str());
	ret.half_rate = atoi(info.substr(index_comma+1,nr_word-index_comma-1).c_str());
    ret.total_cost = find_cost(ret.one_rate, ret.half_rate, N, M);
	return ret;
}

bool comp_cost(struct agency a1, struct agency a2){
	if(a1.total_cost == a2.total_cost){
		return (a1.agency_name < a2.agency_name);
	}
	return (a1.total_cost < a2.total_cost);
}

int main(){
	int T,N,M,L,nr_case=1;
	string info;
	cin >> T;
	while(T--){
		cin >> N >> M >> L;
		vector<struct agency> agency_info(L);
		for(int i=0;i<L;i++){
			cin >> info;
			agency_info[i] = parse_agency_info(info,N,M);
		}
		sort(agency_info.begin(),agency_info.end(),comp_cost);
		cout << "Case " << nr_case << endl;
		for(vector<struct agency>::iterator it = agency_info.begin();it!=agency_info.end();it++){
			cout << (*it).agency_name << " " << (*it).total_cost << endl;
		}
		nr_case++;
	}

	return 0;
}
