#include <iostream>
#include <string>
using namespace std;

struct vertex{
	int x;
	int y;
};

struct vertex points[4];

void swap(struct vertex *a, struct vertex *b){
	struct vertex temp = (*a);
	(*a) = (*b);
	(*b) = temp;
	return;
}

bool same_center(int p1, int p2, int p3, int p4){
	int center_x1 = (points[p1].x + points[p2].x)/2;
	int center_y1 = (points[p1].y + points[p2].y)/2;
	int center_x2 = (points[p3].x + points[p4].x)/2;
	int center_y2 = (points[p3].y + points[p4].y)/2;
	if(center_x1 == center_x2 && center_y1 == center_y2){
		return true;
	}
	return false;
}

bool type_one(void){
	if(same_center(0,1,2,3)){
		swap(&points[1],&points[2]);
		return true;
	}
	if(same_center(0,2,1,3)){
		return true;
	}
	if(same_center(0,3,1,2)){
		swap(&points[2],&points[3]);
		return true;
	}
	return false;
}

int dist(struct vertex p1, struct vertex p2){
	return ((p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y));
}

bool is_square(void){
	int s1 = dist(points[0],points[1]);
	int s2 = dist(points[1],points[2]);
	int s3 = dist(points[2],points[3]);
	int s4 = dist(points[3],points[0]);
	return (s1==s2 && s2==s3 && s1==s3);
}

bool is_same_slope(int p1, int p2, int p3, int p4){
	if((points[p2].y-points[p1].y)*(points[p4].x-points[p3].x)\
		== ((points[p4].y-points[p3].y)*(points[p2].x-points[p1].x))){
		return true;	
	}
	return false;
}

bool is_trapezium(void){
	if(is_same_slope(0,1,2,3)){
		return true;
	}
	if(is_same_slope(0,2,1,3)){
		return true;
	}
	if(is_same_slope(0,3,1,2)){
		return true;
	}
	return false;
}

string determine_shape(bool symmetric){
	string ret;
	if(symmetric){
		if(dist(points[0],points[2]) == dist(points[1],points[3])){
			if(is_square()){
				ret = "Square";
			}
			else{
				ret = "Rectangle";
			}
		}
		else{
			if(is_square()){
				ret = "Rhombus";
			}
			else{
				ret = "Parallelogram";
			}
		}
	}
	else{
		if(is_trapezium()){
			ret = "Trapezium";
		}
		else{
			ret = "Ordinary Quadrilateral";
		}
	}
	return ret;
}

int main(){
	int T,test_case=1;
	cin >> T;
	while(T--){
		for(int i=0;i<4;i++){
			cin >> points[i].x >> points[i].y;
		}
		/*Concept: If center of diagonal points equates,
		then shape is from one of the following:
		Square,Rectangle,Rhombus,Parallelogram (type 1)
		else
		Trapezium,Ordinary Qudrilateral (type 2)*/
		if(type_one()){
			cout << "Case "<<test_case << ": " << determine_shape(true) << endl;
		}
		else{
			cout << "Case "<<test_case << ": " << determine_shape(false) << endl;
		}
		test_case++;
	}
	return 0;
}