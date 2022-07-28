/*
    Distance Vector Routing in this program is implemented using Bellman Ford Algorithm:-
*/

#include<stdio.h>

struct node{
    unsigned dist[20];
    unsigned from[20];
}rt[10];

int main(int argc, char *argv[]){

    int costmat[20][20];
    int nodes, i, j, k, count = 0;
    printf("Enter the number of nodes : ");
    scanf("%d", &nodes);
    printf("Enter the cost matrix :\n");

    for(i = 0; i < nodes; i++){
        for(j = 0; j < nodes; j++){
            printf("Enter edge between node %d and %d: ", i , j);
            scanf("%d",&costmat[i][j]);
            costmat[i][i] = 0;
            rt[i].dist[j] = costmat[i][j];
            //initialise the distance equal to cost matrix
            rt[i].from[j] = j;
        }
    }

    do
    {
       /*
        * We choose arbitary vertex k and we calculate
        * the direct distance from the node i to k using
        * the cost matrix and add the distance from k to node j
        */
        count = 0;
        for(i = 0; i < nodes; i++){
            for(j = 0; j < nodes; j++){
                for(k = 0; k < nodes; k++){
                    if(rt[i].dist[j] > rt[i].dist[k] + rt[k].dist[j]){
                        //We calculate the minimum distance
                        rt[i].dist[j] = rt[i].dist[k] + rt[k].dist[j];
                        rt[i].from[j] = k;
                        count++;
                    }
                }
            }
        }
    }while(count != 0);

    for(i = 0; i < nodes; i++){
        printf("For router %d\n",i+1);
        for(j = 0; j < nodes; j++){
            printf("\tnode %d via %d Distance %d\n", j+1, rt[i].from[j]+1, rt[i].dist[j]);
        }
    }
    printf("\n\n");
    return 1;
}
