#include "list.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int sudo[9][9];
} Node;

Node *createNode() {
  Node *n = (Node *)malloc(sizeof(Node));
  return n;
}

Node *copy(Node *n) {
  Node *new = (Node *)malloc(sizeof(Node));
  *new = *n;
  return new;
}

Node *read_file(char *file_name) {
  Node *n = createNode();
  FILE *file = fopen(file_name, "r");
  int i, j;
  for (i = 0; i < 9; i++) {
    for (j = 0; j < 9; j++) {
      if (!fscanf(file, "%d", &n->sudo[i][j]))
        printf("failed to read data!");
    }
  }

  fclose(file);
  return n;
}

void print_node(Node *n) {
  int i, j;
  for (i = 0; i < 9; i++) {
    for (j = 0; j < 9; j++)
      printf("%d ", n->sudo[i][j]);
    printf("\n");
  }
  printf("\n");
}

int is_valid(Node *n) {

  // Verificacion por filas
  for (int i = 0; i < 9; i++) {
    int fila[10] = {0};
    for (int j = 0; j < 9; j++) {
      if (n->sudo[i][j] != 0) {
        if (fila[n->sudo[i][j]] == 1)
          return 0;
        fila[n->sudo[i][j]] = 1;
      }
    }
  }

  // Verificacion por columnas
  for (int i = 0; i < 9; i++) {
    int col[10] = {0};
    for (int j = 0; j < 9; j++) {
      if (n->sudo[j][i] != 0) {
        if (col[n->sudo[j][i]] == 1)
          return 0;
        col[n->sudo[j][i]] = 1;
      }
    }
  }

  // Verificacion por submatriz
  for (int i = 0; i < 9; i += 3) {
    for (int j = 0; j < 9; j += 3) {
      int test[10] = {0};
      for (int k = i; k < i + 3; k++) {
        for (int l = j; l < j + 3; l++) {
          if (n->sudo[k][l] != 0) {
            if (test[n->sudo[k][l]] == 1)
              return 0;
            test[n->sudo[k][l]] = 1;
          }
        }
      }
    }
  }
  return 1;
}

List *get_adj_nodes(Node *n) {
  List *list = createList();

  for (int k = 0; k <= 8; k++) {
    for (int i = 0; i <= 8; i++) {
      if (n->sudo[k][i] == 0) {
        for (int j = 1; j <= 9; j++) {
          Node *nodo = copy(n);
          nodo->sudo[k][i] = j;
          if (is_valid(nodo)) {
            pushBack(list, nodo);
          } else {
            free(nodo);
          }
        }
        return list;
      }
    }
  }

  return list;
}

int is_final(Node *n) {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (n->sudo[i][j] == 0)
        return 0;
    }
  }
  return 1;
}

Node *DFS(Node *initial, int *cont) {
  Stack *pila = createStack();
  push(pila, initial);
  Node *nodo = createNode();

  while (!is_empty(pila)) {
    nodo = top(pila);
    pop(pila);

    (*cont)++;

    if (is_final(nodo)) {
      return nodo;
    } else {
      List *lista = get_adj_nodes(nodo);
      while (!is_empty(lista)) {
        Node *aux = first(lista);
        push(pila, aux);
        popFront(lista);
      }
      free(nodo);
    }
  }

  return NULL;
}

/*
int main(int argc, char *argv[]) {

  Node *initial = read_file("s12a.txt");
  ;

  int cont = 0;
  Node *final = DFS(initial, &cont);
  printf("iterations:%d\n", cont);
  print_node(final);

  return 0;
}*/