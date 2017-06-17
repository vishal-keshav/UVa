#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

#define INT_MAXIMUM 100000000

using namespace std;

int N,L,C;
vector<int> topic;

int nr_lectures;
int dissatisfaction;

int di(int t){
	if(t==0){
		return 0;
	}
	if(t>10){
		return ((t-10)*(t-10));
	}
	else{
		return -C;
	}
}

void compute_lecture(int topic_index, int time_left, int nr_taken, int total_d){
	if(topic_index>=N){
		if(nr_lectures>=nr_taken){
			nr_lectures = nr_taken;
			/*if(time_left!=L-topic[topic_index-1]){
                total_d+=di(time_left);
			}*/
			total_d+=di(time_left);
			if(dissatisfaction > total_d){
				dissatisfaction = total_d;
			}
		}
	}
	else{
        //cout << topic[topic_index] << " " << nr_taken << endl;
		//Case 1: take the topic in current lecture
		if(topic[topic_index]<=time_left){
			compute_lecture(topic_index+1,time_left-topic[topic_index], nr_taken, total_d);
		}

		//Case 2: take topic in next lecture
		compute_lecture(topic_index+1, L-topic[topic_index], nr_taken+1, total_d+di(time_left));
	}
}

int main(){
	int nr_case = 1;
	cin >> N;
	while(N){
		cin >> L >> C;
		nr_lectures = INT_MAXIMUM;
		dissatisfaction = INT_MAXIMUM;
		topic.clear();
		topic.resize(N);
		for(int i=0; i<N; i++){
			cin >> topic[i];
		}
		compute_lecture(0,L,1,0);
		cout << "Case " << nr_case << ":" << endl;
		cout << "Minimum number of lectures: " << nr_lectures << endl;
		cout << "Total dissatisfaction index: " << dissatisfaction << endl;
		nr_case++;
		cin >> N;
		if(N){
			cout << endl;
		}
	}
	return 0;
}
