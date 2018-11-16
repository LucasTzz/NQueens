//
//  main.cpp
//  Queen
//
//  Created by 陶子卓 on 2018/11/12.
//  Copyright © 2018 tzz. All rights reserved.
//

#include <iostream>
#include <thread>
#include <mutex>
#include <sys/time.h>
using namespace std;
static int row = 1, init_column = 1, column, result_count = 0;
const int N=10;
static int Queens[N+1],conflict[N+1][N+1];
void Queen_place();
mutex mu;
int main() {
    int tid=1;
    struct timeval start;
    struct timeval end;
    unsigned long timer;
    thread Queen_thread[N+1];
    gettimeofday(&start, NULL);
    while (row>=1) {
        Queen_thread[tid]=thread{Queen_place};
        Queen_thread[tid].join();
        ++tid;
        if(tid>N) tid=1;
    }
    gettimeofday(&end, NULL);
    timer= 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
    cout << "Total: " << result_count << " results."<<'\t'<<"Time cost: "<<timer/1000<<"ms"<<endl;
    return 0;
}

void Queen_place()
{
    for (column = init_column; column <= N&&conflict[row][column]; ++column);
    if (column <= N) {
        mu.lock();
        Queens[row] = column;
        for (int i = row + 1; i <= N; ++i)
        {
            ++conflict[i][column];
        }
        for (int i = row + 1, j = column - 1; i <= N&&j >= 1; ++i, --j)
        {
            ++conflict[i][j];
        }
        for (int i = row + 1, j = column + 1; i <= N&&j <= N; ++i, ++j)
        {
            ++conflict[i][j];
        }
        ++row;
        if (row <= N)
        {
            init_column = 1;
            mu.unlock();
            return;
        }
        else
        {
            ++result_count;
            for (int i = 1; i <= N; ++i) cout << Queens[i] << " ";
            cout << endl;
            row = N;
            init_column = Queens[N] + 1;
            mu.unlock();
            return;
        }
    }
    else {
        mu.lock();
        --row;
        if (row >= 1)
        {
            int current_column = Queens[row];
            for (int i = row + 1; i <= N; ++i)
            {
                --conflict[i][current_column];
            }
            for (int i = row + 1, j = current_column - 1; i <= N&&j >= 1; ++i, --j)
            {
                --conflict[i][j];
            }
            for (int i = row + 1, j = current_column + 1; i <= N&&j <= N; ++i, ++j)
            {
                --conflict[i][j];
            }
            init_column = current_column+1;
        }
        mu.unlock();
        return;
    }
}
