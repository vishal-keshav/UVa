#include <iostream>
#include <stdio.h>
#include <cstring>

using namespace std;

int main(){
	int n,p,r,loops=1;
	double d,best_price,compliance,temp_compliance;
	//char line[80],temp_proposal[80],best_contract[80];
	string line,temp_proposal,best_contract;
	cin >> n >> p;
	//getline(cin,line);
	//scanf("%d %d",&n,&p);
	while(n){
		for(int i=0;i<n;i++){
			//cin.getline(line,sizeof(line));
			//getline(cin,line);
			//cout << "Taking input "<< i << endl;
			cin.ignore();
			getline(cin,line);
			//cout << line << endl;

		}
		best_price = 10000000;
		compliance = -1;
		for(int i=0;i<p;i++){

			//cin.getline(temp_proposal,sizeof(temp_proposal));
			//getline(cin,temp_proposal);
			getline(cin,temp_proposal);
			//cout << temp_proposal << endl;
			//cin >> d >> r;
			//getline(cin,line);
			scanf("%lf %d\n",&d,&r);
			temp_compliance = ((double)r/(double)n);
			//cout << temp_compliance << endl;
			if(compliance < temp_compliance){
				compliance = temp_compliance;
				best_price = d;
				best_contract = temp_proposal;
				//strcpy(best_contract,temp_proposal);
			}
			else if(compliance == temp_compliance && best_price > d){
				best_price = d;
				best_contract = temp_proposal;
				//strcpy(best_contract,temp_proposal);
			}
			for(int j=0;j<r;j++){
				//cout << "Taking input second "<< j << endl;
				//cin.getline(line,sizeof(line));
				//getline(cin,line);
				//cin.ignore();
				getline(cin,line);
				//cout << line << endl;
			}

		}
		cout << "RFP #" << loops << endl;
		cout << best_contract << endl;
		loops++;
		cin >> n >> p;
		if(n!=0){
			cout << endl;
		}
	}
	return 0;
}
