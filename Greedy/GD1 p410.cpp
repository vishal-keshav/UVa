#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

struct index_weight{
    int weight;
    int index;
};

struct index_pair_weight{
    int w1, w2;
    int index;
};

bool comp_weight(struct index_weight e1, struct index_weight e2){
    return (e1.weight < e2.weight);
}

bool comp_index(struct index_pair_weight e1, struct index_pair_weight e2){
    return (e1.index < e2.index);
}

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
		//Append with zero weights for rest pairing
		for(int i=S;i<2*C;i++){
			weight.push_back(0);
		}
		//Create index ordered inputs
		vector<struct index_weight> new_weight;
		for(int i=0;i<2*C;i++){
            struct index_weight temp;
            temp.index = i;
            temp.weight = weight[i];
            new_weight.push_back(temp);
		}
		//Sort for optimal pairing
		sort(new_weight.begin(),new_weight.end(),comp_weight);
		double imbalance = 0.00;
		double mean = get_mean(weight,C);
		int nr_chamber=0;
		cout << "Set #" << nr_set <<endl;
		vector<struct index_pair_weight> ans_vec;
		for(int i=0,j=2*C-1;i<j;i++,j--){
            struct index_pair_weight temp;
            if(new_weight[i].index < new_weight[j].index){
                temp.w1 = new_weight[i].weight;
                temp.w2 = new_weight[j].weight;
            }
            else{
                temp.w2 = new_weight[i].weight;
                temp.w1 = new_weight[j].weight;
            }
            temp.index = min(new_weight[i].index,new_weight[j].index);
            ans_vec.push_back(temp);
			imbalance+=absolute((double)(new_weight[i].weight+new_weight[j].weight),mean);
		}
		sort(ans_vec.begin(),ans_vec.end(),comp_index);
		for(int i=0;i<C;i++){
            cout << " " <<nr_chamber << ":";
            if(ans_vec[i].w1!=0){
                cout << " " <<ans_vec[i].w1;
            }
            if(ans_vec[i].w2!=0){
                cout << " " <<ans_vec[i].w2;
            }
            cout << endl;
            nr_chamber++;
		}
        /*while(nr_chamber<C){
            cout << nr_chamber << ": "<< endl;
            nr_chamber++;
        }*/
        printf("IMBALANCE = %0.5f\n\n",imbalance);
		nr_set++;
	}
	return 0;
}
