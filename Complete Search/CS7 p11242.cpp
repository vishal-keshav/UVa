#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

vector<double> fron, rear;

bool comp(double a, double b){
	return (a<b);
}

int main(){
	int f,r;
	cin >> f;
	while(f){
		cin >> r;
		fron.resize(f,0.0);
		for(int i=0;i<f;i++){
			cin >> fron[i];
		}
		rear.resize(r,0.0);
		for(int i=0;i<r;i++){
			cin >> rear[i];
		}
		vector<double> rati;
		for(int i=0;i<f;i++){
			for(int j=0;j<r;j++){
                //cout << (double)rear[j]/(double)fron[i] << endl;
				rati.push_back((double)rear[j]/(double)fron[i]);
			}
		}
		sort(rati.begin(), rati.end(), comp);
		int nr_elem = rati.size();
		double ret = 0.0;
		for(int i=1;i<nr_elem;i++){
            //cout << rati[i]/rati[i-1] << endl;
			if(rati[i]/rati[i-1] > ret){
				ret = rati[i]/rati[i-1];
			}
		}
		printf("%.2f\n",ret);
		cin >> f;
	}
	return 0;
}
