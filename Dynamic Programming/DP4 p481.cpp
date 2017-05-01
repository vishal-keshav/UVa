/* Special mention to these two sources to solve this problem

http://www.geeksforgeeks.org/longest-monotonically-increasing-subsequence-size-n-log-n/

http://stackoverflow.com/questions/2631726/how-to-determine-the-longest-increasing-subsequence-using-dynamic-programming

*/

#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <stack>

using namespace std;

int main(){
    //freopen("output.txt","w",stdout);
	vector<int> input;
	int temp;
	while(!cin.eof() && cin >> temp){
		input.push_back(temp);
	}
	//Process in nlogn way
	vector<int> lis;
	vector<int> lis_index;
	vector<int> parent(input.size());
	//Initialization
	int nr_input = input.size();
	int nr_lis_list = 1;
	lis.push_back(input[0]);
	lis_index.push_back(0);
	parent[0] = -1;
	for(int i=1;i<nr_input;i++){
		//Check if lis can be extended
		if(input[i]>lis[nr_lis_list-1]){
			parent[i] = lis_index[nr_lis_list-1];
			lis.push_back(input[i]);
			lis_index.push_back(i);
			nr_lis_list++;
		}
		else{
			//Check if the smallest element greater that input[i] can be replaced
			vector<int>::iterator temp = lower_bound(lis.begin(),lis.end(), input[i]);
			//Case 1: smallest element found
			int temp_index = temp-lis.begin();
			if(temp_index==0){
				//A new series can be started from here
				(*temp) = input[i];
				lis_index[temp_index] = i;
				parent[i] = -1;
			}
			else{
				(*temp) = input[i];
				lis_index[temp_index] = i;
				parent[i] = lis_index[temp_index-1];
			}
		}
	}
    //cout << lis.size() << endl << "-" << endl;
	/*for(int i=0;i<nr_lis_list;i++){
		cout << lis[i] << endl;
	}*/
	stack<int> result;
	int iter_index = lis_index[nr_lis_list-1];
	while(iter_index!=-1){
		//cout << input[iter_index] << endl;
		result.push(input[iter_index]);
		iter_index = parent[iter_index];
	}
	cout << result.size() << endl << "-" << endl;
	while(!result.empty()){
		cout << result.top() << endl;
		result.pop();
	}

	return 0;
}
