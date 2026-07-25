#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "graph.h"

Grafo* grafo = NULL;
Grafo* grafo2 = NULL;


void encerra()
{
    printf("=== Encerrando o programa ===\n");
    //liberar memória usada ao decorrer do programa, talvez
    if (grafo != NULL) freeGrafo(grafo);
}

void printMenu()
{
    printf("=== SISTEMA DE GRAFOS ===\n");
    printf("1. Carregar grafo de arquivo\n");
    printf("2. Mostrar grafo (lista de adjacência)\n");
    printf("3. Busca em Profundidade (DFS)\n");
    printf("4. Busca em Largura (BFS)\n");
    printf("5. Ordenação Topológica\n");
    printf("6. Árvore Geradora Mínima (Prim)\n");
    printf("7. Menor Caminho (Dijkstra)\n");
    printf("8. Estatísticas do grafo\n");
    printf("9. Sair\n");
    printf("--- EXTRAS ---\n");
    printf("10. Detecção de Ciclos (DFS)\n");
    printf("11. Componentes Fortemente Conexos (Kosaraju/Tarjan)\n");
    printf("12. Caminho Crítico (maior distância)\n");

}

void Menu()
{
    printMenu();

    int num = 0;

    scanf("%d", &num);
    getchar();

    switch (num)
    {
    case 1:
        char nome[100];
        int dir = 0;

        printf("=== Carregar grafo de arquivo ===\n");
        printf("\nDigite o nome do arquivo: ");
        fgets(nome, 100, stdin);
        nome[strcspn(nome, "\n")] = '\0';

        printf("\nO grafo é direcionado (1) ou ñ direcionado (0)?\n");
        scanf("%d", &dir);
        switch(dir)
        {
            case 0:
            grafo = lerArquivo(nome, 0);
            break;

            case 1:
            grafo = lerArquivo(nome, 1);
            grafo2 = lerArquivoTransposto(nome);
            break;

            default:
            printf("Entrada inválida!\n");
            Menu();
            break;
        }
        //chama função desejada
        Menu();
        break;

    case 2:
        printf("=== Mostrar grafo (lista de adjacencia) ===\n");
        if (grafo2 == NULL)
        {
            printf("\nVocê ainda não carregou nenhum arquivo.\n");
            getchar();
        } else
        {
            mostrarGrafo(grafo2);
            getchar();
        }

        Menu();
        break;

    case 3:
        printf("=== Busca em Profundidade (DFS) ===\n");
        //chama função desejada
        Menu();
        break;

    case 4:
        printf("=== Busca em Largura (BFS) ===\n");
        //chama função desejada
        Menu();
        break;

    case 5:
        printf("=== Ordenacao Topologica ===\n");
        //chama função desejada
        Menu();
        break;

    case 6:
        printf("=== Arvore Geradora Minima (Prim) ===\n");
        //chama função desejada
        Menu();
        break;

    case 7:
        if (grafo == NULL)
        {
            printf("\nVocê ainda não carregou nenhum arquivo.\n");
            getchar();
        } else
        {
            int origem, destino;
            printf("=== Menor Caminho (Dijkstra) ===\n");
            printf("\nDigite a origem do algoritmo (vértice de origem)\n");

            scanf("%d", &origem);

            printf("\nDigite o destino do algoritmo (vértice de destino)\n");

            scanf("%d", &destino);
            dijkstra(grafo, origem, destino);
            getchar();
        }

        Menu();
        break;

    case 8:
        printf("=== Estatisticas do grafo ===\n");
        //chama função desejada
        Menu();
        break;

    case 9:
        encerra();
        return;

    case 10:
        printf("=== Deteccao de Ciclos (DFS) ===\n");
        //chama função desejada
        Menu();
        break;

    case 11:
        printf("=== Componentes Fortemente Conexos (Kosaraju/Tarjan) ===\n");
        //chama função desejada
        Menu();
        break;

    case 12: // Só com grafos direcionados
        if (grafo == NULL)
        {
            printf("\nVocê ainda não carregou nenhum arquivo.\n");
            getchar();
        } else
        {
            printf("=== Caminho Critico (maior distancia) ===\n");

            int *duracoes = (int*) malloc(grafo->V * sizeof(int));

            printf("--- Digite a duracao de cada tarefa ---\n");
            for (int i = 0; i < grafo->V; i++) {
                printf("Duracao da Tarefa V%d: ", i);
                scanf("%d", &duracoes[i]);
            }

            caminhoCritico(grafo, duracoes);

            free(duracoes);
            getchar();
        }
        Menu();
        break;

    default:
        printf("Opcao invalida.\n");
        Menu();
        break;
    }
}


int main (void)
{
    Menu();

    return 0;
}
