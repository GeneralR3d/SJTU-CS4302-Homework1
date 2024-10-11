#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<limits.h>
#define SIZE 5
#define min(a,b) (((a)<(b))?(a):(b))

int thread_count;
void floydWarshall(int graph[SIZE][SIZE]);

int main(int argc, char* argv[]){

    
    thread_count = strtol(argv[1],NULL,10);

    // Sample 5x5 graph
    int graph[SIZE][SIZE] = {
        {0, 3, 10e7, 10e7, 7},
        {8, 0, 2, 10e7, 10e7},
        {5, 10e7, 0, 1, 10e7},
        {2, 10e7, 10e7, 0, 6},
        {10e7, 1, 4, 10e7, 0}
    };
    
    floydWarshall(graph);

    return 0;
}

void floydWarshall(int graph[SIZE][SIZE]) {
    int dist[SIZE][SIZE];

    // Initialize the distance array
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            dist[i][j] = graph[i][j];
        }
    }

    // Floyd-Warshall algorithm
    for (int k = 0; k < SIZE; k++) {
        #pragma omp parallel for num_threads(thread_count)
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                dist[i][j] = min(dist[i][j],dist[i][k]+ dist[k][j]);
            }
        }
    }

    // Print the resulting distance matrix
    printf("Distance matrix:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (dist[i][j] == 10e7)
                printf("INF ");
            else
                printf("%d ", dist[i][j]);
        }
        printf("\n");
    }
}