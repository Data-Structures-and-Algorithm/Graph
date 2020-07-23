#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <assert.h>

#define IS_WEIGHTED false
#define IS_DIRECTED false
#define DISPLAY_WEIGHT false
typedef struct node {
	int value;
	int weight;
	struct node *next;
} Node_t;

typedef struct {
	Node_t *head;
} List_t;

typedef struct {
	List_t *list;
	int vertex_count;
	int edge_count;
} Graph_t;

Graph_t *create_graph(void);
Node_t *create_node(int value, int weight);
void add_edge(Graph_t *graph, int u, int v, int weight);
void display_graph(Graph_t *graph);
void delete_graph(Graph_t *graph);

int main()
{    
	Graph_t *graph = NULL;

	graph = create_graph();
	
	// test connections for a vertex count of 8
	add_edge(graph, 6, 4, 0);
	add_edge(graph, 6, 0, 0);
	add_edge(graph, 4, 1, 0);
	add_edge(graph, 0, 1, 0);
	add_edge(graph, 0, 3, 0);
	add_edge(graph, 1, 5, 0);
	add_edge(graph, 3, 5, 0);
	add_edge(graph, 5, 2, 0);
	add_edge(graph, 7, 2, 0);

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
	
	graph->list = malloc(graph->vertex_count * sizeof(List_t));

	if (!graph->list) {
		perror("Memory allocation failed for list:\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < graph->vertex_count; i++) {
		graph->list[i].head = NULL;
	}

	graph->edge_count = 0;

	return graph;
}



Node_t *create_node(int value, int weight)
{
	Node_t *new_node = malloc(1 * sizeof(Node_t));
	new_node->value = value;
	new_node->weight = weight;
	new_node->next = NULL;
	return new_node;
}


void add_edge(Graph_t *graph, int s, int d, int weight)
{
	assert((s >= 0) && \
		   (d >= 0) && \
	       (s < graph->vertex_count) && \
		   (d < graph->vertex_count));
	
	Node_t *dest = create_node(d, weight);	
	dest->next = graph->list[s].head;
	graph->list[s].head = dest;
    
	// for undirected graph, if there is an edge from u to v, then
	// there must be an edge  from v to u
	if (!IS_DIRECTED) {
		dest = create_node(s, weight);
		dest->next = graph->list[d].head;
		graph->list[d].head = dest;
		
	}

}

void display_graph(Graph_t *graph)
{
	if (!graph) {
		printf("NULL Graph\n");
		return;
	}
	
	printf("\n");
	
	for (int i = 0; i < graph->vertex_count; i++) {
		Node_t *temp = graph->list[i].head;
		printf("%d --> ", i);
		while (temp) {
			printf("%d", temp->value);
#if IS_WEIGHTED && DISPLAY_WEIGHT
			printf("(%d)", temp->weight);
#endif
			temp = temp->next;
			if (temp) {
				printf("--> ");
			}
		}	
		printf("\n");
	}
}

void delete_graph(Graph_t *graph)
{
    for (int i = 0; i < graph->vertex_count; i++) {
		Node_t *temp = graph->list[i].head;
		while (temp) {
			Node_t *next_node = temp->next;
			free(temp);
			temp = next_node;
		}	
	}
	free(graph->list);
	free(graph);
}
