#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

int main(){
    //freopen("output.txt","w",stdout);
	vector<int> input;
	int temp;
	while(!cin.eof() && cin >> temp && temp!=-10000){
		input.push_back(temp);
	}
	//Process in nlogn way
	vector<int> lis;
	//Initialization
	int nr_input = input.size();
	int nr_lis_list = 1;
	lis.push_back(input[0]);
	for(int i=1;i<nr_input;i++){
		//Check if lis can be extended
		if(input[i]>lis[nr_lis_list-1]){
			lis.push_back(input[i]);
			nr_lis_list++;
		}
		else{
			//Check if the smallest element greater that input[i] can be replaced
			vector<int>::iterator temp = lower_bound(lis.begin(),lis.end(), input[i]);
			if(temp!=lis.end()){
				(*temp) = input[i];
			}
		}
	}
    cout << lis.size() << endl << "-" << endl;
	for(int i=0;i<nr_lis_list;i++){
		cout << lis[i] << endl;
	}

	return 0;
}
