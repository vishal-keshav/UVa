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
		sort(weight.begin(),weight.end());
		int left = 0;
		int right = S-1;
		double imbalance = 0.00;
		double mean = get_mean(weight,C);
		double left_abs, right_abs, left_right_abs;
		int nr_chamber=0;
		cout << "Set #" << nr_set <<endl;
		while(left<right){
			//Case 1: left is good
			left_abs = absolute((double)weight[left],mean);
			//Case 2: right is good
			right_abs = absolute((double)weight[right],mean);
			//Case 3: both left and right make sense
			left_right_abs = absolute((double)(weight[left]+weight[right]),mean);
			//Select the case which gives minimum absolute difference
			if(left_abs<right_abs){
				if(left_abs<left_right_abs){
					cout << nr_chamber << ": " << weight[left] << endl;
					left++;
					nr_chamber++;
					imbalance+=left_abs;
				}
				else{
					cout << nr_chamber << ": " << weight[left] << " " << weight[right] << endl;
					left++;
					right--;
					nr_chamber++;
					imbalance+=left_right_abs;
				}
			}
			else{
				if(right_abs<left_right_abs){
					cout << nr_chamber << ": " << weight[right] << endl;
					right--;
					nr_chamber++;
					imbalance+=right_abs;
				}
				else{
					cout << nr_chamber << ": " << weight[left] << " " << weight[right] << endl;
					left++;
					right--;
					nr_chamber++;
					imbalance+=left_right_abs;
				}
			}
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
