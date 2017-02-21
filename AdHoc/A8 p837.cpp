#include <iostream>
#include <algorithm>
#include <vector>
#include <stdio.h>

using namespace std;


struct elem{
	double start_x;
	double end_x;
	double coeff;
};

bool sort_func(struct elem e1, struct elem e2){
	return (e1.start_x < e2.start_x);
}

int main(){
	int T,N;
	double x1,y1,x2,y2,c;
	cin >> T;
	while(T--){
		cin >> N;
		vector<struct elem> vec;
		struct elem temp_elem;
		for(int i=0;i<N;i++){
			cin >> x1 >> y1 >> x2 >> y2 >> c;
			//Preserve values
			if(x1>x2){
				y1 = x1;
				x1 = x2;
				x2 = y1;
			}
			temp_elem.start_x = x1;
			temp_elem.end_x = x2;
			temp_elem.coeff = c;
			vec.push_back(temp_elem);
		}
		//Sort vec
		sort(vec.begin(),vec.end(),sort_func);
#ifdef DEBUG
		for(vector<struct elem>::iterator it=vec.begin(); it!=vec.end(); ++it){
			cout << (*it).start_x << " " << (*it).end_x << " " << (*it).coeff << endl;
		}
#endif
		vector<struct elem>::iterator iter;
		vector<struct elem>::iterator dele;
		vector<struct elem>::iterator temp_iter;
		double combined_coeff,min_end_x;
		vector<struct elem> ans_vec;
		struct elem ans_elem;
		while(vec.size()!=0){
			iter = vec.begin();
			ans_elem.start_x = (*iter).start_x;
			combined_coeff = (*iter).coeff;
			min_end_x = (*iter).end_x;
			temp_iter = iter+1;
			while(temp_iter!=vec.end() && (*temp_iter).start_x==(*iter).start_x){
				combined_coeff*=(*temp_iter).coeff;
				min_end_x = min(min_end_x,(*temp_iter).end_x);
				temp_iter++;
			}
			if(temp_iter!=vec.end()){
				min_end_x = min(min_end_x,(*temp_iter).start_x);	
			}
			temp_iter--;
			while(temp_iter!=iter){
				(*temp_iter).start_x = min_end_x;
				if((*temp_iter).start_x == (*temp_iter).end_x){
					dele = temp_iter;
					temp_iter--;
					vec.erase(dele);
				}
				else{
					temp_iter--;
				}
			}
			//For first element
			(*iter).start_x = min_end_x;
			if((*iter).start_x == (*iter).end_x){
				dele = iter;
				vec.erase(dele);
			}
			ans_elem.end_x = min_end_x;
			ans_elem.coeff = combined_coeff;
			ans_vec.push_back(ans_elem);
		}
		//Start printing ans
		
		combined_coeff = 1;
		printf("%d\n",ans_vec.size()+2);
		printf("-inf %.3f %.3f\n",ans_vec[0].start_x,combined_coeff);
		for(vector<struct elem>::iterator it=ans_vec.begin(); it!=ans_vec.end(); ++it){
			printf("%.3f %.3f %.3f\n", (*it).start_x, (*it).end_x, (*it).coeff);
		}
		printf("%.3f +inf %.3f\n\n",ans_vec[ans_vec.size()-1].end_x, combined_coeff);
	}
}