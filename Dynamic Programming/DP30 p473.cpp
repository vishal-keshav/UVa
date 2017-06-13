#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <sstream>
#include <string>

using namespace std;

int n,t,m;
vector<int> input;
vector<vector<vector<int> > > DP;

int max_songs(int index, int current_disc_space, int disc_left){
    //cout << index << " " << current_disc_space << " " << disc_left << endl;
	if(index>=n || disc_left<=0){
		return 0;
	}
	else if(DP[index][current_disc_space][disc_left]!=-1){
        return DP[index][current_disc_space][disc_left];
	}
	else{
		int ret = 0;
		//Choice 1: take song in current disc
		if(current_disc_space>=input[index]){
			ret = max(ret,1+max_songs(index+1,current_disc_space-input[index], disc_left));
		}
		//Choice 2: dont take this song at all
		ret = max(ret, max_songs(index+1,current_disc_space,disc_left));
		//Choice 3: take the song in next disc
		ret = max(ret, max_songs(index,t,disc_left-1));
		DP[index][current_disc_space][disc_left] = ret;
		return ret;
	}
}

int main(){
	int T,temp;
	int nr_case = 1;
	string input_str;
	cin >> T;
	cin.ignore();
	while(T--){
		cin >> n >> t >> m;
		//cin.ignore();
		cin.ignore();
		//cin >> input_str;
		getline(cin,input_str);
        //cout << input_str << endl;
		input.clear();
		stringstream ss(input_str);
		while(ss >> temp){
			input.push_back(temp);
			if(ss.peek()==','){
				ss.ignore();
			}
		}
		/*for(int i=0;i<n;i++){
			cin >> input[i];
		}*/
		DP.clear();
		DP.resize(n,vector<vector<int> >(t+1,vector<int>(m+1,-1)));
		cout << max_songs(0,t,m) << endl;
		if(T){
			cout << endl;
		}
		/*if(nr_case==44){
            cout << input_str << endl;
		}*/
		nr_case++;
	}
	return 0;
}
