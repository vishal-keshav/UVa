#include <iostream>
#include <stdio.h>
#include <vector>
#include <math.h>

using namespace std;

#define INT_MAXIMUM 10000000

vector<double> station;
vector<double> per_gallon;
double min_cost;

int total_hops;
double milage;
double car_cap;

void init(int _size, double dest_dist){
	station.clear();
	per_gallon.clear();
	station.resize(_size);
	per_gallon.resize(_size);
	station[0] = 0;
	per_gallon[0] = 0;
	station[_size-1] = dest_dist;
	per_gallon[_size-1] = 0;
	min_cost = INT_MAXIMUM;
	total_hops = _size;
}

double round(double input){
	input = (input*100.0);
	if(input < 0){
		input = ceil(input-0.5);
	}
	else{
		input = floor(input+0.5);
	}
	return input/100.0;
}

void travel(double spent, int current_hop, int last_fill){
	//Base case
	//cout << "Case: " << spent << " " << current_hop << " " << last_fill << endl;
	if(current_hop>=total_hops-1){
		if(min_cost > spent){
			min_cost = spent;
		}
		return;
	}
	else{
		//Decide if we have to fill up the gallon
		//cout << "Case: " << spent << " " << current_hop << " " << last_fill << endl;
		double dist_covered = station[current_hop] - station[last_fill];
		double dist_to_cover = station[current_hop+1] - station[current_hop];
		double petrol_left = car_cap - (dist_covered/milage);//In gallons
		//cout << dist_covered << " " << dist_to_cover << " " << petrol_left << endl;
		if(petrol_left > car_cap/2){
			if(petrol_left*milage < dist_to_cover){
				//Fill
				travel(spent+2+round(((car_cap-petrol_left)*per_gallon[current_hop])/100),current_hop+1,current_hop);
			}
			else{
				//Do not fill
				travel(spent, current_hop+1, last_fill);
				//Fill
				//travel(spent+2+((car_cap-petrol_left)*per_gallon[current_hop])/100,current_hop+1,current_hop);
			}
		}
		else{
			if(petrol_left*milage < dist_to_cover){
				//Fill
				travel(spent+2+round(((car_cap-petrol_left)*per_gallon[current_hop])/100),current_hop+1,current_hop);
			}
			else{
				//Do not fill
				travel(spent, current_hop+1, last_fill);
				//Fill
				travel(spent+2+round(((car_cap-petrol_left)*per_gallon[current_hop])/100),current_hop+1,current_hop);
			}
		}
	}
}

int main(){
	double dest_dist,initial_cost;
	int hops,nr_case=1;
	cin >> dest_dist;
	while(dest_dist!=-1){
		cin >> car_cap >> milage >> initial_cost;
		cin >> hops;
		init(hops+2, dest_dist);
		for(int i=1;i<=hops;i++){
			cin >> station[i] >> per_gallon[i];
		}
		travel(initial_cost,1,0);
		cout << "Data Set #" << nr_case << endl;
		//cout << "minimum cost = $" << min_cost << endl;
		printf("minimum cost = $%.2f\n",min_cost);

		nr_case++;
		cin >> dest_dist;
	}
	return 0;
}
