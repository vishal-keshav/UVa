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
		int arrival_index = 0;
		while(1){
			//Unload for fresh loading
			load = 0;
			while(load<n && arrival_index<m){
				//Keep on loading
				load++;
				//update global clock for wait
				global_clock = arrivals[arrival_index];
				//wait for next
				arrival_index++;
				/*Check if it can dump current cars
				  and come back before next arrival*/
				if(arrival_index < m){
					if(arrivals[arrival_index]>=global_clock+2*t){
						break;
					}
				}
			}
			//Deliver the loaded cars, update the global clock
			global_clock+=t;
			//Check if all cars have been delivered
			if(arrival_index>=m){
				break;
			}
			else{
				//Go back to load more cars
				global_clock+=t;
			}
		}
		cout << global_clock << endl;
	}
	return 0;
}
