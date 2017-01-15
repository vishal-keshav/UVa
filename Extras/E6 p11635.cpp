#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

#define INT_MAX 100000000

struct node{
	int city;
	int dist;
	struct node *next;
};

struct q_node{
	int city;
	int dist_covered;
	int hotels_booked;
};

int dp[10001][601];
bool hotel[10001];
struct node **adj_list;

int main(){
	int N,h,temp_h,m;
	int src, dest, dist;
	struct node *temp_node;
	cin >> N;
	while(N){
		//memory setting
		for(int i=0;i<=N;i++){
			hotel[i] = false;
			for(int j=0;j<=601;j++){
				dp[i][j] = INT_MAX;
			}
		}
		cin >> h;
		for(int i=0;i<h;i++){
			cin >> temp_h;
			hotel[temp_h] = true;
		}
		//setting graph memory
		adj_list = new struct node*[N+1];
		for(int i=1;i<=N;i++){
			adj_list[i] = NULL;
		}
		cin >> m;
		for(int i=0;i<m;i++){
			cin >> src >> dest >> dist;
			temp_node = new struct node;
			temp_node->city = dest;
			temp_node->dist = dist;
			temp_node->next = adj_list[src];
			adj_list[src] = temp_node;
			//reverse connection as well
			temp_node = new struct node;
			temp_node->city = src;
			temp_node->dist = dist;
			temp_node->next = adj_list[dest];
			adj_list[dest] = temp_node;
		}
		//Checking the graph
		/*for(int i = 1;i<=N;i++){
			struct node *iter = adj_list[i];
			cout << i << ": ";
			while(iter){
				cout << iter->city << "(" << iter->dist << ") :";
				iter = iter->next;
			}
			cout << endl;
		}*/

		//Initialization of initial conditions
		queue<struct q_node> visits;
		dp[1][0] = 0;
		struct q_node push_q_node;
		struct q_node pop_q_node;
		push_q_node.city = 1;
		push_q_node.dist_covered = 0;
		push_q_node.hotels_booked = 0;
		visits.push(push_q_node);
		while(!visits.empty()){
			pop_q_node = visits.front();
			visits.pop();

			/*visit neighbours of pop_q_node.city given the conditions
			1. neighbout is reachable i.e. dist+neighbour <= 600
			2. reaching neghbour makes dp optimal i.e. dp[neighbor][dist+neighbour] < past value_comp
			3. to go to neighbour, update dp and push neighbour node in visits*/

			//iterte through all neighbours
			temp_node = adj_list[pop_q_node.city];
			while(temp_node){
				if(pop_q_node.dist_covered+temp_node->dist <=600){

					if(dp[temp_node->city][pop_q_node.dist_covered+temp_node->dist] > pop_q_node.hotels_booked){
						push_q_node.city = temp_node->city;
						push_q_node.dist_covered = pop_q_node.dist_covered+temp_node->dist;
						push_q_node.hotels_booked = pop_q_node.hotels_booked;
						visits.push(push_q_node);
						dp[temp_node->city][pop_q_node.dist_covered+temp_node->dist] = pop_q_node.hotels_booked;
						//If neighbour has a bookable hotel
						if(hotel[temp_node->city] && dp[temp_node->city][0] > pop_q_node.hotels_booked + 1){
							//Book it at visit
							push_q_node.city = temp_node->city;
							push_q_node.dist_covered = 0;
							push_q_node.hotels_booked=pop_q_node.hotels_booked+1;
							visits.push(push_q_node);
							dp[temp_node->city][0] = pop_q_node.hotels_booked + 1;
						}
					}
				}
				temp_node = temp_node->next;
			}
		}
		//dp is filled, time to give min of dp[N][i], 0<i<=600
		int min_booked = INT_MAX;
		for(int i=0;i<=600;i++){
			min_booked = min(min_booked,dp[N][i]);
		}
		if(min_booked<INT_MAX){
			cout << min_booked << endl;
		}
		else{
			cout << "-1" << endl;
		}

		cin >> N;
	}


	return(0);
}
