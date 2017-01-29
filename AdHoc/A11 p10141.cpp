#include <iostream>
#include <stdio.h>
#include <cstring>

using namespace std;

int main(){
	int n,p,r,loops=1;
	float d,best_price,compliance,temp_compliance;
	char line[80],temp_proposal[80],best_contract[80];
	//string line,temp_proposal,best_contract;
	//cin >> n >> p;
	//getline(cin,line);
	scanf("%d %d",&n,&p);
	cin.sync();
	while(n){
		for(int i=0;i<n;i++){
			//cin.getline(line,sizeof(line));
			//getline(cin,line);
			//cout << "Taking input "<< i << endl;
			gets(line);
			//cout << line << endl;

		}
		cin.sync();
		best_price = 1000000000.000;
		compliance = 0;
		for(int i=0;i<p;i++){

			//cin.getline(temp_proposal,sizeof(temp_proposal));
			//getline(cin,temp_proposal);
			gets(temp_proposal);
			//cout << temp_proposal << endl;
			cin.sync();
			//cin >> d >> r;
			//getline(cin,line);
			scanf("%f %d",&d,&r);
			cin.sync();
			for(int j=0;j<r;j++){
				//cout << "Taking input second "<< j << endl;
				//cin.getline(line,sizeof(line));
				//getline(cin,line);
				gets(line);
				//cout << line << endl;
			}
			cin.sync();
			temp_compliance = ((float)r/(float)n);
			//cout << temp_compliance << endl;
			if(compliance < temp_compliance){
				compliance = temp_compliance;
				best_price = d;
				//best_contract = temp_proposal;
				strcpy(best_contract,temp_proposal);
			}
			else if(compliance == temp_compliance && best_price > d){
				best_price = d;
				//best_contract = temp_proposal;
				strcpy(best_contract,temp_proposal);
			}
			else{
				continue;
			}
		}
		cout << "RFP #" << loops << endl;
		cout << best_contract << endl;
		loops++;
		//cin >> n >> p;
		scanf("%d %d",&n,&p);
		cin.sync();
		if(n!=0){
			cout << endl;
		}
	}
	return 0;
}
