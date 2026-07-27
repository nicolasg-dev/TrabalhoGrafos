#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "grafo.h"

// 1. Leitura e Construção do Grafo (e extras)
void testeMilVertices(int dir){
    clock_t inicio = clock();
    Grafo *g = lerArquivo("grafo1000.txt", dir);
    clock_t final = clock();
    printf("Tempo para ler grafo com 1000 vertices eh de: %lfs\n", (double)(final - inicio) / CLOCKS_PER_SEC);
    inicio = clock();
    Grafo *h = lerArquivo("grafo2000.txt", dir);
    final = clock();
    printf("Tempo para ler grafo com 2000 vertices eh de: %lfs\n", (double)(final - inicio) / CLOCKS_PER_SEC);
    inicio = clock();
    Grafo *i = lerArquivo("grafo5000.txt", dir);
    final = clock();
    printf("Tempo para ler grafo com 5000 vertices eh de: %lfs\n", (double)(final - inicio) / CLOCKS_PER_SEC);
}

void Estatisticas(Grafo* g)
{
    if (g == NULL) return;
    int V = g->V;
    int A = g->A;
    int var = 0; // Variavel usada como booleana para verificar se o grafo eh conexo

    float densidade = 0;

    printf("O grafo tem %d vertices e %d arestas.\n", V, A);
    int grau = 0;
    int conexo = 0;
    No* aux = NULL;

    for (int i = 0; i < V; i++) //Percorre a lista de adjacência
    {
        aux = g->lista[i];
        while (aux !=NULL)
        {
            grau++;
            aux = aux->prox;
        }
        printf("O grau do vertice %d eh %d\n", i, grau);
        grau = 0;
    }
    aux = NULL;

    for (int i = 0; i < V; i++)
    {
        aux = g->lista[i];
        if (aux == NULL) var = 1;
    }
    if (var == 1)
        printf("O grafo ñ eh conexo.\n");
    else
        printf("O grafo eh conexo.\n");

    if (temCiclo(g))
        printf("O grafo tem ciclos.\n");
    else
        printf("O grafo ñ tem ciclos.\n");

    if (g->direcionado == 1)
        printf("O grafo eh direcionado.\n");
    else
        printf("O grafo ñ eh direcionado.\n");

    if (g->direcionado == 1)
    {
        densidade = V/V*(V-1);
        printf("A densidade do grafo eh %2.f\n", densidade);
    } else
    {
        densidade = 2*A/V*(V-1);
        printf("A densidade do grafo eh %2.f\n", densidade);
    }
}

Grafo *criarGrafo(int quantVertices) {
    Grafo *g = (Grafo *)malloc(sizeof(Grafo));
    if(g == NULL) {
        printf("Memoria insuficiente!\n");
        exit(99);
    }
    g->V = quantVertices;
    g->A = 0;
    g->lista = (No **)malloc(quantVertices * sizeof(No *)); //Aloca a quantidade necessária de memória para a lista de adjacência
    if(g->lista == NULL) {
        printf("Memoria insuficiente!\n");
        free(g);
        exit(99);
    }
    for(int i = 0; i < quantVertices; i++) {
        g->lista[i] = NULL; // Garante que todos os vertices iniciais da lista apontem para NULO
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
        } // traspoem o grafo
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
            while (aux != NULL)   //Percorre toda a lista de adjacência através de seus ponteiros prox
            {
                ant = aux;
                aux = aux->prox;
                free(ant);  //Libera as memórias alocadas pelos nos
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
    No* aux = NULL;

    for (int i = 0; i < g->V; i ++)
    {
        aux = g->lista[i];
        printf("V%d ->" , i);
        while (aux != NULL)   //Percorre toda a lista de adjacência através de seus ponteiros prox
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
        while (aux != NULL)  //Percorre toda a lista de adjacência através de seus ponteiros prox
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


int popPilha(Pilha* pi){
    if (pi->topo == NULL)
    {
        return -1;
    }
    Num* aux = pi->topo;
    int n = aux->valor;
    pi->topo = pi->topo->prox;

    free(aux);
    return n;
}

Num* extractMin (Pilha* pi){
    Num* aux;
    Num* menor = NULL;
    if (pi->topo == NULL) return NULL;
    {
        aux = pi->topo;
        while (aux != NULL)
        {
            if (aux->valor < aux->prox->valor)
            {
                menor = aux;
            }
            aux = aux->prox;
        }
    }
    return menor;
}

void addPilha(Pilha* pi, int n){
    Num* novo = (Num*) malloc(sizeof(Num));
    novo->valor = n;

    if (pi->topo == NULL)
    {
        novo->prox = NULL;
        pi->topo = novo;
    } else
    {
        novo->prox = pi->topo;
        pi->topo = novo;
    }
}

void freePilha (Pilha* pi){
    Num* aux = pi->topo;

    if (pi->topo == NULL)
    {
        return;
    } else
    {
        pi->topo = pi->topo->prox;
        free(aux);
    }
}

void printPilha (Pilha* pi){
    Num* aux = pi->topo;

    if (pi->topo == NULL)
    {
        return;
    } else
    {
        pi->topo = pi->topo->prox;
        printf("%d\n", pi->topo->valor);
    }
}

int achaPilha(Pilha* pi, Num* sugeito){
    Num* aux;

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

