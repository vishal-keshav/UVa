#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>

using namespace std;

int move_x[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
int move_y[8] = {1, 2, 2, 1, -1, -2, -2, -1};
bool visited[8][8];

bool node_is_null(pair<int, int> node){
    if(node.first == -1 && node.second == -1){
        return true;
    }
    return false;
}

bool node_is_end(pair<int, int> node, pair<int, int> end_node){
    if(node.first == end_node.first && node.second == end_node.second){
        return true;
    }
    return false;
}

bool node_is_valid(pair<int, int> node){
    if(node.first >=0 && node.first <8 && node.second >=0 && node.second < 8){
        return true;
    }
    return false;
}

int main(){
    string input;
    int start_x, start_y;
    int end_x, end_y;
    int nr_moves;
    while(cin >> input){
        start_x = (input[0] - 'a');
        start_y = (input[1] - '1');
        cin >> input;
        end_x = (input[0] - 'a');
        end_y = (input[1] - '1');
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                visited[i][j] = false;
            }
        }
        pair<int, int> start_pair(start_x, start_y);
        pair<int, int> end_pair(end_x, end_y);
        pair<int, int> null_pair(-1, -1);
        queue<pair<int, int> > bfs_queue;
        bfs_queue.push(start_pair);
        bfs_queue.push(null_pair);
        nr_moves = 0;
        while(!bfs_queue.empty()){
            pair<int, int> temp = bfs_queue.front();
            bfs_queue.pop();
            if(node_is_null(temp)){
                nr_moves++;
                bfs_queue.push(null_pair);
            }
            else{
                visited[temp.first][temp.second] = true;
                if(node_is_end(temp, end_pair)){
                    break;
                }
                else{
                    pair<int, int> to_push;
                    for(int i=0; i< 8; i++){
                        to_push.first = temp.first + move_x[i];
                        to_push.second = temp.second + move_y[i];
                        if(node_is_valid(to_push) && !visited[to_push.first][to_push.second]){
                            bfs_queue.push(to_push);
                        }
                    }
                }
            }
        }
        cout << "To get from " << (char)(start_pair.first + 'a') << (start_pair.second+1) \
                << " to " << (char)(end_pair.first + 'a') << (end_pair.second + 1) << \
                " takes " << nr_moves << " knight moves." << endl;
    }
    return 0;
}
