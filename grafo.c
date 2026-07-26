#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "grafo.h"

// 1. Leitura e Construção do Grafo (e extras)

Grafo *criarGrafo(int quantVertices) {
    Grafo *g = (Grafo *)malloc(sizeof(Grafo));
    if(g == NULL) {
        printf("Memoria insuficiente!\n");
        exit(99);
    }
    g->V = quantVertices;
    g->A = 0;
    g->lista = (No **)malloc(quantVertices * sizeof(No *));
    if(g->lista == NULL) {
        printf("Memoria insuficiente!\n");
        free(g);
        exit(99);
    }
    for(int i = 0; i < quantVertices; i++) {
        g->lista[i] = NULL;
    }
    return g;
}

Grafo *lerArquivo(char *nome, int dir){
    FILE *arquivo = fopen(nome, "r");
    if(arquivo == NULL){
        printf("\nErro ao abrir o arquivo!\n");
        return NULL;
    }
    int Vertices, Arestas, Origem, Destino, Peso;
    fscanf(arquivo,"%d %d", &Vertices, &Arestas); //le os primeiros dois inteiros do arquivo para saber a quantidade de vertices e arestas
    Grafo *g = criarGrafo(Vertices);

    if (dir == 0)
    {
        while(fscanf(arquivo, "%d %d %d", &Origem, &Destino, &Peso) == 3){ //coleta os dados subsequentes de 3 em tres para adicionar as arestas
            adicionarArestaOrdenadoNDir(g, Origem, Destino, Peso); // fiz esse while de == 3 pois o retorno do fscanf é a quantidade de dados que ele le e enquanto ele ler
        } // 3 arquivos o programa da certo
    } else if (dir == 1)
    {
        while(fscanf(arquivo, "%d %d %d", &Origem, &Destino, &Peso) == 3){
            adicionarArestaOrdenado(g, Origem, Destino, Peso);
        }
    }

    fclose(arquivo);
    if(g->A == Arestas){
        return g; // faço o teste para verificar se a quantidade de arestas informadas no arquivo esta de acordo com a quantidade de arquivos do grafo e se nao for
    } // o caso deu algum erro na leitura
    printf("Erro na leitura dos dados!\n");

}

No *criarNo(int destino, int peso) {
    No *novo=(No *)malloc(sizeof(No));
    if(novo == NULL){
        printf("Memoria insuficiente!\n");
        exit(99);
    }
    novo->destino = destino;
    novo->peso = peso;
    novo->prox = NULL;
    novo->pai = NULL;
    return novo;
}

void adicionarArestaOrdenado(Grafo *g, int origem, int destino, int peso) {
    No *novo = criarNo(destino, peso);
    if(g->lista[origem] == NULL || destino < g->lista[origem]->destino){
        novo->prox = g->lista[origem];
        g->lista[origem] = novo;
        novo->pai = g->lista[origem];
    }
    else {
        No *atual = g->lista[origem];
        while (atual->prox != NULL && atual->prox->destino < destino) {
            atual = atual->prox;
        }
        novo->prox = atual->prox;
        atual->prox = novo;
        novo->pai = atual;
    }
    g->A++;
}

void adicionarArestaOrdenadoNDir(Grafo *g, int origem, int destino, int peso) {
    No *novo = criarNo(destino, peso);
    if(g->lista[origem] == NULL || destino < g->lista[origem]->destino){
        novo->prox = g->lista[origem];
        g->lista[origem] = novo;
    }
    else {
        No *atual = g->lista[origem];
        while (atual->prox != NULL && atual->prox->destino < destino) {
            atual = atual->prox;
        }
        novo->prox = atual->prox;
        atual->prox = novo;
    }
    No *segundoNo = criarNo(origem, peso);
    if(g->lista[destino] == NULL || origem < g->lista[destino]->destino){
        segundoNo->prox = g->lista[destino];
        g->lista[destino] = segundoNo;
    }
    else{
        No *atual2 = g->lista[destino];
        while(atual2->prox != NULL && atual2->prox->destino < origem){
            atual2 = atual2->prox;
        }
        segundoNo->prox = atual2->prox;
        atual2->prox = segundoNo;
    }
    g->A++;
}

void freeGrafo(Grafo* g){
    if (g == NULL) return;
    No* aux = NULL;
    No* ant = NULL;

    for (int i = 0; i < g->V; i ++)
    {
        if (g->lista[i] != NULL)
        {
            aux = g->lista[i];
            ant = NULL;
            while (aux != NULL)
            {
                ant = aux;
                aux = aux->prox;
                free(ant);
            }
        }
    }
    free(g);
}

void mostrarGrafo(Grafo* g) {
    if (g->lista == NULL)
    {
        printf("Grafo vazio!\n");
        return;
    }

    for (int i = 0; i < g->V; i ++)
    {
        No * aux = g->lista[i];
        printf("V%d ->" , i);
        while (aux != NULL)
        {
            printf(" V%d (%d) ->", aux->destino, aux->peso);
            aux = aux->prox;
        }
        printf("\n");
    }
}

void removeVertice(Grafo *g, int alvo) {
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

// 8. Funcoes Pilha
Pilha* criaPilha (){
    Pilha* pi = malloc(sizeof(Pilha));
    if (pi != NULL) pi->topo = NULL;
    return pi;

}

No* extractMin (Pilha* pi){
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

void addPilha(Pilha* pi, No* novo){
    if (pi->topo == NULL)
    {
        pi->topo = novo;
    } else
    {
        novo->prox = pi->topo;
        pi->topo = novo;
    }
}

void removePilha (Pilha* pi){
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

int achaPilha(Pilha* pi, No* sugeito){
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

