#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <assert.h>

#define IS_WEIGHTED false
#define IS_DIRECTED false

typedef struct {
	int **matrix;
	int vertex_count;
	int edge_count;
} Graph_t;

Graph_t *create_graph(void);
void add_edge(Graph_t *graph, int u, int v, int weight);
void display_graph(Graph_t *graph);
int main()
{    
	Graph_t *graph = NULL;

	graph = create_graph();
	add_edge(graph, 0, 0, 5);
	add_edge(graph, 2, 0, 4);
	add_edge(graph, 1, 0, 0);

	display_graph(graph);
	return 0;
}

Graph_t *create_graph(void)
{
	Graph_t *graph = NULL;

	graph = malloc(1 * sizeof(Graph_t));

	if (!graph) {
		perror("Memory allocation failed for graph:\n");
		exit(EXIT_FAILURE);
	}

	printf("Enter no.of vertices: ");
	scanf("%d", &graph->vertex_count);
	
	graph->matrix = malloc(graph->vertex_count * sizeof (int *));

	if (!graph->matrix) {
		perror("Memory allocation failed for matrix:\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < graph->vertex_count; i++) {
		graph->matrix[i] = malloc(graph->vertex_count * sizeof (int));
		if (!graph->matrix[i]) {
			perror("Memory allocation failed for row:\n");
			exit(EXIT_FAILURE);
		}
	}

	for (int u = 0; u < graph->vertex_count; u++) {
		for (int v = 0; v < graph->vertex_count; v++) {
			graph->matrix[u][v] = IS_WEIGHTED ? INT_MAX : 0;
		}
	}

	graph->edge_count = 0;

	return graph;

}

void add_edge(Graph_t *graph, int u, int v, int weight)
{
	assert((u >= 0) && (u < graph->vertex_count));
	
	/* Increment edge_count only if the link exists */
    if (IS_WEIGHTED) {
		if (graph->matrix[u][v] == INT_MAX) {
			graph->edge_count++;
		} 
		graph->matrix[u][v] = weight;
		if (!IS_DIRECTED) {
			graph->matrix[v][u] = weight;
		}
	} else {
		if (graph->matrix[u][v] == 0) {
			graph->edge_count++;
		} 
		graph->matrix[u][v] = 1;
		if (!IS_DIRECTED) {
			graph->matrix[v][u] = 1;
		}
	}	
}

void display_graph(Graph_t *graph)
{
	if (!graph) {
		printf("NULL Graph\n");
		return;
	}
	
	printf("\n");
	
	for (int u = 0; u < graph->vertex_count; u++) {
		for (int v = 0; v < graph->vertex_count; v++) {
			printf("%10d\t", graph->matrix[u][v]);
		}
		printf("\n");
	}
}

