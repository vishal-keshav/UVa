#include <stdio.h>
#include <set>

using namespace std;

int main(){
	int T,n,bill,total_exp;
	while(scanf("%d",&T) && T){
		//Multiset keeps elements ordered
		multiset<int> my_set;
		total_exp = 0;
		while(T--){
			scanf("%d",&n);
			while(n--){
				scanf("%d",&bill);
				my_set.insert(bill);
			}
			total_exp+=(*(--my_set.end()) - (*my_set.begin()));
			my_set.erase(my_set.begin());
			my_set.erase(--my_set.end());
		}
		printf("%d\n",total_exp);
	}
	return 0;
}
