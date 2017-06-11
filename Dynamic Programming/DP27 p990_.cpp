//============================================================================
// Name        : UVA.cpp
// Author      : moustafa
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
// URL: https://codingnerd.wordpress.com/2016/02/12/uva-990-solution/
//============================================================================

//Even this solution I found online gives incorrect answer
//Reason: Problem setter was lousy in defining which answer is taken as correct one if there are more than one correct output, so fuck you problem setter.


#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;
int t, w, n, val[110], cost[110];
int dp[2000][100];
bool visits[2000][110];
bool mark[35];
int solve(int remt, int indx) {
    if (remt == 0 || indx == n) {
        return 0;
    }
    if (dp[remt][indx] != -1) {
        return dp[remt][indx];
    }
    if (cost[indx] > remt) {
        return dp[remt][indx] = solve(remt, indx + 1);
    } else {
        int a = solve(remt - cost[indx], indx + 1) + val[indx];
        int b = solve(remt, indx + 1);
        visits[remt][indx] = (a > b);
        return dp[remt][indx] = max(a, b);
    }
}

int main() {
    //freopen("input.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    bool line = false;
    while (scanf("%d %d", &t, &w) != EOF) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d %d", &cost[i], &val[i]);
            cost[i] = cost[i] * w * 3;
        }
        memset(dp, -1, sizeof(dp));
        memset(visits, false, sizeof(visits));
        memset(mark, false, sizeof(mark));
        if (line)
            printf("\n");
        line = true;
        cout << solve(t, 0) << endl;
        int j = t;
        int count = 0;
        for (int i = 0; i < n; i++) {
            if (visits[j][i]) {
                mark[i] = true;
                count++;
                j = j - cost[i];
            }
        }
        printf("%d\n", count);
        for (int i = 0; i < n; i++)
            if (mark[i])
                printf("%d %d\n", cost[i]/(3*w), val[i]);
    }
    return 0;
}
