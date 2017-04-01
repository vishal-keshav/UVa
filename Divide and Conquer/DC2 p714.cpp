#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

#define INT_MAXIMUM 1000000000

int m,k;
vector<long int> pages;
vector<long int> ans;
long int min_max_page;

int main(){
	int N;
	cin >> N;
	while(N--){
		cin >> m >>k;
		pages.clear();
		pages.resize(m);
		min_max_page = INT_MAXIMUM;
		vector<long int> temp;

		long int left=INT_MAXIMUM,right=0,mid;

		for(int i=0;i<m;i++){
            cin >> pages[i];
            left = min(left, pages[i]);
            right+= pages[i];
		}
		while(right>left){
            mid = (left+right)/2;

            int nr_persons = 0;
            long int min_max = 0;
            long int per_person_max = 0;

            for(int i=m-1;i>=0;i--){
                if(per_person_max+pages[i] > mid || i+1 < k-nr_persons){
                    nr_persons++;
                    /*if(nr_persons==k){
                        break;
                    }*/
					temp.push_back(i);
                    min_max= max(min_max,per_person_max);
                    per_person_max = pages[i];
                }
                else{
                    per_person_max+=pages[i];
                }

            }

			if(nr_persons == k-1){
				ans = temp;
			}

            if(min_max > mid || nr_persons>=k){
                //Underassignment
                left = mid;
            }
            else{
				right = mid;
			}

            if((left+right)/2 == mid){
				break;
			}

		}
		for (int i=0; i<m; i++){
			if(i>0){
				cout << " " << pages[i];
			}
			else{
				cout << pages[i];
			}

            if (!ans.empty() && ans.back() == i){
                cout << " /";
                ans.pop_back();
            }
        }
		cout << endl;
	}
	return 0;
}
