#include <stdio.h>
#include <set>

using namespace std;

int main(){
	long int T,n,bill,total_exp;
	while(scanf("%ld",&T) && T){
		//Multiset keeps elements ordered
		multiset<int> my_set;
		total_exp = 0;
		while(T--){
			scanf("%ld",&n);
			while(n--){
				scanf("%ld",&bill);
				my_set.insert(bill);
			}
			total_exp+=(*(--my_set.end()) - (*my_set.begin()));
			my_set.erase(my_set.begin());
			my_set.erase(--my_set.end());
		}
		printf("%ld\n",total_exp);
	}
	return 0;
}
