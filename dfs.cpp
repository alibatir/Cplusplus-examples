#include <stdio.h>

int adj[301][301]; //the adjajency matrix that represents the graph
bool visit[301]; //is this vertex visited?
int n,m;

void dfs(int x) {
    visit[x] = true;

    for (int i = 1; i <= n; i++)
        if (adj[x][i] == 1 && visit[i] == false)
            dfs(i);
}

main()
{
    FILE *in = fopen("input.txt","r");

    fscanf(in,"%d%d",&n,&m);

    for (int i = 1; i<=m; i++) {
        int j,k;

        fscanf(in,"%d%d",&j,&k);

        adj[j][k]=1;
        adj[k][j]=1;
    }


    int cnt = 0;


    for (int i = 1; i <= n; i++) {
        if (!visit[i]) {
            cnt++;
            dfs(i);
        }
    }
    printf("count is %d\n",cnt);




}

