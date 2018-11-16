//
//  Recall.cpp
//  NQueensByRecall
//
//  Created by 陶子卓 on 2018/11/17.
//  Copyright © 2018 tzz. All rights reserved.
//

#include <iostream>
#include <sys/time.h>
using namespace std;

int main() {
    struct timeval start;
    struct timeval end;
    unsigned long timer;
    int N, s = 1, t = 1, k, count = 0;
    cout << "please enter the number of queens: ";
    cin >> N;
    int *Q = new int[N + 1];
    for (int i = 0; i<N + 1; ++i) {
        Q[i] = 0;
    }
    int **conflict = new int*[N + 1];
    for (int i = 0; i<N + 1; ++i) {
        conflict[i] = new int[N + 1];
    }
    for (int i = 0; i<N + 1; ++i) {
        for (int j = 0; j<N + 1; ++j) {
            conflict[i][j] = 0;
        }
    }
    gettimeofday(&start, NULL);
    while (Q[1] <= N) {
        for (k = t; k <= N&&conflict[s][k]; ++k);
        if (k <= N) {
            Q[s] = k;
            for (int i = s + 1; i <= N; ++i)
            {
                ++conflict[i][k];
            }
            for (int i = s + 1, j = k - 1; i <= N&&j >= 1; ++i, --j)
            {
                ++conflict[i][j];
            }
            for (int i = s + 1, j = k + 1; i <= N&&j <= N; ++i, ++j)
            {
                ++conflict[i][j];
            }
            ++s;
            if (s <= N)
            {
                t = 1;
                continue;
            }
            else
            {
                ++count;
                for (int i = 1; i <= N; ++i) cout << Q[i] << " ";
                cout << endl;
                s = N;
                t = Q[N] + 1;
                continue;
            }
        }
        else {
            --s;
            if (s < 1)
            {
                break;
                
            }
            int p = Q[s];
            for (int i = s + 1; i <= N; ++i)
            {
                --conflict[i][p];
            }
            for (int i = s + 1, j = p - 1; i <= N&&j >= 1; ++i, --j)
            {
                --conflict[i][j];
            }
            for (int i = s + 1, j = p + 1; i <= N&&j <= N; ++i, ++j)
            {
                --conflict[i][j];
            }
            t = p+1;
            continue;
        }
    }
    gettimeofday(&end, NULL);
    timer=1000000*(end.tv_sec-start.tv_sec)+end.tv_usec-start.tv_usec;
    cout << "Total: " << count << " results"<<'\t'<<"Time cost: "<<timer/1000<<"ms"<<endl;
    return 0;
}
