#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>
#include "grafo.h"

int tempo = 0;

static void imprimirCaminhoAux(int pai[], int v) {
    if (v == -1) return;
    imprimirCaminhoAux(pai, pai[v]);
    printf("%d ", v);
}
typedef struct {
    int duracao;
    int IC, TC; // Início/Término Mais Cedo
    int IT, TT; // Início/Término Mais Tarde
    int folga;
} TarefaCPM; // Renato

// 2. Busca em Profundidade (DFS)
void dfsIterativa(Grafo *gr, int ini, int *visitado, int *cont); // Ambas dfs foram criadas de forma opaca pois serao usadas somente no graph.c
void dfsRecursiva(Grafo *gr, int ini, int *visitado, int *cont);

void DFS(Grafo *gr, char *tipoDFS, int ini) {               // Essa funcao eh somente para identificar os componentes conexos e identificar o tipo de busca que sera feita
    int *visitado = (int*) calloc(gr->V, sizeof(int));
    if (ini > gr->V)
    {
        printf("Esse vértice não existe!\n");
        return;
    }

    if (visitado == NULL){
        return;
    }
    int cont = 1;

    for(int i = 0; i < gr->V; i++){                         // O for percorre todos os vertices
        int verticeAtual = (i + ini) % gr->V;               // Começa pelo inicio
        if(visitado[verticeAtual] == 0){
            if(strcmp(tipoDFS, "iterativa") == 0){
                dfsIterativa(gr, verticeAtual, visitado, &cont);
            } else if(strcmp(tipoDFS, "recursiva") == 0){
                dfsRecursiva(gr, verticeAtual, visitado, &cont);
            } else {
                printf("Tipo de DFS nao implementada. \n");
                free(visitado);
                return;
            }
        }
    }

    printf(" === DFS === \n"); //Exibicao dos resultados

    for(int i = 0; i < gr->V; i++){
         printf("Vertice %d | Visita: %d\n", i, visitado[i]);
    }

    printf(" \n ----------------------------------------- \n");

    free(visitado);
}

void dfsIterativa(Grafo *gr, int ini, int *visitado, int *cont){
    int *pilha = (int*) malloc((gr->V) * sizeof(int));      // Para ser iterativa, por meio de pesquisa, uma das formas que mais achei era usando pilha
    int iniP = -1;
    pilha[++iniP] = ini;                                    // Empilha o inicial

    while(iniP >= 0){
        int vert = pilha[iniP--];                           // Desempilha
        if(visitado[vert] == 0){
            visitado[vert] = (*cont)++;

            No *aux = gr->lista[vert];
            int *vizinhos = (int*) malloc(gr->V * sizeof(int)); // Tipo auxiliar para verificar os não visitados
            int k = 0;

            while(aux != NULL) {
                if(visitado[aux->destino] == 0) {
                    vizinhos[k++] = aux->destino;
                }
                aux = aux->prox;
            }

            for(int i = k - 1; i >= 0; i--){             // Empilhar ao contrário, para com que o fique na ordem certa
                pilha[++iniP] = vizinhos[i];
            }
            free(vizinhos);
        }
    }

    free(pilha);
}

void dfsRecursiva(Grafo *gr, int ini, int *visitado, int *cont) {
    visitado[ini] = (*cont)++;                          // Usado para marcar a ordem em que cada vertice sera visitado

    No *aux = gr->lista[ini];                           // Usa a lista de adjacencia para percorrer desde o inicio criando um auxiliar
    while(aux != NULL) {
        if(visitado[aux->destino] == 0){                // Se nao foi visitado
            dfsRecursiva(gr, aux->destino, visitado, cont); // Chama a funcao recursivamente
        }
        aux = aux->prox;
    }
}

// 3. Busca em Largura (BFS)
void BFS(Grafo *gr, int ini, int *visitado, int *distancia){
    int iniF = 0, fimF = 0;
    int cont = 1;

    int *fila = (int*) malloc((gr->V) * sizeof(int));   // Criacao de uma fila
    if(fila == NULL){                                   // Se a alocacao nao ocorreu de forma certa, retorna
        return;
    }

    for(int i = 0; i < gr->V; i++){                      // Marcamos primeiramente todos os vertices como nao visitado e a distancia negativa (como se nao tivesse nada)
        visitado[i] = 0;
        distancia[i] = -1;
    }

    fila[fimF++] = ini;                                 // Inserimos o vertice inicial no final da fila e marcamos ele como visitado
    visitado[ini] = cont++;
    distancia[ini] = 0;

    while(iniF < fimF) {                                // Enquanto o inicio não alcançar o fim
        int vert = fila[iniF++];                        // Remove um vertice da fila
        No *aux = gr->lista[vert];                      // Acesso a lista de adjacencia para ajudar percorrer a fila
        while(aux != NULL){
            if(!visitado[aux->destino]){                // Para cada "vizinho" cerifica se ele foi visitado
                fila[fimF++] = aux->destino;            // Caso nao eh inserido no final
                visitado[aux->destino] = cont++;        //marcado como visitado
                distancia[aux->destino] = distancia[vert] + 1;  // Calculado a distancia
            }
            aux = aux->prox;
        }
    }

    printf(" === BFS === \n");                          //Exibicao dos resultados

    for(int i = 0; i < gr->V; i++){
        if(distancia[i] != -1) {
            printf("Vertice %d | Visita: %d | Distancia: %d\n", i, visitado[i], distancia[i]);
        }
    }

    printf(" \n ----------------------------------------- \n");
    free(fila);
}

// 4. Ordenação Topológica
// (não implementado)

// 5. Árvore Geradora Mínima - Prim
void prim(Grafo *gr, int orig, int *pai){               // Os testes que fiz usando grafos desconexos ficaram muito estranhos entao preferi implementar sem o tratamento em uma versao mais limpa
    int i, primeiro, destMin, origMin, menorPeso, pesoTotal = 0;

    int *visitado = (int*) calloc(gr->V, sizeof(int));  // Alocação dinâmica para o vetor de visitados para evitar estouro de pilha (stack overflow)

    if (visitado == NULL) return;

    for(i = 0; i < gr->V; i++){                         // inicializacao
        pai[i] = -1;                                    // Significa que nao tem pai
        visitado[i] = 0;                                // Significa que nao esta na arvore ainda
    }

    pai[orig] = orig;
    visitado[orig] = 1;                                 // A origem ja esta na arvore

    printf(" === Árvore Geradora Mínima (Prim) === \n");

    while(1){                                           // Loop para encontrar as arestas
        primeiro = 1;                                   // Resetar em cada rodada
        origMin = -1;
        destMin = -1;
        menorPeso = 0;

        for(int i = 0; i < gr->V; i++){
            if(visitado[i] == 1){                       // Se o vertice ja faz parte da arvore
                No *aux = gr->lista[i];                 // Novamente por um auxiliar da lista de adjacencia eh feito verificacao
                while(aux != NULL){
                    if(visitado[aux->destino] == 0) {
                        if(primeiro){
                            menorPeso = aux->peso;
                            origMin = i;
                            destMin = aux->destino;
                            primeiro = 0;
                        } else {
                            if(menorPeso > aux->peso){
                                menorPeso = aux->peso;
                                origMin = i;            // Atualiza origMin
                                destMin = aux->destino; // Atualiza destMin
                            }
                        }
                    }
                    aux = aux->prox;
                }
            }
        }

        if(primeiro == 1){          // Se nenhum vertice foi encontrado, está completa

            break;
        }

        pai[destMin] = origMin;
        visitado[destMin] = 1;
        pesoTotal += menorPeso;

        printf("Aresta: (%d - %d) | Peso: %d\n", origMin, destMin, menorPeso);
    }

    printf("-----------------------------------------\n");
    printf("Peso Total da Arvore Geradora Minima: %d\n", pesoTotal);
    printf("-----------------------------------------\n");

    free(visitado); // Libera a memória alocada
}

// 6. Menor Caminho - Dijkstra
// (Implementado por Renato)
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

// 7. Desafios Extras
// 7. 1. Deteccao de Ciclos
// (Implementado por Angelo)

// 7. 2. Componentes Fortemente Conexos
// (Implementado por Nicolas)
void Kosaraju(Grafo* g)
{
    int n = g->V;
    int visitado[100];
    Pilha* p = criaPilha();

    //DFS(g, 0, visitado, p);

    Grafo *reverso = criarGrafo(n);
    for (int u = 0; u < n; u++) {
        No *aux = g->lista[u];
        while (aux != NULL) {
            adicionarArestaOrdenado(reverso, aux->destino, u, aux->peso); // Inverte u -> v para v -> u
            aux = aux->prox;
        }
    }

    //(reverso, 0, visitado, p);
}

// 7. 3. Caminho Crítico
// (não implementado)
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

// 7. 4. Grafo com 1000+ vértices
// (Implementado por Pedro Lucas)




/*void BFS(Grafo *g, int origem) {
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
}*/

/*void DFS(Grafo *g, int v, int visitado[], Pilha* p)
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
}*/