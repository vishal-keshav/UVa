#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

vector<int> track;
vector<int> temp;
vector<int> result;
int max_recording;

int N,T;

void record_track(int track_id, int total_length){
	//Base case
	if(track_id >= T){
		if(max_recording<total_length && total_length <=N){
			max_recording = total_length;
			result = temp;
		}
	}
	else{
		if(total_length>N){
			return;
		}
		//Case 1: Record this track
		temp.push_back(track[track_id]);
		record_track(track_id+1, total_length+track[track_id]);
		temp.pop_back();
		//Case 2: Dont record this track
		record_track(track_id+1, total_length);
	}
}

int main(){

	while(cin >> N){
		cin >> T;
		track.clear();
		result.clear();
		max_recording = 0;
		track.resize(T);
		for(int i=0;i<T;i++){
			cin >> track[i];
		}
		record_track(0,0);
		for(vector<int>::iterator it = result.begin();it!=result.end();it++){
			cout << (*it) << " ";
		}
		cout << "sum:" << max_recording << endl;
	}
	return 0;
}