// GRAPH.h
#ifndef GRAPH_H
#define GRAPH_H

typedef struct No {
    int destino;
    int peso;
    int d;
    int f;
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

void dijkstra(Grafo *g, int origem, int destino); // Renato
void caminhoCritico(Grafo *g, int duracoes[]); // Renato
void grafoTransposto(Grafo *g, int destino, int origem, int peso);
void freeGrafo(Grafo* g);
void mostrarGrafo(Grafo* g);
No* criarNo(int destino, int peso);
Grafo* criarGrafo(int quantVertices);
Grafo* lerArquivo(char *nome, int dir);
Grafo* lerArquivoTransposto(char *nome);
void adicionarArestaOrdenado(Grafo *g, int origem, int destino, int peso); // Pedro
void adicionarArestaOrdenadoNDir(Grafo *g, int origem, int destino, int peso); // Pedro
void removeVertice(Grafo *g, int alvo);
void BFS(Grafo *g, int origem);
void DFS(Grafo *g, int v, int visitado[], Pilha* p);
void DFSvisita(Grafo* g, int u, int visitado[], Pilha* p);
void Kosaraju(Grafo* g, Grafo* gT);
void topoDFS(Grafo *g, int v, int visitado[], int pilha[], int *topo);
Pilha* criaPilha(void);
void addPilha(Pilha *pi, No *novo);
void removePilha(Pilha *pi);
int achaPilha(Pilha *pi, No *sugeito);
No* extractMin(Pilha *pi);
Grafo *Prim(Grafo *g, int r);

#endif // GRAPH_H
