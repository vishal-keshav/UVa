#include <iostream>
#include <stdio.h>
#include <vector>
#include <math.h>

using namespace std;

struct outpost{
	double x, y;
};

struct outpost camps[501];

bool visited[501];
int S,P;
double D_temp;

void init_graph(void){
	for(int i=0;i<P;i++){
		visited[i] = false;
	}
}

double dist(int n1, int n2){
	return sqrt(pow(camps[n1].x-camps[n2].x,2.0)+pow(camps[n1].y-camps[n2].y,2.0));
}

void visit_dfs_way(int node){
	//Iterate through all unvisited node, visit it
	for(int i=0;i<P;i++){
		if(i!=node && !visited[i]){
			if(dist(node,i) <= D_temp){
				visited[i] = true;
				visit_dfs_way(i);
			}
		}
	}
}

int nr_sub_graphs(double d){
	int sub_graph = 0;
	D_temp = d;
	for(int i=0;i<P;i++){
		if(!visited[i]){
			visit_dfs_way(i);
			sub_graph++;
		}
	}
	return sub_graph;
}

double absolute(double a, double b){
	if(a<b){
		return (b-a);
	}
	else{
		return (a-b);
	}
}

int main(){
    //freopen("output.txt","w",stdout);
    int T;
    cin >> T;
    while(T--){
		cin >> S >> P;
		for(int i=0;i<P;i++){
			cin >> camps[i].x >> camps[i].y;
		}

		double left = 0.00;
		double right = 10000.00;
		double mid;
		double prev_mid=0.00;
		int nr_graphs;
		while(1){
			init_graph();
			mid = (left+right)/2;
			nr_graphs = nr_sub_graphs(mid);
			if(nr_graphs == S){
				//Check if nothing can be done
				if(absolute(mid,prev_mid) < 0.0001){
					break;
				}
				else{
					prev_mid = mid;
					right = mid;

				}
			}
			else if(nr_graphs < S){
				prev_mid = mid;
				right = mid;
			}
			else{
				prev_mid = mid;
				left = mid;
			}
		}
		printf("%0.2f\n",mid);
    }
	return 0;
}
