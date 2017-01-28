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
	double x1,y1,x2,y2,c,swap_elem;
	cin >> T;
	//freopen("output.txt","w",stdout);
	while(T--){
		cin >> N;
		vector<struct elem> vec;
		struct elem temp_elem;
		for(int i=0;i<N;i++){
			cin >> x1 >> y1 >> x2 >> y2 >> c;
			//Preserve values
			if(x1>x2){
				swap_elem = x1;
				x1 = x2;
				x2 = swap_elem;
				swap_elem = y1;
				y1 = y2;
				y2 = swap_elem;
			}
			//Logic for remove negative line segment
            if(y1<=0 && y2 <=0 && (y1+y2)<0){
                continue;
            }
            else if(y1>=0 && y2>=0){
                temp_elem.start_x = x1;
                temp_elem.end_x = x2;
                temp_elem.coeff = c;
                vec.push_back(temp_elem);
            }
            else{
                if(y1>=0){
                    x2 = x1 - ((x1-x1)/(y2-y1))*y1;
                }
                else{
                    x1 = x1 - ((x1-x1)/(y2-y1))*y1;
                }
                temp_elem.start_x = x1;
                temp_elem.end_x = x2;
                temp_elem.coeff = c;
                vec.push_back(temp_elem);
            }
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
		vector<struct elem> ans_vec_n;
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
		//Fill the ans for gaps where there are no coefficient
		for(iter=ans_vec.begin(); (iter+1)!=ans_vec.end(); ++iter){
			if((*iter).end_x == (*(iter+1)).start_x){
                ans_vec_n.push_back((*iter));
			}
			else{
                ans_elem.start_x = (*iter).end_x;
                ans_elem.end_x = (*(iter+1)).start_x;
                ans_elem.coeff = 1.000;
                ans_vec_n.push_back((*iter));
                ans_vec_n.push_back(ans_elem);
			}
		}
		ans_vec_n.push_back((*iter));
		//Start printing ans
		combined_coeff = 1;
		printf("%d\n",ans_vec_n.size()+2);
		printf("-inf %.3f %.3f\n",ans_vec_n[0].start_x,combined_coeff);
		for(vector<struct elem>::iterator it=ans_vec_n.begin(); it!=ans_vec_n.end(); ++it){
			printf("%.3f %.3f %.3f\n", (*it).start_x, (*it).end_x, (*it).coeff);
		}
		printf("%.3f +inf %.3f\n",ans_vec_n[ans_vec_n.size()-1].end_x, combined_coeff);
		if(T!=0){
			printf("\n");
		}
	}
}
