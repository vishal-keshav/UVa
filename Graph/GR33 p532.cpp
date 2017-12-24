#include <iostream>
#include <stdio.h>
#include <queue>

using namespace std;


int L, R, C;
int move_x[6] = {0, 0, 0, 0, -1, 1};
int move_y[6] = {0, 0, -1, 1, 0, 0};
int move_z[6] = {-1, 1, 0, 0, 0, 0};

struct loc{
    int x,y,z;
};
char*** mapp;

bool loc_is_null(struct loc location){
    if(location.x == -1 && location.y == -1 && location.z == -1){
        return true;
    }
    return false;
}

bool loc_is_valid(struct loc l){
    if(l.x >=0 && l.x < L && l.y>=0 && l.y<R && l.z>=0 && l.z<C){
        if(mapp[l.x][l.y][l.z] == '.' || mapp[l.x][l.y][l.z] == 'E'){
            return true;
        }
        else{
            return false;
        }
    }
    return false;
}

bool loc_is_end(struct loc l, struct loc e){
    if(l.x == e.x && l.y == e.y && l.z == e.z){
        return true;
    }
    return false;
}

int main(){
    //freopen("output.txt","w",stdout);
    char status;
    cin >> L >> R >> C;
    while(L+R+C !=0){
        struct loc start_loc;
        struct loc end_loc;
        mapp = new char**[L];
        for(int i=0;i<L;i++){
            mapp[i] = new char*[R];
            for(int j=0;j<R;j++){
                mapp[i][j] = new char[C];
                for(int k=0;k<C;k++){
                    cin >> status;
                    mapp[i][j][k] = status;
                    if(status == 'S'){
                        start_loc.x = i;
                        start_loc.y = j;
                        start_loc.z = k;
                    }
                    if(status == 'E'){
                        end_loc.x = i;
                        end_loc.y = j;
                        end_loc.z = k;
                    }
                }
            }
        }
        queue<struct loc> bfs_queue;
        struct loc null_loc;
        null_loc.x = -1;
        null_loc.y = -1;
        null_loc.z = -1;
        bfs_queue.push(start_loc);
        bfs_queue.push(null_loc);
        int nr_moves = 0;
        while(!bfs_queue.empty()){
            struct loc temp = bfs_queue.front();
            bfs_queue.pop();
            if(loc_is_null(temp)){
                if(bfs_queue.empty()){
                    nr_moves = -1;
                    break;
                }
                nr_moves++;
                bfs_queue.push(null_loc);
            }
            else{
                if(loc_is_end(temp, end_loc)){
                    break;
                }
                else{
                    for(int i=0;i<6;i++){
                        struct loc new_loc;
                        new_loc.x = temp.x + move_x[i];
                        new_loc.y = temp.y + move_y[i];
                        new_loc.z = temp.z + move_z[i];
                        if(loc_is_valid(new_loc)){
                            mapp[new_loc.x][new_loc.y][new_loc.z] = '#';
                            bfs_queue.push(new_loc);
                        }
                    }
                }
            }
        }

        if(nr_moves == -1){
            cout << "Trapped!" << endl;
        }
        else{
            cout << "Escaped in " << nr_moves << " minute(s)." << endl;
        }
        cin >> L >> R >> C;
    }
    return 0;
}
