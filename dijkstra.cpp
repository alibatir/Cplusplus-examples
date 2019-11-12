#include <stdio.h>

int adj[301][301]; //the adjajency matrix that represents the graph
bool visit[301]; //is this vertex visited/processed?
int shortest[301]; //shortest[x] = the shortest distance from 1 to x

int n,m;

main() {

    FILE *in = fopen("input2.txt","r");

    fscanf(in,"%d%d",&n,&m);

    for (int i = 1; i <= m; i++) {
        int j,k,l;
        fscanf(in,"%d%d%d",&j,&k,&l);
        adj[j][k] = l;
        adj[k][j] = l;


    }

    int x = 1;
    shortest[1] = 0;

    for (int i = 2; i <= n; i++)
        shortest[i] = 1000000000;

    while (x != -1) {
        visit[x] = true;

        for (int i = 1; i <= n; i++) {
            if (adj[x][i] != 0 && !visit[i] && shortest[i] > shortest[x] + adj[x][i])
                shortest[i] = shortest[x] + adj[x][i];
        }

        x = -1;
        int Min = 1000000000;

        for (int i = 1; i <= n; i++)
        {
            if (!visit[i] && shortest[i] < Min) {
                x = i;
                Min = shortest[i];
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        printf("%d: %d\n",i,shortest[i]);
    }
}
