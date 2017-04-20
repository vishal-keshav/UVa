#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    //freopen("output.txt","w",stdout);
	int T,n,t,m;
	cin >> T;
	while(T--){
		cin >> n >> t >> m;
		vector<int> arrivals(m);
		for(int i=0;i<m;i++){
			cin >> arrivals[i];
		}
		int global_clock = 0;
		int load;
		int arrival_index;
		int nr_trips;
		//Pick smallest left cars initially, remainder
		if(m%n==0){
            arrival_index = n-1;
		}
		else{
            arrival_index = m%n - 1; //Since starting with index 0
		}
		while(1){
			//Unload for fresh loading
			global_clock = max(global_clock,arrivals[arrival_index]);
			//Deliver the loaded cars, update the global clock
			global_clock+=t;
			//Check if all cars have been delivered
			arrival_index+=n;
			if(arrival_index>=m){
				break;
			}
			else{
				//Go back to load more cars
				global_clock+=t;
			}
		}
		//Too clever method for nr_trip calculation
		if(m%n!=0){
            nr_trips = m/n +1;
		}
		else{
            nr_trips = m/n;
		}
		cout << global_clock << " " << nr_trips << endl;
	}
	return 0;
}
