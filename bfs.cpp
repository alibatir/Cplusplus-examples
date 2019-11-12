#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;

vector<int> L[301]; //the adjacency list that represents the graph
queue<int> Q; //the queue to be used in BFS algorithm
int n,m;

int shortest[301]; //shortest[x] = the shortest distance from 1 to x
bool visit[301]; //is the vertex visited/processed?

main() {

    FILE *in = fopen("input.txt","r");

    fscanf(in,"%d%d",&n,&m);

    for (int i = 1; i <= m; i++)
    {
        int j,k;

        fscanf(in,"%d%d",&j,&k);

        L[j].push_back(k);
        L[k].push_back(j);
    }


    Q.push(1);
    shortest[1] = 0;
    visit[1] = true;

    while (!Q.empty()) {
        int x = Q.front();
        Q.pop();

        for (int i = 0; i < L[x].size(); i++) {
            int y = L[x][i];
            if (!visit[y]) {
                shortest[y] = shortest[x] + 1;
                visit[y] = true;
                Q.push(y);
            }
        }
    }

    for (int i = 1; i <= n; i++)
        printf("%d: %d\n",i,shortest[i]);




}
