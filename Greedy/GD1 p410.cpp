#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

double get_mean(vector<int> w, int c){
	double ret = 0.00;
	for(vector<int>::iterator it = w.begin(); it!=w.end(); it++){
		ret+=(double)(*it);
	}
	return (double)(ret/(double)c);
}

double absolute(double a, double b){
	if(a<b){
		return (b-a);
	}
	else{
		return (a-b);
	}
}

int main(){
	int C,S,nr_set=1;
	while(cin >> C >> S){
		vector<int> weight(S);
		for(int i=0;i<S;i++){
			cin >> weight[i];
		}
		double imbalance = 0.00;
		double mean = get_mean(weight,C);
		int nr_chamber=0;
		cout << "Set #" << nr_set <<endl;
		while(!weight.empty()){
			vector<int>::iterator first = weight.begin();
			vector<int>::iterator second = weight.end();
			double temp_diff = absolute((double)(*first),mean);
			for(vector<int>::iterator it=first+1;it!=weight.end();it++){
				if(temp_diff > absolute((double)((*first)+(*it)),mean)){
					temp_diff = absolute((double)((*first)+(*it)),mean);
					second = it;
				}
			}
			imbalance+=temp_diff;
			cout << nr_chamber << ": " << (*first);

			if(second!=weight.end()){
				cout << " " << (*second);
				weight.erase(first);
				//First is removed, so idex will reduce by 1 for second
				weight.erase(second-1);
			}
			else{
                weight.erase(first);
			}
			cout << endl;
			nr_chamber++;
		}
        while(nr_chamber<C){
            cout << nr_chamber << ": "<< endl;
            nr_chamber++;
        }
        //cout << "IMBALANCE = " << imbalance << endl << endl;
        printf("IMBALANCE = %0.5f\n\n",imbalance);
		nr_set++;
	}
	return 0;
}
