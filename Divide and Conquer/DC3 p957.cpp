#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
	long int Y, P;
	while(cin >> Y >> P){
        vector<long int> elect_year(P,0);
        vector<long int>::iterator last;
        vector<long int>::iterator ans_first;
        vector<long int>::iterator ans_last;
        int max_elects = 0;
        for(long int i=0;i<P;i++){
            cin >> elect_year[i];
        }
        for(vector<long int>::iterator it = elect_year.begin(); it!=elect_year.end(); it++){
            last = upper_bound(it,elect_year.end(), (*it)+Y-1);
            if(last!=elect_year.end()){
                //cout << (*it) << " " << (last-it) << endl;
                if(last-it > max_elects){
                    max_elects = last-it;
                    ans_first = it;
                    ans_last = last-1;
                }
            }
        }
        cout << max_elects << " " <<(*ans_first) << " " << (*ans_last) << endl;
	}
	return 0;
}
