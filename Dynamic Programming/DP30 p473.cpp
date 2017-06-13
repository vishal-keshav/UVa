#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

int n,t,m;
vector<int> input;


int max_songs(int index, int current_disc_space, int disc_left){
    //cout << index << " " << current_disc_space << " " << disc_left << endl;
	if(index>=n || disc_left<=0 || current_disc_space<=0){
		return 0;
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
		ret = max(ret, 1+max_songs(index+1,t-input[index],disc_left-1));
		return ret;
	}
}

int main(){
	cin >> n >> t >>m;
	input.resize(n);
	for(int i=0;i<n;i++){
		cin >> input[i];
	}
	cout << max_songs(0,t,m) << endl;

	return 0;
}
