#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int N,M, time_now;
vector<string> city;
vector<string>camera_city;
vector<vector<int> > adj_mat;
vector<int> visited;
vector<int> parent;
vector<int> visit_seq;
vector<int> back_seq;
map<string, int> hash_map;

int find_camera(int node){
  int ret = 0;
  int nr_child = 0;
  bool articulation = false;
  visited[node] = 1;
  visit_seq[node] = time_now;
  back_seq[node] = time_now;
  for(int i=0;i<N;i++){
    if(adj_mat[node][i]==1 && parent[node]!=i && node!=i){
      if(visited[i]==1){
        back_seq[node] = min(back_seq[node], visit_seq[i]);
      }
      else{
        parent[i] = node;
        nr_child++;
        time_now++;
        ret+=find_camera(i);
        back_seq[node] = min(back_seq[node], back_seq[i]);
        if(visit_seq[node] <= back_seq[i] && parent[node]!=node){
          articulation = true;
        }
      }
    }
  }
  if(nr_child > 1 && parent[node]==node && !articulation){
    articulation = true;
  }
  if(articulation){
    camera_city.push_back(city[node]);
    ret++;
  }
  return ret;
}

void print_camera_city(void){
  sort(camera_city.begin(), camera_city.end());
  for(vector<string>::iterator it=camera_city.begin(); it!=camera_city.end(); it++){
    cout << (*it) << endl;
  }
}

int main(){
  //freopen("output.txt","w",stdout);
  string city_name;
  string city1, city2;
  int nr_camera, nr_case=1;
  cin >> N;
  while(N){
    hash_map.clear();
    city.clear();
    for(int i=0;i<N;i++){
      cin >> city_name;
      hash_map[city_name] = i;
      city.push_back(city_name);
    }
    cin >> M;
    adj_mat.clear();
    adj_mat.resize(N, vector<int>(N,0));
    visited.clear();
    visited.resize(N,0);
    visit_seq.clear();
    visit_seq.resize(N);
    back_seq.clear();
    back_seq.resize(N);
    camera_city.clear();
    parent.clear();
    parent.resize(N);
    for(int i=0;i<N;i++){
      parent[i] = i;
    }
    for(int i=0;i<M;i++){
      cin >> city1 >> city2;
      adj_mat[hash_map[city1]][hash_map[city2]] = 1;
      adj_mat[hash_map[city2]][hash_map[city1]] = 1;
    }
    time_now = 0;
    nr_camera = 0;
    for(int i=0;i<N;i++){
      if(visited[i]==0){
        nr_camera+= find_camera(i);
      }
    }
    cout << "City map #" << nr_case << ": " << nr_camera << " camera(s) found" << endl;
    print_camera_city();
    cout << endl;
    cin >> N;
    nr_case++;
  }

  return 0;
}
