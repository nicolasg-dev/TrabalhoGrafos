#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

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
