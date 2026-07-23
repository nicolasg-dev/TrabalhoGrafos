#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "graph.h"

Grafo* criarGrafo(int vertices)
{
    Grafo* grafo = (Grafo*) malloc(sizeof(Grafo));

    for (int i = 0; i < vertices; i ++) // itera na lista de grafos, alocando cada vértice necessário
    {
        grafo->lista[i] = malloc (sizeof(No));
        grafo->lista[i]->prox = NULL; //Claude sugeriu
    }
    grafo->V = vertices;
    return grafo;
}

/*
Grafo* leGrafo(char str[]) // key = 1 -> direcionado; 0 -> n direcionado
{
    FILE* arquivo = fopen(str, "r");
    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo!\n");
        return NULL;
    }

    char linha[256];
    int l = 1;
    int Vnum, Anum, a, b, c;

    Grafo* grafo = (Grafo*) malloc(sizeof(Grafo));


    fscanf (arquivo, "%d %d",&Vnum, &Anum); // deu certo
    grafo->V = Vnum;
    grafo->A = Anum;
    grafo->lista = (No**) malloc (grafo->V * sizeof(No*));


    for (int i = 0; i < grafo->V; i ++)
    {
        grafo->lista[i] = malloc (sizeof(No));
    }

    while(fscanf(arquivo, "%d %d %d", &a, &b, &c) == 3)
    {
        printf("%d %d %d\n", a, b, c);
        adicionarAresta(grafo, a, b, c);
    }

    /*while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        printf("%s", linha);
        l++;
    }#1#

    for (int i = 0; i < grafo->V; i ++)
    {
        No * aux = grafo->lista[i];
        printf("%d" , i+1);
        while (aux != NULL)
        {
            aux = aux->prox;
            printf("V%d (%d)", i, aux->peso);

        }
        printf("\n");
    }

}
*/

Grafo *lerArquivo(char *nome){
    FILE *arquivo = fopen(nome, "r");
    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo!\n");
        exit(100);
    }
    int Vertices, Arestas, Origem, Destino, Peso;
    fscanf(arquivo,"%d %d", &Vertices, &Arestas); //le os primeiros dois inteiros do arquivo para saber a quantidade de vertices e arestas
    Grafo *g = criarGrafo(Vertices);
    while(fscanf(arquivo, "%d %d %d", &Origem, &Destino, &Peso) == 3){ //coleta os dados subsequentes de 3 em tres para adicionar as arestas
        adicionarAresta(g, Origem, Destino, Peso); // fiz esse while de == 3 pois o retorno do fscanf é a quantidade de dados que ele le e enquanto ele ler
    } // 3 arquivos o programa da certo
    fclose(arquivo);
    if(g->A == Arestas){
        return g; // faço o teste para verificar se a quantidade de arestas informadas no arquivo esta de acordo com a quantidade de arquivos do grafo e se nao for
    } // o caso deu algum erro na leitura
    printf("Erro na leitura dos dados!\n");


    for (int i = 0; i < g->V; i ++)
    {
        No * aux = g->lista[i];
        printf("%d" , i+1);
        while (aux != NULL)
        {
            aux = aux->prox;
            printf("V%d (%d)", i, aux->peso);

        }
        printf("\n");
    }
}

void adicionarArestaOrdenado(Grafo *g, int origem, int destino, int peso) {
    No *novo = (No*) malloc(sizeof(No));
    novo->destino = destino;
    novo->peso = peso;
    No* aux = g->lista[origem];
    No* ant = g->lista[origem];
    while (aux->destino < destino && aux->prox != NULL)
    {
        ant = aux;
        aux = aux->prox;
    }
    novo->prox = aux;
    ant->prox = novo;
}

void adicionarAresta(Grafo *g, int origem, int destino, int peso) {
    No *novo = (No*) malloc(sizeof(No));
    novo->destino = destino;
    novo->peso = peso;
    novo->prox = g->lista[origem];
    g->lista[origem] = novo;
}

void removeVertice(Grafo *g, int alvo)
{
    No* aux = NULL;
    No* ant = NULL;
    for (int i = 0; i < g->V; i++)
    {
        aux = g->lista[i];
        while (aux != NULL)
        {
            if (aux->destino == alvo)
            {
                ant = aux->prox;
                free(aux);
                break;
            }
            ant = aux;
            aux = aux->prox;
        }
    }

    free(g->lista[alvo]);
}

void DFS(Grafo *g, int v, int visitado[])
{
    visitado[v] = 1;
    printf("%d\n", v);
    No* aux = g->lista[v];

    while (aux != NULL)
    {
        if (!visitado[aux->destino]) // se a cor for branco
        {
            DFS(g, aux->destino, visitado);
        }
        aux = aux->prox;
    }
}

void BFS(Grafo *g, int origem) {
    int fila[100];
    int inicio = 0;
    int fim = 0;
    int visitado[100] = {0};
    fila[fim++] = origem;
    visitado[origem] = 1;
    while (inicio < fim) {
        int v = fila[inicio++];
        printf("%d ", v);
        No *aux = g->lista[v];
        while (aux) {
            if (!visitado[ aux->destino ]) {
                visitado[ aux->destino ] = 1;
                fila[fim++] = aux->destino;
            }
            aux = aux->prox;
        }
    }
}

void topoDFS(Grafo *g, int v, int visitado[], int pilha[], int *topo) {
    visitado[v] = 1;
    No *aux = g->lista[v];

    while (aux) {
        if (!visitado[aux->destino]) {
            topoDFS(g, aux->destino, visitado, pilha, topo);
        }
        aux = aux->prox;
    }

    pilha[(*topo)++] = v;
}

Pilha* criaPilha ()
{
    Pilha* pi = malloc(sizeof(Pilha));
    if (pi != NULL) pi->topo = NULL;
    return pi;

}

void addPilha(Pilha* pi, No* novo)
{
    if (pi->topo == NULL)
    {
        pi->topo = novo;
    } else
    {
        novo->prox = pi->topo;
        pi->topo = novo;
    }
}

void removePilha (Pilha* pi)
{
    No* aux = pi->topo;

    if (pi->topo == NULL)
    {
        return;
    } else
    {
        pi->topo = pi->topo->prox;
        free(aux);
    }
}

int achaPilha(Pilha* pi, No* sugeito)
{
    No* aux;

    if (pi->topo == NULL) return -1;
    {
        aux = pi->topo;
        while (aux != NULL)
        {
            if (aux == sugeito)
            {
                return 1;
            }
            aux = aux->prox;
        }
    }
    return 0;
}

No* extractMin (Pilha* pi)
{
    No* aux;
    No* menor = NULL;
    if (pi->topo == NULL) return NULL;
    {
        aux = pi->topo;
        while (aux != NULL)
        {
            if (aux->chave < aux->prox->chave)
            {
                menor = aux;
            }
            aux = aux->prox;
        }
    }
    return menor;
}

Grafo* Prim(Grafo* g, int r)
{
    No* raiz = g->lista[r];
    No* v = NULL;
    No* u = NULL;

    for (int i = 0; i < g->V; i++)
    {
        g->lista[i]->chave = 10000;
        g->lista[i]->pai = NULL;
    }

    Pilha* p = criaPilha();
    raiz->chave = 0;

    for (int i = 0; i < g->V; i++)
    {
        addPilha(p, g->lista[i]);
    }

    while (p->topo != NULL)
    {
        u = extractMin(p); // u <- menor vértice da pilha
        v = u;
        do
        {
            v = v->prox;
            if (achaPilha(p, v) == 1 && v->peso < v->chave)
            {
                v->pai = u;
                v->chave = v->peso;
            }
        } while (v != NULL);
    }
}
