//
// Created by nicolas on 7/25/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include "graph.h"

int tempo = 0;

static void imprimirCaminhoAux(int pai[], int v) {
    if (v == -1) return;
    imprimirCaminhoAux(pai, pai[v]);
    printf("%d ", v);
}

void dijkstra(Grafo *g, int origem, int destino) {
    if (g == NULL || origem < 0 || origem >= g->V || destino < 0 || destino >= g->V) {
        printf("Origem ou destino invalido!\n");
        return;
    }

    int dist[g->V];
    int visitado[g->V];
    int pai[g->V];

    for (int i = 0; i < g->V; i++) {
        dist[i] = INT_MAX;
        visitado[i] = 0;
        pai[i] = -1;
    }

    dist[origem] = 0;

    for (int count = 0; count < g->V - 1; count++) {
        int min = INT_MAX, u = -1;
        for (int v = 0; v < g->V; v++) {
            if (!visitado[v] && dist[v] <= min) {
                min = dist[v];
                u = v;
            }
        }

        if (u == -1 || u == destino) break;

        visitado[u] = 1;

        No *aux = g->lista[u];
        while (aux != NULL) {
            int v = aux->destino;
            int peso = aux->peso;

            if (!visitado[v] && dist[u] != INT_MAX && dist[u] + peso < dist[v]) {
                dist[v] = dist[u] + peso;
                pai[v] = u;
            }
            aux = aux->prox;
        }
    }

    // Resultados
    if (dist[destino] == INT_MAX) {
        printf("\nNao existe caminho entre V%d e V%d.\n", origem, destino);
    } else {
        printf("\nDIJKSTRA (V%d -> V%d)\n", origem, destino);
        printf("Menor Distancia: %d\n", dist[destino]);
        printf("Caminho percorrido: ");
        imprimirCaminhoAux(pai, destino);
        printf("\n\n");
    }
}

typedef struct {
    int duracao;
    int IC, TC; // Início/Término Mais Cedo
    int IT, TT; // Início/Término Mais Tarde
    int folga;
} TarefaCPM;

void caminhoCritico(Grafo *g, int duracoes[]) {
    if (g == NULL) return;

    int n = g->V;
    TarefaCPM t[n];

    // Inicialização
    for (int i = 0; i < n; i++) {
        t[i].duracao = duracoes[i];
        t[i].IC = 0;
        t[i].TC = 0;
    }

    // 1. FORWARD PASS (Cálculo de IC e TC)
    for (int u = 0; u < n; u++) {
        t[u].TC = t[u].IC + t[u].duracao;

        No *aux = g->lista[u];
        while (aux != NULL) {
            int v = aux->destino;
            if (t[u].TC > t[v].IC) {
                t[v].IC = t[u].TC;
            }
            aux = aux->prox;
        }
    }


    int duracaoTotal = 0;
    for (int i = 0; i < n; i++) {
        if (t[i].TC > duracaoTotal) {
            duracaoTotal = t[i].TC;
        }
    }

    // 2. BACKWARD PASS (Cálculo de TT, IT e Folga)
    for (int i = 0; i < n; i++) {
        t[i].TT = duracaoTotal;
    }

    Grafo *reverso = criarGrafo(n);
    for (int u = 0; u < n; u++) {
        No *aux = g->lista[u];
        while (aux != NULL) {
            adicionarArestaOrdenado(reverso, aux->destino, u, aux->peso); // Inverte u -> v para v -> u
            aux = aux->prox;
        }
    }

    for (int u = n - 1; u >= 0; u--) {
        t[u].IT = t[u].TT - t[u].duracao;
        t[u].folga = t[u].IT - t[u].IC;

        No *aux = reverso->lista[u];
        while (aux != NULL) {
            int antecessor = aux->destino;
            if (t[u].IT < t[antecessor].TT) {
                t[antecessor].TT = t[u].IT;
            }
            aux = aux->prox;
        }
    }

    // 3. Exibição da Tabela
    printf("\n     -METODO DO CAMINHO CRITICO-\n");
    printf("Tarefa / Duracao / IC  /  TC  / IT  / TT  / Folga / Critica\n");
    for (int i = 0; i < n; i++) {
        printf("  V%-2d  /   %2d    / %2d  / %2d  / %2d  / %2d  /  %2d   / %s\n",
               i, t[i].duracao, t[i].IC, t[i].TC, t[i].IT, t[i].TT, t[i].folga,
               (t[i].folga == 0) ? "SIM ***" : "Nao");
    }
    printf("\nDuracao Total do Projeto: %d unidades de tempo\n", duracaoTotal);
    freeGrafo(reverso);
}

void DFS(Grafo *g, int v, int visitado[], Pilha* p)
{
    visitado[v] = 1;
    printf("%d\n", v);
    No* aux = g->lista[v];

    while (aux != NULL)
    {
        if (!visitado[aux->destino]) // se a cor for branco
        {
            DFSvisita(g, aux->destino, visitado, p);
        }
        aux = aux->prox;
    }
}

void DFSvisita(Grafo* g, int u, int visitado[], Pilha* p)
{
    No* vu = g->lista[u];
    tempo = tempo + 1;
    No* aux = g->lista[u];
    aux->d = tempo;

    while (aux != NULL)
    {
        if (!visitado[aux->destino])
        {
            aux->pai = vu;
            DFSvisita(g, aux->destino, visitado, p);
        }
    }
    visitado[u] = 1;
    tempo++;
    vu->f = tempo;
    p->topo = vu;
}

void Kosaraju(Grafo* g, Grafo* gT)
{
    int visitado[100];
    Pilha* p = criaPilha();

    DFS(g, 0, visitado, p);


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