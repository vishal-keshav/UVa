#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

int main(){
	int N;
	cin >> N;
	while(N){
		vector<int> bet(N);
		for(int i=0;i<N;i++){
			cin >> bet[i];
		}
		int running_max = 0, last_max = 0;
		for(int i=0;i<N;i++){
			running_max+=bet[i];
			if(running_max < 0){
				running_max = 0;
			}
			if(last_max < running_max){
				last_max = running_max;
			}
		}
		if(last_max){
			cout << "The maximum winning streak is " << last_max << "." << endl;
		}
		else{
			cout << "Losing streak." << endl;
		}
		
		cin >> N;
	}
	
	
}