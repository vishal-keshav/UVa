#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

int main(){
	int n,cost,left,right,reduction;
	cin >> n;
	while(n){
		vector<int> input(n);
		for(int i=0;i<n;i++){
			cin >> input[i];
		}
		cost = 0;
		for(int i=0;i<n;i++){
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
		}
		cout << cost << endl;
		cin >> n;
	}
	return 0;
}
