// Adapted from Rosetta Code
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// forward declaration
struct node;

struct edge {
  struct node* target; // the target of this edge
  double cost; // edge cost
  struct edge* sibling; // internal linked list of edges leading out from the same node
};

struct node {
  struct edge* edge; // singly linked list of edges
  struct node* via; // previous node in shortest path
  double cost; // distance from origin node
  int name; // "name" (which is actually a number)
  int heap_index; // heap position for updating distance
};

void add_edge(struct node* a, struct node* b, double cost) {
  struct edge* answer = malloc(sizeof(struct edge));
  answer->target = b;
  answer->cost = cost;
  answer->sibling = a->edge;
  a->edge = answer;
}

void calc_all(struct node* start, int num_nodes) {
  struct node** heap = calloc(sizeof(struct node*), num_nodes + 1);
  start->heap_index = 1;
  start->via = start;
  start->cost = 0;
  heap[1] = start;
  int heap_len = 1;
  while (heap_len) {
    struct node* lead = heap[1];
    struct node* temp = heap[heap_len--];
    int i, j;
    for (i = 1; i < heap_len && (j = i * 2) <= heap_len; i = j) {
      if (j < heap_len && heap[j]->cost > heap[j+1]->cost) {
        j++;
      }
      if (heap[j]->cost >= temp->cost) {
        break;
      }
      (heap[i] = heap[j])->heap_index = i;
    }
    heap[i] = temp;
    temp->heap_index = i;
    for (struct edge* e = lead->edge; e; e = e->sibling) {
      if (e->target->via && e->target->cost < lead->cost + e->cost) {
        continue;
      }
      e->target->cost = lead->cost + e->cost;
      e->target->via = lead;
      int i = e->target->heap_index;
      if (!i) {
        i = ++heap_len;
      }
      for (; i > 1 && e->target->cost < heap[j = i/2]->cost; i = j) {
        (heap[i] = heap[j])->heap_index = i;
      }
      heap[i] = e->target;
      e->target->heap_index = i;
    }
  }
}

void show_path(struct node* n) {
  if (n->via == n) {
    printf("%c", 'a' + n->name);
  } else if (!n->via) {
    printf("unreached");
  } else {
    show_path(n->via);
    printf("-> %c ", 'a' + n->name);
  }
}


int main(int argc, char* argv) {
  int num_nodes;
  assert(scanf("%d", &num_nodes) == 1);
  struct node* nodes = calloc(sizeof(struct node), num_nodes);
  for (int i = 0; i < num_nodes; i += 1) {
    nodes[i].name = i;
  }
  int num_edges;
  assert(scanf("%d", &num_edges) == 1);
  for (int i = 0; i < num_edges; i += 1) {
    int source, target, cost;
    assert(scanf("%d %d %d", &source, &target, &cost) == 3);
    add_edge(nodes + source, nodes + target, cost);
  }
  calc_all(nodes, num_nodes);
  for (int i = 0; i < num_nodes; i += 1) {
    printf("path to %c (cost %f) ", 'a' + nodes[i].name, nodes[i].cost);
    show_path(nodes + i);
    putchar('\n');
  }

  return 0;
}

  


