// GRAPH.h
#ifndef GRAPH_H
#define GRAPH_H

typedef struct No {
    int destino;
    int peso;
    int chave;
    struct No* pai;
    struct No *prox;
} No;

typedef struct {
    int V;      // Número de vértices
    int A;      // Número de arestas
    No **lista; // Lista de adjacência
} Grafo;

typedef struct pilha
{
    No* topo;
}Pilha;

void adicionarAresta(Grafo *g, int origem, int destino, int peso);
void removeVertice(Grafo *g, int alvo);
void BFS(Grafo *g, int origem);
void DFS(Grafo *g, int v, int visitado[]);
void topoDFS(Grafo *g, int v, int visitado[], int pilha[], int *topo);
void addPilha(Pilha *pi, No *novo);
void removePilha(Pilha *pi);
Grafo *Prim(Grafo *g, int r);

#endif // GRAPH_H
