#include <stdio.h>
typedef struct
{
    unsigned dist[20];
    unsigned from[20];
} node;
node rt[10];
int main()
{
    int costmat[20][20];
    int nodes, i, j, k, count = 0;
    printf("\nEnter the number of nodes : ");
    scanf("%d", &nodes);
    printf("\nEnter the cost matrix :\n");
    int x = 0;
    for (; x < nodes; x++)
        printf("\t%c", x + 97);
    printf("\n");
    for (x = 0; x < nodes; x++)
        printf("\t_");
    printf("\n");
    for (i = 0; i < nodes; i++)
    {
        printf("\n%c|\t", i + 97);
        for (j = 0; j < nodes; j++)
        {
            scanf("%d", &costmat[i][j]);
            costmat[i][i] = 0;
            rt[i].dist[j] = costmat[i][j];
            rt[i].from[j] = j;
        }
    }
    do
    {
        count = 0;
        for (i = 0; i < nodes; i++)
            for (j = 0; j < nodes; j++)
                for (k = 0; k < nodes; k++)
                    if (rt[i].dist[j] > costmat[i][k] + rt[k].dist[j])
                    {
                        rt[i].dist[j] = rt[i].dist[k] + rt[k].dist[j];
                        rt[i].from[j] = k;
                        count++;
                    }
    } while (count != 0);
    for (i = 0; i < nodes; i++)
    {
        printf("\n\n For router %c\n", i + 97);
        for (j = 0; j < nodes; j++)
        {
            printf("\t\nnode %c via %c Distance %d ", j + 97, rt[i].from[j] + 97, rt[i].dist[j]);
        }
    }
    printf("\n\n");
    return 0;
}