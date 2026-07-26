#ifndef GRAPH_H
#define GRAPH_H

typedef struct No {
    int destino;
    int peso;
    int chave;
    struct No *pai;
    struct No *prox;
} No;

typedef struct grafo {
    int V;
    int A;
    No **lista;
} Grafo;

typedef struct num
{
    int valor;
    struct num* prox;
} Num;

typedef struct pilha {
    Num *topo;
} Pilha;

// 1. Leitura e Construção do Grafo (e extras)
Grafo* criarGrafo(int quantVertices);
Grafo* lerArquivo(char *nome, int dir);
No* criarNo(int destino, int peso);
void adicionarArestaOrdenado(Grafo *g, int origem, int destino, int peso);
void adicionarArestaOrdenadoNDir(Grafo *g, int origem, int destino, int peso);
void freeGrafo(Grafo* g);
void mostrarGrafo(Grafo* g);
void removeVertice(Grafo *g, int alvo);

// 2. Busca em Profundidade (DFS)
void DFS(Grafo *gr, char *tipoDFS, int ini);

// 3. Busca em Largura (BFS)
void BFS(Grafo *gr, int ini, int *visitado, int *distancia);

// 4. Ordenação Topológica
// (não implementado)

// 5. Árvore Geradora Mínima - Prim
void prim(Grafo *gr, int orig, int *pai);

// 6. Menor Caminho - Dijkstra
// (Implementado por Renato)
void dijkstra(Grafo *g, int origem, int destino);

// 7. Desafios Extras
// 7. 1. Deteccao de Ciclos
// (Implementado por Angelo)

// 7. 2. Componentes Fortemente Conexos
// (Implementado por Nicolas)
void Kosaraju(Grafo *g);
void DFSKosaraju(Grafo *gr, int ini, int *visitados);
void DFSWithVertexPriorities(Grafo *gr, int ini, int *visitado, Pilha* p);
void dfsRecursivaKosaraju(Grafo *gr, int ini, int *visitado);

// 7. 3. Caminho Crítico
// (Implementado por Renato)
void caminhoCritico(Grafo *g, int duracoes[]);

// 7. 4. Grafo com 1000+ vértices
// (Implementado por Pedro Lucas)

// 8. Funcoes Pilha
Pilha* criaPilha(void);
int popPilha(Pilha* pi);
Num* extractMin(Pilha *pi);
void addPilha(Pilha *pi, int n);
void freePilha(Pilha *pi);
int achaPilha(Pilha *pi, Num *sugeito);
void printPilha (Pilha* pi);

#endif // GRAPH_H
