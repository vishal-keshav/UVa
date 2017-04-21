#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

struct winer{
	long long int nr_wine;
	long long int location;
};

long long int absolute(long long int a){
	if(a<0){
		return (0-a);
	}
	else{
		return a;
	}
}

int main(){
	long long int n,cost,left,right,reduction;
	cin >> n;
	while(n){
		//vector<int> input(n);
		queue<struct winer> buyer;
		queue<struct winer> seller;
		long long int input;
		for(long long int i=0;i<n;i++){
			cin >> input;
			struct winer temp;
			if(input>0){
				temp.nr_wine = input;
				temp.location = i;
				buyer.push(temp);
			}
			if(input<0){
				temp.nr_wine = -input;
				temp.location = i;
				seller.push(temp);
			}
		}
		cost = 0;
		//Keep popping out buyers from far left and sellers from far left to meet demand
		struct winer temp_buyer;
		struct winer temp_seller;
		while(!buyer.empty()){
			temp_buyer = buyer.front();
			//pick a seller from far left
			temp_seller = seller.front();

			//Case 1: seller completely satisfy buyer
			if(temp_buyer.nr_wine == temp_seller.nr_wine){
				cost+=temp_buyer.nr_wine*absolute(temp_buyer.location-temp_seller.location);
				buyer.pop();
				seller.pop();
			}
			//buyer is satisfied, the seller has more to sell
			else if(temp_buyer.nr_wine < temp_seller.nr_wine){
				cost+=temp_buyer.nr_wine*absolute(temp_buyer.location-temp_seller.location);
				seller.front().nr_wine-= temp_buyer.nr_wine;
				buyer.pop();
			}
			//seller is done, but buyer wants more
			else{
				cost+=temp_seller.nr_wine*absolute(temp_buyer.location-temp_seller.location);
				seller.pop();
				buyer.front().nr_wine-=temp_seller.nr_wine;
			}
		}

		/*for(int i=0;i<n;i++){
			left = i;
			right = i;
			if(input[i]<0){
				continue;
			}
			while(input[i]!=0){
				left = max(-1,left-1);
				right = min(n,right+1);

				if(left!=-1 && input[left]<0){
					reduction = min(-input[left], input[i]);
					input[left]+=reduction;
					input[i]-=reduction;
					cost+=reduction*(i-left);
				}
				if(right!=n && input[right]<0){
					reduction = min(-input[right], input[i]);
					input[right]+=reduction;
					input[i]-=reduction;
					cost+=reduction*(right-i);
				}
			}
		}*/
		cout << cost << endl;
		cin >> n;
	}
	return 0;
}